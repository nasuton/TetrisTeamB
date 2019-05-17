#ifndef TITLELAYER_h
#define TITLELAYER_h

#include "LayerBase.h"

class TitleLayer : public LayerBase 
{
public:
	TitleLayer();
	virtual ~TitleLayer();

	CREATE_FUNC(TitleLayer);

private:
	bool init();

};

#endif