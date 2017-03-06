#include"cocos2d.h"
#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__


#include"UserInfoScene.h"
#include"SelectedScene.h"
#include "Welcome.h"
#include "CreateJoin.h"

using namespace cocos2d;

class HomeScene :public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(HomeScene);
	static Scene* createScene();
	


};
#endif // __HOME_SCENE_H__