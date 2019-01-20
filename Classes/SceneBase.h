#ifndef SCENEBASE_h
#define SCENEBASE_h

#include "cocos2d.h"

class SceneBase : public cocos2d::Scene
{
public:
	SceneBase();
	virtual ~SceneBase();

protected:
	//Layer‚ð’Ç‰Á‚·‚é
	template <class LayerClass>
	static cocos2d::Layer* CreateLayer();
};

template <class LayerClass>
inline cocos2d::Layer* SceneBase::CreateLayer()
{
	auto layer = LayerClass::create();

	return layer;
}

#endif