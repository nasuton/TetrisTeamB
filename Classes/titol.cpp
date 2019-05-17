#include "titol.h"
#include "SceneManager.h"
USING_NS_CC;

titol::titol()
{

}

titol::~titol()
{

}

Scene* titol::createScene()
{
	auto scene = Scene::create();
	auto layer = titol::create();
	scene->addChild(layer);
	return scene;
}

bool titol::init() {
	
	if (!Layer::init()) {
		return false;
	}

	auto director = Director::getInstance();
	auto size = director->getWinSize();

	auto background = Sprite::create("background.png");
	background->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
	this->addChild(background);

	auto logo = Sprite::create("TitleName.png");
	logo->setPosition(Vec2(size.width / 2.0, size.height /2.0));
	this->addChild(logo);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* _event)-> bool {
		//this->getEventDispatcher()->removeAllEventListeners();
		auto delay = DelayTime::create(0.5);
		auto startGame = CallFunc::create([] {
			//auto scene = GameScene::SceneCreate();
			//auto transition = TransitionPageTurn::create(0.5, scene, true);
			//Director::getInstance()->replaceScene(transition);
			
				SceneManager::CreateTutorialScene();
		});
		this->runAction(Sequence::create(delay, startGame, NULL));
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}