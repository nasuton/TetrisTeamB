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

	//Layer���q�Ƃ��Ēǉ�
	scene->addChild(CreateLayer<GameLayer>());

	return scene;
}