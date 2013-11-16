#pragma once
#include <list>
#include "block.h"

class Block;
enum CharacterType {
		NONE, LOL, GENIUS, HARD_WORKER, OUTSIDER, ALCOHOLIC
	};

class Player
{
public:


private:
    int     position;
    int     energy;
    bool    bankrupt;
    bool    mobile;
    int     panelty;
	int		checkmouindo;
	bool	checkwinstatus;
    std::list<Block>   own_blocks;
    CharacterType character_type;

public:
    Player();
    ~Player();

    int getPosition() const;
    bool isMobile() const;
    int getEnergy() const;
	CharacterType getCharacter_Type() const;
	int getMouindo() const;

    void setPosition(int position);
	void setEnergy(int getenergy);
	void setMouindo(int mouindonumber);
    void moveTo(int position);//blocknumber�� position�� ������ �̵��ϰ� ��
							//block���� �� ���� �ִ� �÷��̾ playerpointer(������ ��� ���� �������?)�� �����ϰ� �Ѵٸ� ������ move�� ���ش� ���� �÷��̾� �����͸� �־��ټ��ְٴ�!? �ƴѰ� �ݴ�� �ؾߵǳ� ��
    bool checkWinStatus();
    int getMouindo();//�ش� player�� ���ε� �ȿ� �����鼭 ���� turn.. 0�̸� ���� ��ȥ
    bool escapeMouindo();
    bool hasBlock(Block block);
    void buyBlock(Block block);
    void sellBlock(Block block);


};
      
