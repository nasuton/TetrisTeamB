#ifndef GAMESCENE_h
#define GAMESCENE_h

#include "SceneBase.h"

class GameScene : public SceneBase
{
public:
	GameScene();
	virtual ~GameScene();

	static cocos2d::Scene* SceneCreate();
};

#endif