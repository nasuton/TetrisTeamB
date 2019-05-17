#ifndef TITLESCENE_h
#define TITLESCENE_h

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	static cocos2d::Scene* SceneCreate();
};

#endif