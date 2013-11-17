#include "player.h"
#include "eventblock.h"
#include <ctime>
#include <iostream>

using namespace std;

EventBlock::EventBlock()
{
}

EventBlock::~EventBlock()
{
}

void EventBlock::checkEvent(Player* player)
{
	// �̺�Ʈ ���� ������ �����Ͽ� ������ �̺�Ʈ �߻�
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
		clubActivity(player);
		break;
	}
}

void EventBlock::drink(Player* player)
{
	// ���ַ� ���� �ൿ�� ����
	player.setEnergy(player.getEnergy() - 100);
}

void EventBlock::cc(Player* player)
{
	// Ŀ�� Ȱ������ ���� �ൿ�� ���� ( �ƴϸ� ���� Ȯ���� ������? )
	player.setEnergy(player.getEnergy() - 100);
}

void EventBlock::takeSubject(Player* player)
{
	// �÷��̾ ������ �ϳ� ������ �� buyBlock�� �����Ѵ�.
	// player.buyBlock();
}

void EventBlock::loseSubject(Player* player)
{
	// �÷��̾ ���� �ϳ��� �Ҵ´�. (���� or ����)
	// player.sellBlock();
}

void EventBlock::lol(Player* player)
{
	// �� �ʹ� �����ؼ� �ൿ�� ���� ����
	player.setEnergy(player.getEnergy() - 100);
}

void EventBlock::eatChicken(Player* player)
{
	// ġ������ �����Ͽ� �ൿ�� ����
	player.setEnergy(player.getEnergy() + 100);

}

void EventBlock::clubActivity(Player* player)
{
	// ���Ƹ� Ȱ������ ������ �ð��� ����..
	player.setEnergy(player.getEnergy() - 100);
}