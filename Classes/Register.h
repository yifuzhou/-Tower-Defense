#ifndef __REGISTER_H__
#define __REGISTER_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "ui\UIEditBox\UIEditBox.h"
#include "network\HttpRequest.h"
#include "network\HttpClient.h"
#include "network\HttpResponse.h"
#include "Welcome.h"
using namespace cocos2d::network;

class Register : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    bool init();

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);

	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);

	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);

	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

	bool Confirm(Ref *pSender);

	void complete1(HttpClient *client, HttpResponse *response);

	void goback(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Register);
};

#endif // __REGISTER_H__