#ifndef __USERINFO_SCENE_H__
#define __USERINFO_SCENE_H__
#include"cocos2d.h"
#include"HelloWorldScene.h"
#include"HomeScene.h"
#include "network\HttpRequest.h"
#include "network\HttpClient.h"
#include "network\HttpResponse.h"
#include "PublicVar.h"
#include "spine\Json.h"
using namespace cocos2d::network;

class  UserInfoScene:public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(UserInfoScene);
	static Scene* createScene();
	void complete2(HttpClient *client, HttpResponse *response);


};
#endif // __USERINFO_SCENE_H__