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

	//Layer‚ğq‚Æ‚µ‚Ä’Ç‰Á
	scene->addChild(CreateLayer<GameLayer>());

	return scene;
}