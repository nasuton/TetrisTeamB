#ifndef FIELD_h
#define FIELD_h

#include "Config.h"
#include "Chunk.h"

class Field
{
public:
	Block*** blocks;

public:
	Field();
	~Field();
};

#endif