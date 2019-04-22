#include "GameScene.h"
#include "GameLayer.h"

USING_NS_CC;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

Scene* GameScene::SceneCreate()
{
	Scene* scene = Scene::create();

	//Layerを子として追加
	scene->addChild(CreateLayer<GameLayer>());

	return scene;
}