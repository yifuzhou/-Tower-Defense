#ifndef __SELECTED_SCENE_H__
#define __SELECTED_SCENE_H__
#include"cocos2d.h"
#include"HelloWorldScene.h"
#include"SingleGameScene.h"
#include"SingleGameScene2.h"
#include"SingleGameScene3.h"
#include"SingleGameScene4.h"
#include"HomeScene.h"
using namespace cocos2d;

class  SelectedScene :public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(SelectedScene);
	static Scene* createScene();
	void addLevelFlag(int);
	void popUp(int);

};
#endif // __MONSTER_H__