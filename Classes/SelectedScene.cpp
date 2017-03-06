#include"SelectedScene.h"

Scene* SelectedScene::createScene()
{
	auto s = Scene::create();
	auto l = SelectedScene::create();
	s->addChild(l);
	return s;

}

bool SelectedScene::init()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("registerbackground.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);
	
	auto back = Sprite::create("Back_Arrow.png");
	back->setPosition(visibleSize.width / 5, visibleSize.height / 8);
	back->setScale(0.5);
	addChild(back);
	auto listen_b = EventListenerTouchOneByOne::create();
	listen_b->onTouchBegan = [back, this](Touch* t, Event* e)
	{
		if (back->getBoundingBox().containsPoint(t->getLocation()))
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, HomeScene::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_b, back);

	addLevelFlag(LEVELLOCK);
	return true;
}

void SelectedScene::addLevelFlag(int i)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (i >= 1)
	{
		Sprite* flag;
		if (i == 1)
			flag = Sprite::create("level.png");
		else
			flag = Sprite::create("levelPass.png");

		flag->setPosition(Point(visibleSize.width*0.44, visibleSize.height*0.5));
		flag->setScale(0.6);
		addChild(flag);
		flag->runAction(MoveBy::create(1, Point(0, -visibleSize.height*0.2)));

		auto listen_f = EventListenerTouchOneByOne::create();
		listen_f->onTouchBegan = [flag, this](Touch* t, Event* e)
		{
			if (flag->getBoundingBox().containsPoint(t->getLocation()))
				popUp(1);
			return true;
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_f, flag);
	}
	if (i >= 2)
	{
		Sprite* flag;
		if (i == 2)
			flag = Sprite::create("level.png");
		else
			flag = Sprite::create("levelPass.png");
		flag->setPosition(Point(visibleSize.width*0.36, visibleSize.height*0.67));
		flag->setScale(0.6);
		
		addChild(flag);
		flag->runAction(MoveBy::create(1, Point(0, -visibleSize.height*0.2)));
		auto listen_f = EventListenerTouchOneByOne::create();
		listen_f->onTouchBegan = [flag, this](Touch* t, Event* e)
		{
			if (flag->getBoundingBox().containsPoint(t->getLocation()))
				popUp(2);
			return true;
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_f, flag);
	}
	if (i >= 3)
	{
		Sprite* flag;
		if (i == 3)
			flag = Sprite::create("level.png");
		else
			flag = Sprite::create("levelPass.png");
		flag->setPosition(Point(visibleSize.width*0.41, visibleSize.height*0.8));
		flag->setScale(0.6);

		addChild(flag);
		flag->runAction(MoveBy::create(1, Point(0, -visibleSize.height*0.2)));
		auto listen_f = EventListenerTouchOneByOne::create();
		listen_f->onTouchBegan = [flag, this](Touch* t, Event* e)
		{
			if (flag->getBoundingBox().containsPoint(t->getLocation()))
				popUp(3);
			return true;
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_f, flag);
	}
	if (i >= 4)
	{
		Sprite* flag;
		if (i == 4)
			flag = Sprite::create("level.png");
		else
			flag = Sprite::create("levelPass.png");
		flag->setPosition(Point(visibleSize.width*0.3, visibleSize.height*0.92));
		flag->setScale(0.6);

		addChild(flag);
		flag->runAction(MoveBy::create(1, Point(0, -visibleSize.height*0.2)));
		auto listen_f = EventListenerTouchOneByOne::create();
		listen_f->onTouchBegan = [flag, this](Touch* t, Event* e)
		{
			if (flag->getBoundingBox().containsPoint(t->getLocation()))
				popUp(4);
			return true;
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_f, flag);
	}
	
}

void SelectedScene::popUp(int i)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	//this is the board picture
	auto announcement = Sprite::createWithSpriteFrameName("mainmenu_saveslot_0001.png");
	auto confirm = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png");
	auto _delete = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png");
	Sprite* selectMap;
	if (i == 1)
		selectMap = Sprite::create("map_selected1.png");
	else if (i == 2)
		selectMap = Sprite::create("map_selected2.png");
	else if (i == 3)
		selectMap = Sprite::create("map_selected3.png");
	else
		selectMap = Sprite::create("map_selected4.png");
	selectMap->setPosition(Point(announcement->getContentSize().width / 3.5, announcement->getContentSize().height / 2));
	selectMap->setScale(0.4);
	confirm->setPosition(Point(announcement->getContentSize().width/1.5, announcement->getContentSize().height/5));
	confirm->setScale(0.7);
	_delete->setPosition(Point(announcement->getContentSize().width / 1.2, announcement->getContentSize().height / 5));
	_delete->setScale(0.7);
	
	announcement->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(announcement);
	announcement->addChild(confirm, 1);
	announcement->addChild(_delete, 1);
	announcement->addChild(selectMap, 1);
	announcement->setScale(0.2f);
	ScaleTo * scaleto = ScaleTo::create(0.6, 2, 2);
	announcement->runAction(scaleto);

	auto listen_confirm = EventListenerTouchOneByOne::create();
	listen_confirm->onTouchBegan = [confirm, i, this](Touch* t, Event* e)
	{
		auto target = static_cast<Sprite*>(e->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Rect rect = Rect(0, 0, confirm->getContentSize().width, confirm->getContentSize().height);

		if (rect.containsPoint(locationInNode))
		{
			if (i == 1)
				Director::getInstance()->replaceScene(TransitionFade::create(1, SingleGameScene::createScene()));
			else if (i==2)
				Director::getInstance()->replaceScene(TransitionFade::create(1, SingleGameScene2::createScene()));
			else if (i == 3)
				Director::getInstance()->replaceScene(TransitionFade::create(1, SingleGameScene3::createScene()));
			else
				Director::getInstance()->replaceScene(TransitionFade::create(1, SingleGameScene4::createScene()));
			return true;
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_confirm, confirm);

	auto listen_delete = EventListenerTouchOneByOne::create();
	listen_delete->onTouchBegan = [_delete, announcement, i, this](Touch* t, Event* e)
	{
		auto target = static_cast<Sprite*>(e->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Rect rect = Rect(0, 0, _delete->getContentSize().width, _delete->getContentSize().height);

		if (rect.containsPoint(locationInNode))
		{
			announcement->removeFromParentAndCleanup(true);
			return true;
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_delete, _delete);

	
}