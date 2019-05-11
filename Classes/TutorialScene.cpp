#include "TutorialScene.h"
#include "TutorialLayer.h"

USING_NS_CC;

TutorialScene::TutorialScene()
{

}

TutorialScene::~TutorialScene()
{

}

Scene* TutorialScene::SceneCreate()
{
	Scene* scene = Scene::create();

	//Layerを子として追加
	scene->addChild(CreateLayer<TutorialLayer>());

	return scene;
}