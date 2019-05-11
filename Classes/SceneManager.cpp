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
	Director::getInstance()->replaceScene(nextScene);
}

void SceneManager::CreateTutorialScene()
{
	Scene* nextScene = SceneCreate<TutorialScene>();
	Director::getInstance()->replaceScene(nextScene);
}