#include "TutorialLayer.h"
#include "SceneManager.h"

USING_NS_CC;

TutorialLayer::TutorialLayer()
{

}

TutorialLayer::~TutorialLayer()
{

}

bool TutorialLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	//チュートリアル画像を表示
	Sprite* tutorialTexture = Sprite::create("tutorial.png");
	tutorialTexture->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
	this->addChild(tutorialTexture);

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