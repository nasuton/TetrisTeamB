#ifndef __tetris__GameScene__
#define __tetris__GameScene__

#include "cocos2d.h"
#include "Game.h"

class GameScene : public cocos2d::Layer
{
private:
    Game* game;
    int lastBlockNumber = 0;
    
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
    
    void moveUnder(float dt);
    
    void deleteLines();
    
    void resetIfGameover();
    
public:
    virtual bool init();
    static cocos2d::Scene* Createscene();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__tetris__GameScene__) */
