#ifndef __CHOOSE_IP_H__
#define __CHOOSE_IP_H__

#include "DoubleGameScene.h"
#include "cocos2d.h"
#include "network\HttpRequest.h"
#include "network\HttpClient.h"
#include "network\HttpResponse.h"

using namespace cocos2d::network;
USING_NS_CC;

class ChooseIP : public Layer
{
public:
	std::string IPtoJoin;

	static cocos2d::Scene* createScene();
	virtual bool init();
	void refresh(Ref *pSender);
	void connect(Ref *psender);
	void ChooseIP::GETcompleted(HttpClient *client, HttpResponse *response);
	int pointer;
	Vector<Label*> labelID;
	Vector<Sprite*> labelID_B;

	virtual void update(float);

	
	CREATE_FUNC(ChooseIP);
};

#endif 
