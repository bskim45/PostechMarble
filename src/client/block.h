#pragma once
#include "block.h"

// circular dependency
class Board;
class Player;

class Block
{
public:
    enum CornerType
    {
        DORMITORY,
        CALLTAXI,
        BREAKSEMESTER,
        PLURALMAJOR
    };
	int blocknumber;//blocknumber Ȥ�� board�� ��� ��ȣ�� �� �� ��ȣ�� ������ �� ������ ���ڴ�.. �ƴϸ� �̰� ��ǥ�� �ϰ��ֳ�!?
					//0�� =dormitory~

public:


    Block();
    virtual ~Block();
    virtual void enter(Player* player);
};

