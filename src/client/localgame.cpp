#include "localgame.h"
#include "dice.h"
#include "board.h"
#include "subjectblock.h"
#include <iostream>
#include <QDebug>
#include <QtGlobal>
#include <QMessageBox>

using namespace std;
using namespace LocalGameState;

LocalGame::LocalGame(){
    m_state = ROLL_DICE;
    player_queue = new PlayerQueue;
}

//Singleton methods
LocalGame * LocalGame::m_inst = NULL;

LocalGame * LocalGame::getInst(){
    if(m_inst == NULL){
        m_inst = new LocalGame;
    }

    return m_inst;
}

void LocalGame::delInst(){
    if(m_inst != NULL){
        delete m_inst;
        m_inst = NULL;
    }
}

void LocalGame::addPlayer(Player *new_player){
    player_queue->push(new_player);
    nPlayers++;
    emit new_player->disable();
    connect(new_player,SIGNAL(playerArrived(Player*)),this,SLOT(playerEvent(Player*)));
}

void LocalGame::init(Board * board, Dice * dice){
    m_current_player = player_queue->next();
    Q_CHECK_PTR(m_current_player);
    emit m_current_player->activate();
    m_board = board;
    m_dice = dice;
    nPlayers = 0;
    connect(m_dice,SIGNAL(diceRolled(Dice*)),this,SLOT(diceEvent(Dice*)));
}

Board* LocalGame::getBoard(){
    return m_board;
}

void LocalGame::setBoard(Board *board){
    m_board = board;
}

Dice* LocalGame::getDice(){
    return m_dice;
}

void LocalGame::setDice(Dice * dice){
    m_dice = dice;
}

Player* LocalGame::getCurrentPlayer(){
    return m_current_player;
}

LocalGameState::State LocalGame::getGameState(){
    return m_state;
}

void LocalGame::setGameState(State new_state){
    m_state = new_state;
}



void LocalGame::turnOver(){
    //switch current player to next player and change state
    if(m_current_player->checkWinStatus()){
        //TODO: need to emit signal to notify gameover
        winner = m_current_player;
        qDebug() << "winner! player:" << m_current_player->getId();
        m_state = GAME_OVER;
        return;
    }
    if(m_current_player->isBankrupt()){
        nPlayers--;
        if(nPlayers == 1) {
            qDebug() << "winner! player:" << m_current_player->getId();
            winner = player_queue->next();
            m_state = GAME_OVER;
            return;
        }
    }
    //should never happen
    Q_ASSERT(nPlayers != 1);
    //update current Player if dice is not double
    emit m_current_player->disable();
    if(!Dice::getInst()->isDouble()){
        do {
            m_current_player = player_queue->next();
        } while(m_current_player->isBankrupt());
    }
    emit m_current_player->activate();
    m_state = ROLL_DICE;
}

void LocalGame::diceEvent(Dice * dice){
    qDebug() << "dice event caught by localgame";
    if(m_state == ROLL_DICE){
        if(m_current_player->isMobile()){
            m_current_player->walkBy(dice->getValue());
        }
        else{
            if(dice->isDouble()){
                m_current_player->setMobile(true);
                m_current_player->walkBy(dice->getValue());
            }
            else{
                m_current_player->escapeAttempt(); //decreases one immobile penalty
                turnOver();
            }
        }
    }
}

void LocalGame::blockEvent(Block *block){
    qDebug() << "block event caught:" << block->getPosition();
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    if(m_state == JUMP_PLAYER){
        m_current_player->jumpTo(block->getPosition());
    }
    //drink event
    if(m_state == EVENT_DRINK){
        if (block->getPosition() != 20 && block->getPosition() != 4){
            //not a valid location to jump.
            warn_box.setWindowTitle(QString("이벤트: 음주"));
            warn_box.setText(QString("불금칸으로만 갈 수 있어요!"));
            warn_box.exec();
        }
        else{
            m_current_player->jumpTo(block->getPosition());
        }
    }
    //take subject event
    if(m_state == EVENT_TAKE_SUBJECT){
        if(block->getType() == BlockType::SUBJECT){
            m_current_player->addBlock(block);
            SubjectBlock * subj = dynamic_cast<SubjectBlock*>(block);
            subj->decideGrade();
            LocalGame::getInst()->turnOver();
        }
        else{
            warn_box.setWindowTitle("이벤트: 과목 수강");
            warn_box.setText("과목 블럭을 선택해 주세요!");
            warn_box.exec();
        }
    }

    if(m_state == EVENT_LOSE_SUBJECT){
        if(block->getType() == BlockType::SUBJECT){
            m_current_player->removeBlock(block);
            LocalGame::getInst()->turnOver();
        }
        else{
            warn_box.setWindowTitle("이벤트: 과목 포기");
            warn_box.setText("과목 블럭을 선택해 주세요!");
            warn_box.exec();
        }
    }
}

void LocalGame::playerEvent(Player *player){
    qDebug() << "signal emmited by Player" << player->getId();
    if(m_state == PLAYER_MOVING){
        qDebug() << "Player in block!";
        int position = player->getPosition();
        Block * cur_block = m_board->getBlock(position);
        cur_block->enter(player);
    }
}

void LocalGame::boardEvent(Board *board){

}
