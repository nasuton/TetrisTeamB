#ifndef MODALLAYER_h
#define MODALLAYER_h

#include "cocos2d.h"

class ModalLayer : public cocos2d::Layer 
{
public:
	ModalLayer();
	~ModalLayer();

	CREATE_FUNC(ModalLayer);
private:
	bool init();
};

#endif