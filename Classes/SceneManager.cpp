#include "SceneManager.h"
#include "TutorialScene.h"
#include "GameScene.h"

USING_NS_CC;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::CreateGameScene()
{
	Scene* nextScene = SceneCreate<GameScene>();
	auto sceneAnimation = TransitionFade::create(1.0f, nextScene, Color3B::WHITE);
	Director::getInstance()->replaceScene(sceneAnimation);
}

void SceneManager::CreateTutorialScene()
{
	Scene* nextScene = SceneCreate<TutorialScene>();
	Director::getInstance()->replaceScene(nextScene);
}