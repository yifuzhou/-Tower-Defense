#ifndef __CREATE_JOIN_H__
#define __CREATE_JOIN_H__
#include "cocos2d.h"
#include "ChooseIP.h"
#include "HomeScene.h"
#include "DoubleGameScene.h";
#include "PublicVar.h"

USING_NS_CC;

class CreateJoin : public Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	void CreateRoom(Ref *pSender);
	void JoinGame(Ref *pSender);

	CREATE_FUNC(CreateJoin);
};
#endif __CREATE_JOIN_H__