#include "CreateJoin.h"

Scene* CreateJoin::createScene()
{
	auto scene = Scene::create();
	auto layer = CreateJoin::create();
	scene->addChild(layer);
	return scene;
}

bool  CreateJoin::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("doubleSelect.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);

	auto lblCreate = Label::createWithSystemFont("Create My Game", "Arial", 36.f);
	lblCreate->setColor(Color3B::BLACK);
	auto menuServer = MenuItemLabel::create(lblCreate, CC_CALLBACK_1(CreateJoin::CreateRoom, this));
	menuServer->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.6));

	auto lblJoin = Label::createWithSystemFont("Choose A Game to Join", "Arial", 36.f);
	lblJoin->setColor(Color3B::BLACK);
	auto menuClient = MenuItemLabel::create(lblJoin, CC_CALLBACK_1(CreateJoin::JoinGame, this));
	menuClient->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.3));

	auto menu = Menu::create(menuServer, menuClient, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

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

	return true;
}

void CreateJoin::CreateRoom(Ref* sender)
{
	auto scene = DoubleGameScene::createScene(NICKNAME,1);
	Director::getInstance()->replaceScene(scene);
}

void CreateJoin::JoinGame(Ref* sender)
{
	auto scene = ChooseIP::createScene();
	Director::getInstance()->replaceScene(scene);
}
