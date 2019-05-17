#ifndef __tetris__titol__
#define __tetris__titol__

#include "cocos2d.h"
#include "GameScene.h"

class titol : public cocos2d::Layer
{
protected:
	titol();
	virtual ~titol();
	bool init() override;

public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(titol);

	
};

#endif // __HELLOWORLD_SCENE_H__