#include "Block.h"

Block::Block(int num, int col)
	:number(num)
	,color(col)
{
}

Block::~Block()
{
}

int Block::GetNumber()
{
	return number;
}

int Block::GetColor()
{
	return color;
}
