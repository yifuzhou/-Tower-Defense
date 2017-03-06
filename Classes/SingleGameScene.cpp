#include"SingleGameScene.h"
#include "HelloWorldScene.h"

Scene* SingleGameScene::createScene()
{
	auto s = Scene::create();
	auto l = SingleGameScene::create();
	s->addChild(l);
	return s;

}

bool SingleGameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = Sprite::create("map_level_1.png");
	map->setPosition(visibleSize.width / 2, visibleSize.height /2);
	addChild(map);
	/*
	auto label = Label::createWithTTF("This is Single Game", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);
	*/

	//****************************
	scoreboard = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	scoreboard->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - scoreboard->getContentSize().height));
	this->addChild(scoreboard, 3); //highest Z-Coordinate level


	HP = Label::createWithTTF("HP: 3", "fonts/Marker Felt.ttf", 24);


	HP->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100,
		origin.y + visibleSize.height - HP->getContentSize().height));
	//HP->setScale(initScale);
	this->addChild(HP, 3);

	GOLD = Label::createWithTTF("GOLD: 0", "fonts/Marker Felt.ttf", 24);


	GOLD->setPosition(Vec2(origin.x + visibleSize.width / 2 - 200,
		origin.y + visibleSize.height - GOLD->getContentSize().height));
	//GOLD->setScale(initScale);
	this->addChild(GOLD, 3);


	ntimeboard = Label::createWithTTF("3", "fonts/Marker Felt.ttf", 88);

	ntimeboard->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - ntimeboard->getContentSize().height -150));
	//GOLD->setScale(initScale);
	this->addChild(ntimeboard, 3);

	gameover = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 150);

	gameover->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - gameover->getContentSize().height - 150));
	//GOLD->setScale(initScale);
	this->addChild(gameover, 3);
	gameover->setVisible(false);

	winninggame = Label::createWithTTF("WIN !!!", "fonts/Marker Felt.ttf", 150);

	winninggame->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - winninggame->getContentSize().height - 150));
	//GOLD->setScale(initScale);
	this->addChild(winninggame, 3);
	winninggame->setVisible(false);

	waveboard = Label::createWithTTF("Wave: 1", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	waveboard->setPosition(Vec2(origin.x + visibleSize.width / 2 + 400,
		origin.y + visibleSize.height - waveboard->getContentSize().height));
	this->addChild(waveboard, 3); //highest Z-Coordinate level


	//*********************************
	addBase();
	addField();

	//add the menu button
	auto menuitem = MenuItemImage::create(
		"option.png",
		"option.png",
		CC_CALLBACK_1(SingleGameScene::menuCloseCallback, this));

	menuitem->setPosition(Vec2(origin.x + visibleSize.width - menuitem->getContentSize().width / 2,
		origin.y + menuitem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	//add the magic button
	/**
	auto magicitem = MenuItemImage::create(
		"magicbutton.png",
		"magicbutton.png",
		CC_CALLBACK_1(SingleGameScene::magic, this));

	magicitem->setPosition(Vec2(origin.x + magicitem->getContentSize().width / 2,
		origin.y + magicitem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto magicbutton = Menu::create(magicitem, NULL);
	magicbutton->setPosition(Vec2::ZERO);
	this->addChild(magicbutton, 2);
	*/
	auto magicitem = MenuItemImage::create(
		"magicbutton.png",
		"magicbutton.png",
		CC_CALLBACK_1(SingleGameScene::magic, this));

	magicitem->setPosition(Vec2(origin.x + magicitem->getContentSize().width / 2, origin.y + magicitem->getContentSize().height / 2));
	// create menu, it's an autorelease object
	auto magicbutton = Menu::create(magicitem, NULL);
	magicbutton->setPosition(Vec2::ZERO);
	this->addChild(magicbutton, 2);


	auto listener123 = EventListenerTouchOneByOne::create();

	listener123->setSwallowTouches(true);
	listener123->onTouchBegan = CC_CALLBACK_2(SingleGameScene::touchToBuild, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority
	(listener123, this);

	resetFrames(group);
	scheduleUpdate();
	return true;
}

bool SingleGameScene::touchToBuild(Touch*touch, Event* event)
{
	//log("hereherehrhehrehrehr");
	if (!hascircle) {
		int sizeofTower = towerVector.size();
		tower * tow;
		for (int i = sizeofTower - 1; i >= 0; i--)
		{
			tow = towerVector.at(i);
			auto tower_sprite = tow->getSprite();
			if (tower_sprite->getBoundingBox().containsPoint(touch->getLocation()))
			{
				hascircle = true;
				upgradeTower(tow, tower_sprite->getPositionX(), tower_sprite->getPositionY());
			}
		}
	}
	return true;
}

void SingleGameScene::towerAttack()
{
	int soldierSize = soldierVector.size();
	int towerSize = towerVector.size();
	for (int i = 0; i < soldierSize; i++)
	{
		//int hurt = 0;
		//Vector<Monster*> saveAttackingSoldier;
		for (int j = 0; j < towerSize; j++)
		{
			float range = towerVector.at(j)->range;
			float p_m_x = soldierVector.at(i)->getCurrentX();
			float p_m_y = soldierVector.at(i)->getCurrentY();
			float p_t_x = towerVector.at(j)->p_x;
			float p_t_y = towerVector.at(j)->p_y;
			float dis = sqrt((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y));
			if ((dis <= range)&&(towerVector.at(j)->startAttack))
			{
				if (p_m_x - p_t_x >= 0)
				{
					towerVector.at(j)->sprite_tower->setFlippedX(false);
				}
				else
				{
					towerVector.at(j)->sprite_tower->setFlippedX(true);
				}
				int type = towerVector.at(j)->tower_type;
				auto bullet = bullet::create(towerVector.at(j), soldierVector.at(i), 1, type);
				addChild(bullet, 3);
				towerVector.at(j)->startAttack = false;
			}
		}
	}
}

void SingleGameScene::monsterAttack()
{
	int soldierSize = soldierVector.size();
	int towerSize = towerVector.size();
	for (int j = 0; j < towerSize; j++)
	{
		int hurt = 0;
		Vector<Monster*> saveAttackingSoldier;
		for (int i = 0; i < soldierSize; i++)
		{
				float range = soldierVector.at(i)->AttackRange;
				float p_m_x = soldierVector.at(i)->getCurrentX();
				float p_m_y = soldierVector.at(i)->getCurrentY();
				float p_t_x = towerVector.at(j)->p_x;
				float p_t_y = towerVector.at(j)->p_y;
				if ((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y) <= range * range)
				{
					soldierVector.at(i)->stopAndAttack = true;
					hurt = hurt + soldierVector.at(i)->hurtVar;
					saveAttackingSoldier.pushBack(soldierVector.at(i));
				}
				else
				{
					soldierVector.at(i)->stopAndAttack = false;
					//towerVector.at(j)->stopAttack();
				}
		}
		towerVector.at(j)->isAttackedFun(hurt);
		if (towerVector.at(j)->isDead())
		{

			int size = saveAttackingSoldier.size();
			for (int m = 0; m < size; m++)
				saveAttackingSoldier.at(m)->stopAndAttack = false;
		}
	}
}

void SingleGameScene::upgradeTower(tower *tow, float position_x, float position_y) {
	if (!menuopened && !gameisover) {
		auto circle = Sprite::create("circle.png");
		circle->setScale(0.4);
		circle->setPosition(Vec2(position_x, position_y));
		addChild(circle, 2);

		Size circlesize = circle->getContentSize();

		auto trade = Sprite::create("trade.png");
		trade->setScale(0.8);
		trade->setPosition(Vec2(position_x - circlesize.width / 6, position_y));

		addChild(trade, 3);

		auto upgradebuild = Sprite::create("upgrade.png");
		upgradebuild->setScale(0.8);
		upgradebuild->setPosition(Vec2(position_x + circlesize.width / 6, position_y));

		addChild(upgradebuild, 3);

		auto listen_trade = EventListenerTouchOneByOne::create();
		listen_trade->onTouchBegan = [trade, position_x, position_y, circle, tow, upgradebuild, this](Touch* t, Event* e)
		{
			if (trade->getBoundingBox().containsPoint(t->getLocation()))
			{

				trade->removeFromParent();
				circle->removeFromParent();
				upgradebuild->removeFromParent();
				tow->Blood = 0;
				updateGold(+10);
				hascircle = false;
				return true;
			}
			else {
				upgradebuild->removeFromParent();
				circle->removeFromParent();
				trade->removeFromParent();
				hascircle = false;

				return false;
			}
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_trade, trade);


		auto listen_upgrade = EventListenerTouchOneByOne::create();
		listen_upgrade->onTouchBegan = [trade, position_x, position_y, circle, upgradebuild, tow, this](Touch* t, Event* e)
		{
			if (upgradebuild->getBoundingBox().containsPoint(t->getLocation()) && gold >= 10)
			{
				trade->removeFromParent();
				circle->removeFromParent();
				hascircle = false;
				upgradebuild->removeFromParent();
				if (gold >= 10) {
					updateGold(-10);
					tow->upgrade();
				}
				return true;
			}

		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_upgrade, upgradebuild);
		//t->upgrade();

	}

}

bool SingleGameScene::buildtower(float position_x, float position_y, Sprite* field, int place)
{
	if (!menuopened && !gameisover) {
		int f_place = place;
		//Size visibleSize = Director::getInstance()->getVisibleSize();
		auto circle = Sprite::create("circle.png");
		circle->setScale(0.4);
		circle->setPosition(Vec2(position_x, position_y));
		addChild(circle, 2);

		Size circlesize = circle->getContentSize();

		auto boombuild = Sprite::create("boombuild.png");
		boombuild->setScale(0.3);
		boombuild->setPosition(Vec2(position_x - circlesize.width / 6, position_y));

		addChild(boombuild, 3);

		auto freezebuild = Sprite::create("freezebuild.png");
		freezebuild->setScale(0.53);
		freezebuild->setPosition(Vec2(position_x + circlesize.width / 6, position_y));

		addChild(freezebuild, 3);

		auto normalbuild = Sprite::create("normalbuild.png");
		normalbuild->setScale(0.3);
		normalbuild->setPosition(Vec2(position_x, position_y - circlesize.height / 6));

		addChild(normalbuild, 3);

		auto listen_boombuild = EventListenerTouchOneByOne::create();
		listen_boombuild->onTouchBegan = [boombuild, position_x, position_y, normalbuild, freezebuild, circle, field, f_place, this](Touch* t, Event* e)
		{
			if (boombuild->getBoundingBox().containsPoint(t->getLocation()) && gold >= 10)
			{
				auto towe = tower::create(position_x, position_y, 1, 1, f_place);
				addChild(towe, 2);
				towerVector.pushBack(towe);

				normalbuild->removeFromParent();
				freezebuild->removeFromParent();
				circle->removeFromParent();
				boombuild->removeFromParent();
				field->removeFromParent();
				updateGold(-10);
				return true;
			}
			else {
				normalbuild->removeFromParent();
				freezebuild->removeFromParent();
				circle->removeFromParent();
				boombuild->removeFromParent();
				return false;
			}
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_boombuild, boombuild);

		auto listen_normalbuild = EventListenerTouchOneByOne::create();
		listen_normalbuild->onTouchBegan = [boombuild, position_x, position_y, normalbuild, freezebuild, circle, field, f_place, this](Touch* t, Event* e)
		{
			if (normalbuild->getBoundingBox().containsPoint(t->getLocation()) && gold >= 10)
			{
				auto tower = tower::create(position_x, position_y, 1, 0, f_place);
				addChild(tower, 2);
				towerVector.pushBack(tower);

				normalbuild->removeFromParent();
				freezebuild->removeFromParent();
				circle->removeFromParent();
				boombuild->removeFromParent();
				field->removeFromParent();
				updateGold(-10);
				return true;
			}

		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_normalbuild, normalbuild);

		auto listen_freezebuild = EventListenerTouchOneByOne::create();
		listen_freezebuild->onTouchBegan = [boombuild, position_x, position_y, normalbuild, freezebuild, circle, field, f_place, this](Touch* t, Event* e)
		{
			if (freezebuild->getBoundingBox().containsPoint(t->getLocation()) && gold >= 10)
			{
				auto tower = tower::create(position_x, position_y, 1, 2, f_place);
				addChild(tower, 2);
				towerVector.pushBack(tower);

				normalbuild->removeFromParent();
				freezebuild->removeFromParent();
				circle->removeFromParent();
				boombuild->removeFromParent();
				field->removeFromParent();
				updateGold(-10);
				return true;
			}

		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_freezebuild, freezebuild);
	}
	return false;
}

void SingleGameScene::addField()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto field_1 = Sprite::create("field.png");
	field_1->setScale(0.7);
	field_1->setPosition(Point(visibleSize.width*0.36, visibleSize.height*0.93));
	addChild(field_1, 2);
	auto listen_f1 = EventListenerTouchOneByOne::create();
	listen_f1->onTouchBegan = [field_1, this](Touch* t, Event* e)
	{
		if (field_1->getBoundingBox().containsPoint(t->getLocation()))
		{
			bool build_success = buildtower(field_1->getPositionX(), field_1->getPositionY(), field_1, 0);

			/**
			auto tower = tower::create(field_1->getPositionX(), field_1->getPositionY(), 1);
			addChild(tower, 2);
			field_1->removeFromParent();
			towerVector.pushBack(tower);
			*/
		}
		return true;
	};

	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f1, field_1);

	auto field_2 = Sprite::create("field.png");
	field_2->setScale(0.7);
	field_2->setPosition(Point(visibleSize.width*0.44, visibleSize.height*0.66));
	addChild(field_2, 2);
	auto listen_f2 = EventListenerTouchOneByOne::create();
	listen_f2->onTouchBegan = [field_2, this](Touch* t, Event* e)
	{
		if (field_2->getBoundingBox().containsPoint(t->getLocation()))
		{

			bool build_success = buildtower(field_2->getPositionX(), field_2->getPositionY(), field_2, 1);

		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f2, field_2);

	auto field_3 = Sprite::create("field.png");
	field_3->setScale(0.7);
	field_3->setPosition(Point(visibleSize.width*0.33, visibleSize.height*0.66));
	addChild(field_3, 2);
	auto listen_f3 = EventListenerTouchOneByOne::create();
	listen_f3->onTouchBegan = [field_3, this](Touch* t, Event* e)
	{
		if (field_3->getBoundingBox().containsPoint(t->getLocation()))
		{

			bool build_success = buildtower(field_3->getPositionX(), field_3->getPositionY(), field_3, 2);

		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f3, field_3);

	auto field_4 = Sprite::create("field.png");
	field_4->setScale(0.7);
	field_4->setPosition(Point(visibleSize.width*0.22, visibleSize.height*0.66));
	addChild(field_4, 2);
	auto listen_f4 = EventListenerTouchOneByOne::create();
	listen_f4->onTouchBegan = [field_4, this](Touch* t, Event* e)
	{
		if (field_4->getBoundingBox().containsPoint(t->getLocation()))
		{

			bool build_success = buildtower(field_4->getPositionX(), field_4->getPositionY(), field_4, 3);

		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f4, field_4);


	auto field_5 = Sprite::create("field.png");
	field_5->setScale(0.7);
	field_5->setPosition(Point(visibleSize.width*0.74, visibleSize.height*0.3));
	addChild(field_5, 2);
	auto listen_f5 = EventListenerTouchOneByOne::create();
	listen_f5->onTouchBegan = [field_5, this](Touch* t, Event* e)
	{
		if (field_5->getBoundingBox().containsPoint(t->getLocation()))
		{

			bool build_success = buildtower(field_5->getPositionX(), field_5->getPositionY(), field_5, 4);

		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f5, field_5);

	auto field_6 = Sprite::create("field.png");
	field_6->setScale(0.7);
	field_6->setPosition(Point(visibleSize.width*0.19, visibleSize.height*0.18));
	addChild(field_6, 2);
	auto listen_f6 = EventListenerTouchOneByOne::create();
	listen_f6->onTouchBegan = [field_6, this](Touch* t, Event* e)
	{
		if (field_6->getBoundingBox().containsPoint(t->getLocation()))
		{

			bool build_success = buildtower(field_6->getPositionX(), field_6->getPositionY(), field_6, 5);

		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f6, field_6);

	auto field_7 = Sprite::create("field.png");
	field_7->setScale(0.7);
	field_7->setPosition(Point(visibleSize.width*0.72, visibleSize.height*0.67));
	addChild(field_7, 2);
	auto listen_f7 = EventListenerTouchOneByOne::create();
	listen_f7->onTouchBegan = [field_7, this](Touch* t, Event* e)
	{
		if (field_7->getBoundingBox().containsPoint(t->getLocation()))
		{

			bool build_success = buildtower(field_7->getPositionX(), field_7->getPositionY(), field_7, 6);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f7, field_7);

	auto field_8 = Sprite::create("field.png");
	field_8->setScale(0.7);
	field_8->setPosition(Point(visibleSize.width*0.59, visibleSize.height*0.48));
	addChild(field_8, 2);
	auto listen_f8 = EventListenerTouchOneByOne::create();
	listen_f8->onTouchBegan = [field_8, this](Touch* t, Event* e)
	{
		if (field_8->getBoundingBox().containsPoint(t->getLocation()))
		{
			
			bool build_success = buildtower(field_8->getPositionX(), field_8->getPositionY(), field_8, 7);

		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f8, field_8);
}



void SingleGameScene::addBase()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite *sprite_base = Sprite::create("Base_00.png");
	this->addChild(sprite_base, 0);
	sprite_base->setPosition(ccp(visibleSize.width / 1.46f, visibleSize.height / 1.09f));

	Animation* animation_base = Animation::create();
	for (int i = 1; i <= 20; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "Base_%02d.png", i % 4);
		animation_base->addSpriteFrameWithFileName(szName);
	}
	animation_base->setDelayPerUnit(2.8f / 14.0f);
	animation_base->setRestoreOriginalFrame(true); 
	Animate *animate_base = Animate::create(animation_base);
	sprite_base->runAction(RepeatForever::create(dynamic_cast<ActionInterval *>(Sequence::create(animate_base, NULL))));

}
void SingleGameScene::addSoldiers(int speed)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int t_path = d_path % 3;
	d_path++;


	int m_type;
	if (group<12) {
		m_type = group % 6;
	}
	else
	{
		m_type = 7;
	}

	auto soldiers = Monster::create(speed, visibleSize.width / 2, visibleSize.height / 2, 1, t_path, m_type, 1);
	addChild(soldiers, 1);
	soldierVector.pushBack(soldiers);
}



void SingleGameScene::resetFrames(int a)
{
	currentFrameIndex = -180;
	limitFrameIndex = 60;
	wait = false;
	counter = 0;
	d_path = 0;
}

void SingleGameScene::update(float dt)
{
	currentFrameIndex++;
	monsterAttack();
	towerAttack();



	if (currentFrameIndex%60==0&&ntime>0)
	{
		ntime--;
		sprintf(ntimearr, "%d", ntime);
		ntimeboard->setString(ntimearr);
		ntimeboard->setVisible(true);


	}

	
	
	if(ntime==0)
	{
		ntimeboard->setVisible(false);
	}

	if (hitpoint==0)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		gameover->setVisible(true);
		gameisover = true;
		auto quititem = MenuItemImage::create(
			"quitgame.png",
			"quitgame.png",
			CC_CALLBACK_1(SingleGameScene::quitgamescene, this));

		quititem->setPosition(Vec2(origin.x + visibleSize.width - quititem->getContentSize().width / 2,
			origin.y + quititem->getContentSize().height / 2+500));

		// create menu, it's an autorelease object
		auto quitgame = Menu::create(quititem, NULL);
		quitgame->setPosition(Vec2::ZERO);
		this->addChild(quitgame, 4);
		
	}

	//if (currentFrameIndex >= nextFrameCout)
	if (currentFrameIndex>=0 && currentFrameIndex % limitFrameIndex == 0&&!wait)
	{
		addSoldiers(group);

		// update wave label
		wave = group;
		sprintf(wavearr, "Wave: %d", wave);
		waveboard->setString(wavearr);
		waveboard->setVisible(true);

		counter++;
		if (counter == (9 + 2*group))
			wait = true;
	}

	

	if (currentFrameIndex >= 60 * 1 / dt - 10 * (group - 1))
	{

		//win the game if after level 2
		if (group == 12)
		{
			letswin();
		}
		else
		{
			resetFrames(group++);
		}
		
	}
			

		
	//update the vector if the bullet is scope damage
	int size_z = soldierVector.size();
	for (int i = size_z - 1; i >= 0; i--)
	{
		if (soldierVector.at(i)->scope) {
			float p_m_x = soldierVector.at(i)->getCurrentX();
			float p_m_y = soldierVector.at(i)->getCurrentY();
			//add the build animation
			Sprite *sprite_cyclone = Sprite::create("boom_00.png");
			this->addChild(sprite_cyclone, 3);

			sprite_cyclone->setPosition(Vec2(p_m_x, p_m_y));

			Animation* animation_cyclone = Animation::create();
			for (int i = 0; i <= 3; i++)
			{
				char szName[100] = { 0 };
				sprintf(szName, "boom_%02d.png", i % 3);
				animation_cyclone->addSpriteFrameWithFileName(szName);
			}
			animation_cyclone->setDelayPerUnit(2.8f / 15.0f);
			animation_cyclone->setRestoreOriginalFrame(true);
			Animate *animate_cyclone = Animate::create(animation_cyclone);

			sprite_cyclone->runAction(CCSequence::create(animate_cyclone, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sprite_cyclone)), NULL));

			//hurt surrounding monster;
			
			for (int j = size_z - 1; j >= 0; j--) {
				if (j != i) {
					float p_t_x = soldierVector.at(j)->getCurrentX();
					float p_t_y = soldierVector.at(j)->getCurrentY();
					if ((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y) <= 70 * 70) {
						soldierVector.at(j)->getHurt(50);
					}
				}
			}

			soldierVector.at(i)->scope = false;
		}	
	}

	//**********************
	//Update gold every second(60 frames)

	if (currentFrameIndex % 60 == 59)//so first frame wont add gold
	{
		updateGold(1);
	}
	//update HP when a monster escape out
	int size_o = soldierVector.size();
	for (int i = size_o - 1; i >= 0; i--)
	{
		if (soldierVector.at(i)->isOut)
		{
			soldierVector.erase(i);
			hitpoint--;
			if (hitpoint >= 0)
			{
				sprintf(hitpointarr, "HP: %d", hitpoint);
				HP->setString(hitpointarr);
				HP->setVisible(true);
			}
		}
	}

	//**********************


	//Update the Vector if some monsters die
	int size_m = soldierVector.size();
	for (int i = size_m - 1; i >= 0; i--)
	{
		if (soldierVector.at(i)->isDead() && !soldierVector.at(i)->isOut)
		{
			//update score
			score++;
			sprintf(scorearr, "Score: %d", score);
			scoreboard->setString(scorearr);
			scoreboard->setVisible(true);

			//update gold
			
			updateGold(soldierVector.at(i)->getGoldBonus());

			soldierVector.erase(i);


		}
			
	}
	

	//Update the Vector if some tower die
	int size_t = towerVector.size();
	for (int i = size_t - 1; i >= 0; i--)
	{
		if (towerVector.at(i)->isDead())
			towerVector.erase(i);
	}
}

void SingleGameScene::updateGold(int different)
{
	gold+= different;
	sprintf(goldarr, "GOLD: %d", gold);
	GOLD->setString(goldarr);
	GOLD->setVisible(true);

}

void SingleGameScene::magic(cocos2d::Ref * pSender) {
	if (!menuopened&&!magicused&&!gameisover) {
		magicused = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto feiji = Sprite::create("dragon_00.png");
		feiji->setPosition(0, visibleSize.height / 2);
		//feiji->runAction(Sequence::create(MoveBy::create(2, Point(visibleSize.width, visibleSize.height / 2)), NULL));
		feiji->setScale(1);
		addChild(feiji,6);
		//feiji->runAction(Sequence::create(MoveBy::create(4, Point(visibleSize.width+300, visibleSize.height / 2)), NULL));
		//Sequence action = Sequence::create(MoveBy::create(2, Point(visibleSize.width, visibleSize.height / 2)), NULL);

		Animation* animation_cyclone = Animation::create();
		for (int i = 0; i <= 3; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "dragon_%02d.png", i % 11);
			animation_cyclone->addSpriteFrameWithFileName(szName);
		}
		animation_cyclone->setDelayPerUnit(2.8f / 15.0f);
		animation_cyclone->setRestoreOriginalFrame(true);
		Animate *animate_cyclone = Animate::create(animation_cyclone);
		feiji->runAction(RepeatForever::create(dynamic_cast<ActionInterval *>(Sequence::create(animate_cyclone, NULL))));

		feiji->runAction(Sequence::create(MoveBy::create(3, Point(visibleSize.width+200, visibleSize.height / 2)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, feiji)), NULL));

		//clear monster
		int size_m = soldierVector.size();
		for (int i = size_m - 1; i >= 0; i--)
		{
			soldierVector.at(i)->getHurt(70);
		}
	}
}

void SingleGameScene::letswin()
{
	winninggame->setVisible(true);

	unscheduleUpdate();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//win this game
	gameisover = true;
	auto quititem = MenuItemImage::create(
		"quitgame.png",
		"quitgame.png",
		CC_CALLBACK_1(SingleGameScene::quitgamescene, this));

	quititem->setPosition(Vec2(origin.x + visibleSize.width - quititem->getContentSize().width / 2,
		origin.y + quititem->getContentSize().height / 2 + 500));

	// create menu, it's an autorelease object
	auto quitgame = Menu::create(quititem, NULL);
	quitgame->setPosition(Vec2::ZERO);
	this->addChild(quitgame, 4);
}

void SingleGameScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	if (!menuopened&&!gameisover) {
		menuopened = true;

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite * background = CCSprite::create("popbackground.png");
		background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->addChild(background,4);
		CCSize contentSize = background->getContentSize();

		auto label = Label::createWithTTF("Game Menu", "fonts/Marker Felt.ttf", 22);
		label->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 70));
		this->addChild(label, 5);

		CCSprite * returned = CCSprite::create("return.png");
		returned->setPosition(Vec2(winSize.width / 2, winSize.height / 2+20));
		this->addChild(returned, 5);

		CCSprite * quit = CCSprite::create("quit.png");
		quit->setPosition(Vec2(winSize.width / 2, winSize.height / 2-20));
		this->addChild(quit, 5);

		auto listen_return = EventListenerTouchOneByOne::create();
		listen_return->onTouchBegan = [returned, background, label, quit, this](Touch* t, Event* e)
		{
			if (returned->getBoundingBox().containsPoint(t->getLocation()))
			{
				returned->removeFromParentAndCleanup(true);
				background->removeFromParentAndCleanup(true);
				label->removeFromParentAndCleanup(true);
				quit->removeFromParentAndCleanup(true);
				menuopened = false;
			}
			return true;
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_return, returned);

		auto listen_quit = EventListenerTouchOneByOne::create();
		listen_quit->onTouchBegan = [returned, background, label, quit, this](Touch* t, Event* e)
		{
			if (quit->getBoundingBox().containsPoint(t->getLocation()))
			{
				auto scene = HelloWorld::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
			}
			return true;
		};
		Director::getInstance()->getEventDispatcher()->
			addEventListenerWithSceneGraphPriority(listen_quit, quit);

	}
}
void SingleGameScene::quitgamescene(cocos2d::Ref * pSender) 
{
	auto request = new cocos2d::network::HttpRequest();
	request->setTag("type is post");
	request->setUrl("10.25.70.125/updatescore.php");
	//Set request type
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);

	// adjust data form to be receivable to server
	std::string conc = "userID=" + std::to_string(USERID) + "&userscore" + std::to_string(LEVELLOCK+1);
	__String *toSend = __String::create(conc);
	request->setRequestData(toSend->getCString(), toSend->length());
	//request->setResponseCallback(CC_CALLBACK_2(DoubleGameScene::POSTcompleted, this));

	//Create a client instance to send the request
	auto client = cocos2d::network::HttpClient::getInstance();
	client->setTimeoutForConnect(10);
	client->send(request);
	request->release();
	auto scene = HomeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}