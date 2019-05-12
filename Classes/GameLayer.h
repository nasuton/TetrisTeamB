#ifndef GAMELAYER_h
#define GAMELAYER_h

#include "LayerBase.h"
#include "Game.h"

class GameLayer : public LayerBase
{
public:
	GameLayer();
	virtual ~GameLayer();

	CREATE_FUNC(GameLayer);

private:
	bool init();

	void makeField();

	void makeControlButton();
	void tapMoveLeft(cocos2d::Ref* pSender);
	void tapMoveRight(cocos2d::Ref* pSender);
	void tapTurnLeft(cocos2d::Ref* pSender);
	void tapTurnRight(cocos2d::Ref* pSender);

	void startGame();

	void makeChunk();
	void moveChunk();
	void makeAndMoveChunk(float dt);

	void moveUnder(float delta);

	void deleteLines();

	void resetIfGameover();

private:
	Game* game;
	int lastBlockNumber = 0;
	bool isEnd;
	cocos2d::EventListenerKeyboard* listener;
};

#endif