#include "TitleScene.h"
#include "TitleLayer.h"

USING_NS_CC;

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

Scene* TitleScene::SceneCreate()
{
	Scene* scene = Scene::create();

	//Layerを子として追加
	scene->addChild(CreateLayer<TitleLayer>());

	return scene;
}