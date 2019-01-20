#ifndef SCENEMANAGER_h
#define SCENEMANAGER_h

#include "cocos2d.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	//�����V�[����ǉ����Ă���

private:
	template <class Scene>
	static cocos2d::Scene* SceneCreate();

};

template<class Scene>
inline cocos2d::Scene* SceneManager::SceneCreate()
{
	cocos2d::Scene* scene = Scene::SceneCreate();

	return scene;
}

#endif