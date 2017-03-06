#include"HomeScene.h"

Scene* HomeScene::createScene()
{
	auto s = Scene::create();
	auto l = HomeScene::create();
	s->addChild(l);
	return s;

}

bool HomeScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("registerbackground.png");
	bg->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
	this->addChild(bg, 0);
	auto User_Info = Sprite::create("button.png");
	User_Info->setPosition(2.5 * visibleSize.width / 5, 4 * visibleSize.height / 5);
	addChild(User_Info);
	auto UI_label = Label::create();
	UI_label->setString("User Information");
	UI_label->setColor(Color3B::WHITE);
	UI_label->setSystemFontSize(32);
	UI_label->setPosition(2.5 * visibleSize.width / 5, 4 * visibleSize.height / 5);
	addChild(UI_label,2);
	auto listen_UI = EventListenerTouchOneByOne::create();
	listen_UI->onTouchBegan = [UI_label, this](Touch* t, Event* e)
	{
		if (UI_label->getBoundingBox().containsPoint(t->getLocation()))
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, UserInfoScene::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_UI, UI_label);

	auto Single_Play = Sprite::create("button.png");
	Single_Play->setPosition(2.5 * visibleSize.width / 5, 3*visibleSize.height / 5);
	addChild(Single_Play);
	auto SP_label = Label::create();
	SP_label->setString("Single Play");
	SP_label->setColor(Color3B::WHITE);
	SP_label->setSystemFontSize(32);
	SP_label->setPosition(2.5 * visibleSize.width / 5, 3 * visibleSize.height / 5);
	addChild(SP_label, 2);
	auto listen_SP = EventListenerTouchOneByOne::create();
	listen_SP->onTouchBegan = [SP_label, this](Touch* t, Event* e)
	{
		if (SP_label->getBoundingBox().containsPoint(t->getLocation()))
			Director::getInstance()->replaceScene(TransitionFade::create(1, SelectedScene::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_SP, SP_label);

	auto pokemon = Sprite::create("button.png");
	pokemon->setPosition(2.5 * visibleSize.width / 5, 2*visibleSize.height / 5);
	addChild(pokemon);
	auto DP_label = Label::create();
	DP_label->setString("Double Play");
	DP_label->setColor(Color3B::WHITE);
	DP_label->setSystemFontSize(32);
	DP_label->setPosition(2.5 * visibleSize.width / 5, 2 * visibleSize.height / 5);
	addChild(DP_label);

	auto listen_DP = EventListenerTouchOneByOne::create();
	listen_DP->onTouchBegan = [DP_label, this](Touch* t, Event* e)
	{
		if (DP_label->getBoundingBox().containsPoint(t->getLocation()))
			Director::getInstance()->replaceScene(TransitionFade::create(1, CreateJoin::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_DP, DP_label);


	auto back = Sprite::create("Back_Arrow.png");
	back->setPosition( visibleSize.width / 5, visibleSize.height / 8);
	back->setScale(0.5);
	addChild(back);
	
	auto listen_b = EventListenerTouchOneByOne::create();
	listen_b->onTouchBegan = [back, this](Touch* t, Event* e)
	{
		if (back->getBoundingBox().containsPoint(t->getLocation()))
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, Welcome::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_b, back);

	
	return true;
}

