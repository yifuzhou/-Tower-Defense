#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite1 = Sprite::create("background.png");
	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite1, 0);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	auto sprite_Logo = Sprite::createWithSpriteFrameName("logo.png");
	auto start_button = Sprite::createWithSpriteFrameName("menu_startchain_0002.png");
	Size size = start_button->getContentSize();
	start_button->setPosition(Vec2(sprite_Logo->getContentSize().width / 2, 0 -size.height/9));
	sprite_Logo->addChild(start_button, -1);

	sprite_Logo->setScale(0.2f);

	sprite_Logo->setPosition(Point(visibleSize.width / 2, visibleSize.height - (sprite_Logo->getContentSize().height / 2)));
	addChild(sprite_Logo, 1);
	ScaleTo * scaleto = ScaleTo::create(0.5, 1.1, 1.1);
	sprite_Logo->runAction(scaleto);

	auto sprite = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");

	sprite->setPosition(Point(visibleSize.width / 2, visibleSize.height - (sprite_Logo->getContentSize().height / 2)));

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> aFrames(20);

	for (int len = 1; len <= 21; len++)
	{
		frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("logo_brillo_00%02d.png", len)->getCString());
		if (frame != nullptr)
			aFrames.pushBack(frame);
	}
	addChild(sprite, 2);
	auto animation = Animation::createWithSpriteFrames(aFrames, 0.1f);

	sprite->runAction(RepeatForever::create(Animate::create(animation)));

	//add listener when click start
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchToStart, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority
		(listener, this);


	/*auto listen_start = EventListenerTouchOneByOne::create();
	Rect rect = Rect(0 + 40, 0 + 30, size.width - 80, size.height / 3 + 15);
	listen_start->onTouchBegan = [rect, this](Touch* t, Event* e)
	{
		log("click!");
		if (rect.containsPoint(t->getLocation()))
		{
			log("click in area");
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, Register::createScene()));
		}
			
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_start, rect);

		*/

    return true;
}


bool HelloWorld::touchToStart(Touch*touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//log("x is %f; y is %f", locationInNode.x, locationInNode.y);
	Rect rect = Rect(visibleSize.width/2.7, visibleSize.height/18, visibleSize.width/4, visibleSize.height/5.5);
	
	if (rect.containsPoint(locationInNode))
	{ 
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, Welcome::createScene()));
		return true;
	}
	return false;

}
