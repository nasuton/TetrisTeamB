#ifndef BLOCK_h
#define BLOCK_h

#include "cocos2d.h"

class Block
{
public:
	enum kColor
	{
		kColor_white,
	};

private:

	int number;
	int color;

public:
	Block(int num, int col);
	~Block();

	int GetNumber();
	int GetColor();
};

#endif