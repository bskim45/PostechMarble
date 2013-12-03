#include "eventblock.h"
#include "scene/ingamescene.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "localgame.h"

using namespace std;

// Constructor & Destructor
EventBlock::EventBlock(QGameItem * parent) : Block(parent)
{
}


EventBlock::~EventBlock()
{

}


// Methods
void EventBlock::enter(Player* player)
{
    LocalGame::getInst()->turnOver();
    return;
}

void EventBlock::checkEvent(Player* player)
{
    // generate random event
    srand((unsigned)time(NULL));
    int value = rand() % 7;

    switch(value) {
        case 0:
            drink(player);
            break;
        case 1:
            cc(player);
            break;
        case 2:
            takeSubject(player);
            break;
        case 3:
            loseSubject(player);
            break;
        case 4:
            lol(player);
            break;
        case 5:
            eatChicken(player);
            break;
        case 6:
            photoGenic();
            break;
    }
}

void EventBlock::drink(Player* player)
{
    // 원하는 불금칸을 이동
     
}

void EventBlock::cc(Player* player)
{
    // 행동력 감소 + 일정 확률로 휴학 또는 61콜 이동
    if(getType()!=CharacterType::OUTSIDER)
    {
        int c;
        c= rand()%2;
        switch(c)
        {
        case 0:
            // 휴학블록으로 이동
            break;
        case 1:
            //61블록으로 이동
            break;
        }
    }
}

void EventBlock::takeSubject(Player* player)
{
    // 플레이어가 과목을 하나 선택한 후 buyBlock을 실행한다
    //player->buyBlock();
}

void EventBlock::loseSubject(Player* player)
{
    // 플레이어가 과목 하나를 잃는다. (랜덤 or 선택)
    //player->sellBlock();
}

void EventBlock::lol(Player* player)
{
    // 50:50으로 행동력 증가 또는 감소, lol타입 캐릭터의 경우 항상 증가
    if(getType()==CharacterType::LOL)
    player->setEnergy(player->getEnergy() +50); //
    else
    {
        int outcome;
        outcome=rand()%2;
        if(outcome==0)
        player->setEnergy(player->getEnergy()+50); //승리
        else if(player->getEnergy()>=100)
            player->setEnergy(player->getEnergy() - 100);
        else
        {
            if(player->getAssetValue() > 100){

                Sellpopup * popup = new Sellpopup();
                popup->show();

            }
        } // 패배
    }
}

void EventBlock::eatChicken(Player* player)
{
    // 치느님을 영접하여 행동력 증가
    player->setEnergy(player->getEnergy() + 100);

}

void EventBlock::photoGenic()
{
    dynamic_cast<IngameScene*>(QGameItem::parent_scene)->showPhotoGenic();
}
