#include "ModalLayer.h"
#include "SceneManager.h"

USING_NS_CC;

ModalLayer::ModalLayer()
{

}

ModalLayer::~ModalLayer()
{

}

bool ModalLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	//背景に黒の画像を表示
	Sprite* maskSprite = Sprite::create("mask.png");
	maskSprite->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
	this->addChild(maskSprite);

	//gameOverの画像を表示
	Sprite* gameOver = Sprite::create("gameOver.png");
	gameOver->setPosition(winSize.width * 0.5f, winSize.height * 0.8f);
	this->addChild(gameOver);

	//Labelを追加
	auto reStartLabel = LabelTTF::create("Please press\nEnter to retry", "Arial", 50.0f, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	reStartLabel->setPosition(winSize.width * 0.5f, winSize.height * 0.45f);
	this->addChild(reStartLabel);

	auto backTitle = LabelTTF::create("Please press\nSpace to the Title", "Arial", 50.0f, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	backTitle->setPosition(winSize.width * 0.5f, winSize.height * 0.2f);
	this->addChild(backTitle);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* _event)-> bool {
		//実際の処理をキーに割り当てる
		switch (keyCode)
		{
		//リスタートする
		case EventKeyboard::KeyCode::KEY_ENTER:
			SceneManager::CreateGameScene();
			break;
		//チュートリアルへ戻る
		//TODO : タイトルへ戻るようにする
		case EventKeyboard::KeyCode::KEY_SPACE:
			SceneManager::CreateTutorialScene();
			break;
		default:
			break;
		}

		return true;
	};

	//上記のキーボードイベントを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}