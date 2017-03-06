#ifndef __WELCOME_H__
#define __WELCOME_H__

#include"HomeScene.h"


#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "ui\UIEditBox\UIEditBox.h"
#include "network\HttpRequest.h"
#include "network\HttpClient.h"
#include "network\HttpResponse.h"
#include"PublicVar.h"

using namespace cocos2d::network;

class Welcome: public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void toRegister(Ref *pSender);

	void toLogin(Ref *pSender);

	void toExit(Ref *pSender);

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);

	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);

	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);

	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

	void complete2(HttpClient *client, HttpResponse *response);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Welcome);
};

#endif // __WELCOME_H__
