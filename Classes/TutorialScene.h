#ifndef TUTORIALSCENE_h
#define TUTORIALSCENE_h

#include "SceneBase.h"

class TutorialScene : public SceneBase
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	static cocos2d::Scene* SceneCreate();
};

#endif