#include "TitleLayer.h"
#include "SceneManager.h"

USING_NS_CC;

//文字化けを防ぐおまじない
#pragma execution_character_set("utf-8")

TitleLayer::TitleLayer() 
{

}

TitleLayer::~TitleLayer()
{

}

bool TitleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	//背景の追加
	Sprite* backGround = Sprite::create("background.png");
	backGround->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
	this->addChild(backGround);

	//タイトルを追加
	Sprite* titleSprite = Sprite::create("TitleName.png");
	titleSprite->setPosition(winSize.width * 0.5f, winSize.height * 0.7f);
	this->addChild(titleSprite);

	//文字を表示する
	Label* pressKeyMessage = Label::createWithSystemFont("～ Start by pressing Enter ～", "Arial", 55.0f);
	pressKeyMessage->setPosition(winSize.width * 0.5f, winSize.height * 0.3f);
	pressKeyMessage->setTextColor(Color4B::BLACK);
	//アウトラインを付ける(きちんと動作しない、なぜ？)
	//pressKeyMessage->enableOutline(Color4B::WHITE, 5);
	//影を付ける
	pressKeyMessage->enableShadow(Color4B::WHITE);
	this->addChild(pressKeyMessage);
	//点滅のアニメーションを追加
	auto flashing = Sequence::create(FadeOut::create(1.5f), FadeIn::create(1.5f), NULL);
	pressKeyMessage->runAction(RepeatForever::create(flashing));

	//キーイベントを作成する
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* _event)-> bool {
		//実際の処理をキーに割り当てる
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_ENTER:
			SceneManager::CreateGameScene();
			break;
		default:
			break;
		}

		return true;
	};

	//上記で作ったものを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}