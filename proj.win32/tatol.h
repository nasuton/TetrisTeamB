#ifndef __tetris__tatol__
#define __tetris__tatol__

#include "cocos2d.h"
#include "GameScene.h"

class titol : public cocos2d::Scene 
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// there's no 'id' in cpp, so we recommend to return the class instance pointer
	static cocos2d::CCScene* scene();


	// スプライトを格納する配列
	cocos2d::CCArray enemys;


	// タッチ関係のイベント
	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

	// implement the "static create()" method manually
	CREATE_FUNC(titol);
};

#endif // __HELLOWORLD_SCENE_H__