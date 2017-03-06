#include"DoubleGameScene.h"

std::string hostname;
bool HOST;
std::string IPaddress;

Scene* DoubleGameScene::createScene(std::string IPtoJoin, int isHost)
{
	if (isHost == 1)
	{
		HOST = true;
	}
	else
	{
		HOST = false;
		IPaddress = IPtoJoin;
		CCLOG("%s",IPaddress.c_str());
	}

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DoubleGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool DoubleGameScene::init()
{
	BUILD = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	H_X = 512;
	H_Y = 288;
	H_Scale = 1;

	G_X = 410;
	G_Y = 102;
	G_Scale = 0.3;

	isStart = false;

	if (HOST)
	{
		startServer();
		sendIP(NICKNAME);
	}
	else
	{
		startClient();
	}
	//create host map
	auto h_map = Sprite::create("map_level_1.png");
	h_map->setPosition(H_X, H_Y);
	h_map->setScale(H_Scale);
	addChild(h_map, 0);

	//create guest map
	auto g_map = Sprite::create("map_level_1.png");
	g_map->setPosition(G_X, G_Y);
	g_map->setScale(G_Scale);
	g_map->setOpacity(200);
	addChild(g_map, 3);

	addBase(G_X, G_Y, G_Scale);
	addBase(H_X, H_Y, H_Scale);

	addField();

	//add start button
	if (HOST)
	{
		auto startgame = MenuItemImage::create(
			"play_s.png",
			"play_s.png",
			CC_CALLBACK_1(DoubleGameScene::StartPlay, this));

		startgame->setPosition(Vec2(50, 500));
		auto menu = Menu::create(startgame, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);
	}

	auto quitGame = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(DoubleGameScene::BackToHome, this));
	quitGame->setPosition(Vec2(950, 500));
	auto M = Menu::create(quitGame, NULL);
	M->setPosition(Vec2::ZERO);
	this->addChild(M, 1);

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

	resetFrames(group);
	scheduleUpdate();
	return true;
}

/*
bool DoubleGameScene::touchToBuild(Touch*touch, Event* event)
{
	//log("hereherehrhehrehrehr");
	if (!hascircle) {
		int sizeofTower = HtowerVector.size();
		tower * tow;
		for (int i = sizeofTower - 1; i >= 0; i--)
		{
			tow = HtowerVector.at(i);
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
*/

void DoubleGameScene::guestMapBuildTower(float x, float y)
{
	//add in the G_Map
	float G_T_location_x = G_X + (x - H_X)*G_Scale;
	float G_T_location_y = G_Y + (y - H_Y)*G_Scale;

	Sprite *G_sprite_cyclone = Sprite::create("cyclone_00.png");
	G_sprite_cyclone->setPosition(Point(G_T_location_x, G_T_location_y));
	G_sprite_cyclone->setScale(G_Scale);
	addChild(G_sprite_cyclone, 5);
	Animation* G_animation_cyclone = Animation::create();
	for (int i = 0; i <= 3; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "cyclone_%02d.png", i % 4);
		G_animation_cyclone->addSpriteFrameWithFileName(szName);
	}
	G_animation_cyclone->setDelayPerUnit(2.8f / 15.0f);
	G_animation_cyclone->setRestoreOriginalFrame(true);
	Animate *G_animate_cyclone = Animate::create(G_animation_cyclone);

	G_sprite_cyclone->runAction(CCSequence::create(G_animate_cyclone, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, G_sprite_cyclone)), NULL));
	//log("In double:x is %f, y is %f", G_T_location_x, G_T_location_y);
	auto G_tower = tower::create(G_T_location_x, G_T_location_y, G_Scale,0,0);

	addChild(G_tower, 4);
	GtowerVector.pushBack(G_tower);
}


void DoubleGameScene::Host_towerAttack()
{
	int soldierSize = HsoldierVector.size();
	int towerSize = HtowerVector.size();
	for (int i = 0; i < soldierSize; i++)
	{
		//int hurt = 0;
		//Vector<Monster*> saveAttackingSoldier;
		for (int j = 0; j < towerSize; j++)
		{
			float range = HtowerVector.at(j)->range;
			float p_m_x = HsoldierVector.at(i)->getCurrentX();
			float p_m_y = HsoldierVector.at(i)->getCurrentY();
			float p_t_x = HtowerVector.at(j)->p_x;
			float p_t_y = HtowerVector.at(j)->p_y;
			float dis = sqrt((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y));
			if ((dis <= range) && (HtowerVector.at(j)->startAttack))
			{
				if (p_m_x - p_t_x >= 0)
				{
					HtowerVector.at(j)->sprite_tower->setFlippedX(false);
				}
				else
				{
					HtowerVector.at(j)->sprite_tower->setFlippedX(true);
				}
				auto bullet = bullet::create(HtowerVector.at(j), HsoldierVector.at(i), H_Scale, HtowerVector.at(j)->tower_type);
				addChild(bullet, 9);
				HtowerVector.at(j)->startAttack = false;
			}
		}
	}
}

void DoubleGameScene::Host_monsterAttack()
{
	int soldierSize = HsoldierVector.size();
	int towerSize = HtowerVector.size();
	for (int j = 0; j < towerSize; j++)
	{
		int hurt = 0;
		Vector<Monster*> saveAttackingSoldier;
		for (int i = 0; i < soldierSize; i++)
		{
			float range = HsoldierVector.at(i)->AttackRange;
			float p_m_x = HsoldierVector.at(i)->getCurrentX();
			float p_m_y = HsoldierVector.at(i)->getCurrentY();
			float p_t_x = HtowerVector.at(j)->p_x;
			float p_t_y = HtowerVector.at(j)->p_y;
			if ((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y) <= range * range)
			{
				HsoldierVector.at(i)->stopAndAttack = true;
				hurt = hurt + HsoldierVector.at(i)->hurtVar;
				saveAttackingSoldier.pushBack(HsoldierVector.at(i));
			}
			else
			{
				HsoldierVector.at(i)->stopAndAttack = false;
				//towerVector.at(j)->stopAttack();
			}
		}
		HtowerVector.at(j)->isAttackedFun(hurt);
		if (HtowerVector.at(j)->isDead())
		{

			int size = saveAttackingSoldier.size();
			for (int m = 0; m < size; m++)
				saveAttackingSoldier.at(m)->stopAndAttack = false;
		}
	}
}

void DoubleGameScene::Guest_towerAttack()
{
	int soldierSize = GsoldierVector.size();
	int towerSize = GtowerVector.size();
	for (int i = 0; i < soldierSize; i++)
	{
		for (int j = 0; j < towerSize; j++)
		{
			float range = (GtowerVector.at(j)->range)*G_Scale;
			float p_m_x = GsoldierVector.at(i)->getCurrentX();
			float p_m_y = GsoldierVector.at(i)->getCurrentY();
			float p_t_x = GtowerVector.at(j)->p_x;
			float p_t_y = GtowerVector.at(j)->p_y;
			float dis = sqrt((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y));
			if ((dis <= range) && (GtowerVector.at(j)->startAttack))
			{
				if (p_m_x - p_t_x >= 0)
				{
					GtowerVector.at(j)->sprite_tower->setFlippedX(false);
				}
				else
				{
					GtowerVector.at(j)->sprite_tower->setFlippedX(true);
				}
				//auto bullet = bullet::create(GtowerVector.at(j), GsoldierVector.at(i), G_Scale,);

				//addChild(bullet, 9);
				//GtowerVector.at(j)->startAttack = false;
			}
		}
	}
}

void DoubleGameScene::Guest_monsterAttack()
{
	int soldierSize = GsoldierVector.size();
	int towerSize = GtowerVector.size();
	for (int j = 0; j < towerSize; j++)
	{
		int hurt = 0;
		Vector<Monster*> saveAttackingSoldier;
		for (int i = 0; i < soldierSize; i++)
		{
			float range = (GsoldierVector.at(i)->AttackRange)*G_Scale;
			float p_m_x = GsoldierVector.at(i)->getCurrentX();
			float p_m_y = GsoldierVector.at(i)->getCurrentY();
			float p_t_x = GtowerVector.at(j)->p_x;
			float p_t_y = GtowerVector.at(j)->p_y;
			if ((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y) <= range * range)
			{
				GsoldierVector.at(i)->stopAndAttack = true;
				hurt = hurt + GsoldierVector.at(i)->hurtVar;
				saveAttackingSoldier.pushBack(GsoldierVector.at(i));
			}
			else
			{
				GsoldierVector.at(i)->stopAndAttack = false;
				//towerVector.at(j)->stopAttack();
			}
		}
		GtowerVector.at(j)->isAttackedFun(hurt);
		if (GtowerVector.at(j)->isDead())
		{

			int size = saveAttackingSoldier.size();
			for (int m = 0; m < size; m++)
				saveAttackingSoldier.at(m)->stopAndAttack = false;
		}
	}
}


void DoubleGameScene::addBase(float x, float y, float scale)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite *sprite_base = Sprite::create("Base_00.png");
	sprite_base->setScale(scale);
	if (scale != 1)
		this->addChild(sprite_base, 3);
	else
		this->addChild(sprite_base, 0);
	sprite_base->setPosition(ccp(scale*visibleSize.width / 1.46f + x - scale*visibleSize.width / 2,
		scale*visibleSize.height / 1.09f + y - scale*visibleSize.height / 2));

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

void DoubleGameScene::addField()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto field_0 = Sprite::create("field.png");
	field_0->setScale(0.7);
	field_0->setPosition(Point(visibleSize.width*0.59, visibleSize.height*0.48));
	fieldVector[0] = Point(visibleSize.width*0.59, visibleSize.height*0.48);
	addChild(field_0, 2);
	auto listen_f0 = EventListenerTouchOneByOne::create();
	listen_f0->onTouchBegan = [field_0, this](Touch* t, Event* e)
	{
		if (field_0->getBoundingBox().containsPoint(t->getLocation()))
		{

			auto tower = tower::create(field_0->getPositionX(), field_0->getPositionY(), 1, 0,0);
			if (HOST)
				serverSend("0 0");

			else
				clientSend("0 0");

			addChild(tower, 2);
			field_0->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f0, field_0);

	auto field_1 = Sprite::create("field.png");
	field_1->setScale(0.7);
	field_1->setPosition(Point(visibleSize.width*0.36, visibleSize.height*0.93));
	fieldVector[1] = Point(visibleSize.width*0.36, visibleSize.height*0.93);

	addChild(field_1, 2);
	auto listen_f1 = EventListenerTouchOneByOne::create();
	listen_f1->onTouchBegan = [field_1, this](Touch* t, Event* e)
	{
		if (field_1->getBoundingBox().containsPoint(t->getLocation()))
		{
			auto tower = tower::create(field_1->getPositionX(), field_1->getPositionY(), 1,0,1);
			if (HOST)
				serverSend("1 0");
			else
				clientSend("1 0");
			addChild(tower, 2);
			field_1->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f1, field_1);

	auto field_2 = Sprite::create("field.png");
	field_2->setScale(0.7);
	field_2->setPosition(Point(visibleSize.width*0.44, visibleSize.height*0.66));
	fieldVector[2] = Point(visibleSize.width*0.44, visibleSize.height*0.66);
	addChild(field_2, 2);
	auto listen_f2 = EventListenerTouchOneByOne::create();
	listen_f2->onTouchBegan = [field_2, this](Touch* t, Event* e)
	{
		if (field_2->getBoundingBox().containsPoint(t->getLocation()))
		{
			auto tower = tower::create(field_2->getPositionX(), field_2->getPositionY(), 1, 0, 2);
			if (HOST)
				serverSend("2 0");
			else
				clientSend("2 0");
			addChild(tower, 2);
			field_2->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f2, field_2);

	auto field_3 = Sprite::create("field.png");
	field_3->setScale(0.7);
	field_3->setPosition(Point(visibleSize.width*0.33, visibleSize.height*0.66));
	fieldVector[3] = Point(visibleSize.width*0.33, visibleSize.height*0.66);
	addChild(field_3, 2);
	auto listen_f3 = EventListenerTouchOneByOne::create();
	listen_f3->onTouchBegan = [field_3, this](Touch* t, Event* e)
	{
		if (field_3->getBoundingBox().containsPoint(t->getLocation()))
		{
			auto tower = tower::create(field_3->getPositionX(), field_3->getPositionY(), 1, 0, 3);
			if (HOST)
				serverSend("3 0");
			else
				clientSend("3 0");
			addChild(tower, 2);
			field_3->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f3, field_3);

	auto field_4 = Sprite::create("field.png");
	field_4->setScale(0.7);
	field_4->setPosition(Point(visibleSize.width*0.22, visibleSize.height*0.66));
	fieldVector[4] = Point(visibleSize.width*0.22, visibleSize.height*0.66);
	addChild(field_4, 2);
	auto listen_f4 = EventListenerTouchOneByOne::create();
	listen_f4->onTouchBegan = [field_4, this](Touch* t, Event* e)
	{
		if (field_4->getBoundingBox().containsPoint(t->getLocation()))
		{
			auto tower = tower::create(field_4->getPositionX(), field_4->getPositionY(), 1, 0, 4);
			if (HOST)
				serverSend("4 0");
			else
				clientSend("4 0");
			addChild(tower, 2);
			field_4->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f4, field_4);


	auto field_5 = Sprite::create("field.png");
	field_5->setScale(0.7);
	field_5->setPosition(Point(visibleSize.width*0.74, visibleSize.height*0.3));
	fieldVector[5] = Point(visibleSize.width*0.74, visibleSize.height*0.3);
	addChild(field_5, 2);
	auto listen_f5 = EventListenerTouchOneByOne::create();
	listen_f5->onTouchBegan = [field_5, this](Touch* t, Event* e)
	{
		if (field_5->getBoundingBox().containsPoint(t->getLocation()))
		{
			auto tower = tower::create(field_5->getPositionX(), field_5->getPositionY(), 1, 0, 5);
			if (HOST)
				serverSend("5 0");
			else
				clientSend("5 0");
			addChild(tower, 2);
			field_5->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f5, field_5);

	auto field_6 = Sprite::create("field.png");
	field_6->setScale(0.7);
	field_6->setPosition(Point(visibleSize.width*0.19, visibleSize.height*0.18));
	fieldVector[6] = Point(Point(visibleSize.width*0.19, visibleSize.height*0.18));
	addChild(field_6, 2);
	auto listen_f6 = EventListenerTouchOneByOne::create();
	listen_f6->onTouchBegan = [field_6, this](Touch* t, Event* e)
	{
		if (field_6->getBoundingBox().containsPoint(t->getLocation()))
		{
			auto tower = tower::create(field_6->getPositionX(), field_6->getPositionY(), 1, 0, 6);
			if (HOST)
				serverSend("6 0");
			else
				clientSend("6 0");
			addChild(tower, 2);
			field_6->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f6, field_6);

	auto field_7 = Sprite::create("field.png");
	field_7->setScale(0.7);
	field_7->setPosition(Point(visibleSize.width*0.72, visibleSize.height*0.67));
	fieldVector[7] = Point(visibleSize.width*0.72, visibleSize.height*0.67);
	addChild(field_7, 2);
	auto listen_f7 = EventListenerTouchOneByOne::create();
	listen_f7->onTouchBegan = [field_7, this](Touch* t, Event* e)
	{
		if (field_7->getBoundingBox().containsPoint(t->getLocation()))
		{
			auto tower = tower::create(field_7->getPositionX(), field_7->getPositionY(), 1, 0, 7);
			if (HOST)
				serverSend("7 0");
			else
				clientSend("7 0");
			addChild(tower, 2);
			field_7->removeFromParent();
			HtowerVector.pushBack(tower);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_f7, field_7);


}


void DoubleGameScene::addSoldiers(int speed)
{
	int m_type;
	if (group<12) {
		m_type = group % 6;
	}
	else
	{
		m_type = 7;
	}

	int t_path = d_path % 3;
	d_path++;
	auto H_Soldiers = Monster::create(speed, H_X, H_Y, H_Scale, t_path, m_type, 1);
	addChild(H_Soldiers, 1);
	HsoldierVector.pushBack(H_Soldiers);

	auto G_Soldiers = Monster::create(speed, G_X, G_Y, G_Scale, t_path, m_type, 1);
	addChild(G_Soldiers, 4);
	GsoldierVector.pushBack(G_Soldiers);

}

void DoubleGameScene::resetFrames(int a)
{
	currentFrameIndex = -180;
	limitFrameIndex = 60;
	wait = false;
	counter = 0;
	d_path = 0;
}

void DoubleGameScene::update(float dt)
{
	if (isStart)
		currentFrameIndex++;

	Host_monsterAttack();
	Host_towerAttack();
	Guest_monsterAttack();
	Guest_towerAttack();

	if (hitpoint == 0)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		gameover->setVisible(true);
		gameisover = true;
		auto quititem = MenuItemImage::create(
			"quitgame.png",
			"quitgame.png",
			CC_CALLBACK_1(DoubleGameScene::quitgamescene, this));
		
		quititem->setPosition(Vec2(visibleSize.width - quititem->getContentSize().width / 2,
			quititem->getContentSize().height / 2 + 500));

		// create menu, it's an autorelease object
		auto quitgame = Menu::create(quititem, NULL);
		quitgame->setPosition(Vec2::ZERO);
		this->addChild(quitgame, 4);
		
	}


	////////==============================///////////
	
	if (BUILD)
	{

		guestMapBuildTower(fieldVector[t_field].x, fieldVector[t_field].y);
		BUILD = false;
	}

	if (currentFrameIndex >= 0 && currentFrameIndex % limitFrameIndex == 0 && !wait)
	{
		addSoldiers(group);

		// update wave label
		wave = group;
		sprintf(wavearr, "Wave: %d", wave);
		waveboard->setString(wavearr);
		waveboard->setVisible(true);

		counter++;
		if (counter == (9 + 2 * group))
			wait = true;
	}
	if (currentFrameIndex >= 60 * 1 / dt - 10 * (group - 1))
		resetFrames(group++);

	//update the vector if the bullet is scope damage
	int size_z = HsoldierVector.size();
	for (int i = size_z - 1; i >= 0; i--)
	{
		if (HsoldierVector.at(i)->scope) {
			float p_m_x = HsoldierVector.at(i)->getCurrentX();
			float p_m_y = HsoldierVector.at(i)->getCurrentY();
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
					float p_t_x = HsoldierVector.at(j)->getCurrentX();
					float p_t_y = HsoldierVector.at(j)->getCurrentY();
					if ((p_m_x - p_t_x)*(p_m_x - p_t_x) + (p_m_y - p_t_y)*(p_m_y - p_t_y) <= 70 * 70) {
						HsoldierVector.at(j)->getHurt(50);
					}
				}
			}

			HsoldierVector.at(i)->scope = false;
		}
	}

	//**********************
	//Update gold every second(60 frames)

	if (currentFrameIndex % 60 == 59)//so first frame wont add gold
	{
		updateGold(1);
	}
	//update HP when a monster escape out
	int size_o = HsoldierVector.size();
	for (int i = size_o - 1; i >= 0; i--)
	{
		if (HsoldierVector.at(i)->isOut)
		{
			HsoldierVector.erase(i);
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
	int size_m = HsoldierVector.size();
	for (int i = size_m - 1; i >= 0; i--)
	{
		if (HsoldierVector.at(i)->isDead() && !HsoldierVector.at(i)->isOut)
		{
			//update score
			score++;
			sprintf(scorearr, "Score: %d", score);
			scoreboard->setString(scorearr);
			scoreboard->setVisible(true);

			//update gold

			updateGold(HsoldierVector.at(i)->getGoldBonus());

			HsoldierVector.erase(i);

			if (HOST)
			{
				std::string killSold = "-100.0 " + std::to_string(i);
				sprintf(sendBuf, killSold.c_str(), inet_ntoa(addrClient.sin_addr));
				send(_client, sendBuf, strlen(sendBuf) + 1, 0);
				sendBuf[0] = 0;
			}

			else
			{
				std::string killSold = "-100.0 " + std::to_string(i);
				send(sockClient, killSold.c_str(), strlen(killSold.c_str()) + 1, 0);
			}


		}

	}

	if (wantDeleteS)
	{
		GsoldierVector.at(GDeleteS)->removeFromParent();
		GsoldierVector.erase(GDeleteS);
		wantDeleteS = false;
	}

	//Update the Vector if some tower die
	int size_ht = HtowerVector.size();
	for (int i = size_ht - 1; i >= 0; i--)
	{
		if (HtowerVector.at(i)->isDead())
		{
			HtowerVector.erase(i);
			//add send

		}

	}
	int size_gt = GtowerVector.size();
	for (int i = size_gt - 1; i >= 0; i--)
	{
		if (GtowerVector.at(i)->isDead())
			GtowerVector.erase(i);
	}

}

void DoubleGameScene::startServer()
{
	WSADATA wsd;
	int len;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		CCLOG("start up failed!\n");
	}
	_server = socket(AF_INET, SOCK_STREAM, 0);

	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(_server, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	listen(_server, 5);
	len = sizeof(SOCKADDR);

	std::thread th(&DoubleGameScene::ThreadAccept, this, _server, (SOCKADDR*)&addrClient, &len);
	th.detach();

	jump = false;
	connected = false;
	CCLOG("ServerStarted");

}
void DoubleGameScene::startClient()
{
	WSADATA wsd;
	SOCKADDR_IN addrSrv;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("start up failed!\n");
	}
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IPaddress.c_str());
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	if (0 == connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))
	{
		CCLOG("Connected to host");
		end = false;
		std::thread th(&DoubleGameScene::receive, this);
		th.detach();
	}
	else
	{
		CCLOG("Connection timed out");
	}

}

//add socket
void DoubleGameScene::ThreadAccept(SOCKET s, sockaddr *addr, int *addrlen)
{
	connected = false;
	_client = accept(s, addr, addrlen);

	if (_client != INVALID_SOCKET)
	{
		connected = true;
		CCLOG("%d", _client);
		auto request = new cocos2d::network::HttpRequest();
		request->setTag("type is post");
		request->setUrl("10.25.70.125/deleteByID_new.php");
		//Set request type
		request->setRequestType(cocos2d::network::HttpRequest::Type::POST);

		// adjust data form to be receivable to server
		std::string conc = "ID=" + hostname;
		__String *toSend = __String::create(conc);
		request->setRequestData(toSend->getCString(), toSend->length());

		//Create a client instance to send the request
		auto client = cocos2d::network::HttpClient::getInstance();
		client->setTimeoutForConnect(10);
		client->send(request);
		request->release();
	}
	else
	{
		CCLOG("Connection Failed");
	}

	while (!jump && connected)
	{
		if (0 >= recv(_client, recvBuf, 100, 0))
		{
			break;
		}
		CCLOG("%s\n", recvBuf);
		std::string Received(recvBuf);
		if (Received == "win")
		{

		}
		std::string::size_type sz;
		t_field = std::stof(Received, &sz);
		t_tower = std::stof(Received.substr(sz));

		if (t_field < -99)
		{
			GDeleteS = t_tower;
			wantDeleteS = true;
		}
		else
		{
			BUILD = true;
		}
		recvBuf[0] = 0;
	}
	connected = false;
	AllClean();
	return;
}

void DoubleGameScene::receive()
{
	while (0<recv(sockClient, recvBuffer, 100, 0))
	{
	
		CCLOG("%s\n", recvBuffer);
		std::string Received(recvBuffer);
		if (Received == "GO")
		{
			isStart = true;
		}

		else
		{
			//receive the tower message!!!!!
			std::string::size_type sz;
			t_field = std::stof(Received, &sz);
			t_tower = std::stof(Received.substr(sz));
			if (t_field < -99)
			{
				GDeleteS = t_tower;
				wantDeleteS = true;
			}
			else
			{
				BUILD = true;
			}

		}
		recvBuffer[0] = 0;
	}
	closesocket(sockClient);
	CCLOG("socket closed");
	WSACleanup();
	return;
}

std::string DoubleGameScene::Convert(float Num)
{
	std::stringstream ss;
	ss << Num;
	std::string str(ss.str());
	return str;
}


void DoubleGameScene::POSTcompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
	CCLOG("Response Tag is %s", response->getHttpRequest()->getTag());
	CCLOG("Respnse Code : %d ", response->getResponseCode());
	if (response->isSucceed())
	{
		// build a buffer to restore server's reponse
		std::vector<char> *ServerResponse = response->getResponseData();
		char *concatenated = (char*)malloc(ServerResponse->size() + 1);
		// convert the response to a long, complete string
		std::string tempString(ServerResponse->begin(), ServerResponse->end());
		strcpy(concatenated, tempString.c_str());

		// build a json object with the string and parse this object to get its variables in different index
		Json *json = Json_create(concatenated);
		int id = Json_getInt(json, "ID", -1);
		hostname = id;
		CCLOG("%d", id);
	}
}

void DoubleGameScene::sendIP(std::string nickname)
{
	char lv_name[50];
	gethostname(lv_name, 50);
	hostent *lv_pHostent;
	lv_pHostent = (hostent *)malloc(sizeof(hostent));
	if (NULL == (lv_pHostent = gethostbyname(lv_name)))
	{
		printf("get Hostname Fail \n");
	}
	memcpy(&addrSrv.sin_addr.S_un.S_addr, lv_pHostent->h_addr_list[0], lv_pHostent->h_length);
	CCLOG("%s\n", inet_ntoa(addrSrv.sin_addr));
	std::string IPADDR = inet_ntoa(addrSrv.sin_addr);

	auto request = new cocos2d::network::HttpRequest();
	request->setTag("type is post");
	request->setUrl("10.25.70.125/postaddr.php");
	//Set request type
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);

	// adjust data form to be receivable to server
	std::string conc = "hostname=" + nickname + "&ipaddr=" + IPADDR;
	CCLOG("The Host IP Address is %s\n",conc.c_str());
	__String *toSend = __String::create(conc);
	request->setRequestData(toSend->getCString(), toSend->length());
	request->setResponseCallback(CC_CALLBACK_2(DoubleGameScene::POSTcompleted, this));

	//Create a client instance to send the request
	auto client = cocos2d::network::HttpClient::getInstance();
	client->setTimeoutForConnect(10);
	client->send(request);
	request->release();
}

void DoubleGameScene::StartPlay(Ref* pSender)
{
	if (connected)
	{
		std::string StartSignal = "GO";
		sprintf(sendBuf, StartSignal.c_str(), inet_ntoa(addrClient.sin_addr));
		send(_client, sendBuf, strlen(sendBuf) + 1, 0);
		isStart = true;
	}
	else
	{
		CCLOG("Waiting for another player!");
	}
}

bool DoubleGameScene::serverSend(std::string message)
{
	sprintf(sendBuf, message.c_str(), inet_ntoa(addrClient.sin_addr));
	send(_client, sendBuf, strlen(sendBuf) + 1, 0);
	sendBuf[0] = 0;
	return true;
}

bool  DoubleGameScene::clientSend(std::string message)
{
	send(sockClient, message.c_str(), strlen(message.c_str()) + 1, 0);
	return true;
}

void DoubleGameScene::quitgamescene(cocos2d::Ref * pSender) {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

void DoubleGameScene::AllClean()
{
	closesocket(_server);
	closesocket(_client);
	CCLOG("socket closed");
	WSACleanup();
}

void DoubleGameScene::BackToHome(Ref *pSender)
{
	auto request = new cocos2d::network::HttpRequest();
	request->setTag("type is post");
	request->setUrl("10.25.70.125/deleteByID_new.php");
	//Set request type
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);

	// adjust data form to be receivable to server
	std::string conc = "ID=" + hostname;
	__String *toSend = __String::create(conc);
	request->setRequestData(toSend->getCString(), toSend->length());

	//Create a client instance to send the request
	auto client = cocos2d::network::HttpClient::getInstance();
	client->setTimeoutForConnect(10);
	client->send(request);
	request->release();

	if (HOST)
	{
		//serverSend("win");
		jump = true;
		connected = false;
		shutdown(_client, 2);
		Sleep(1000);
	}
	else
	{
		//clientSend("win");
		end = true;
		Sleep(1000);
	}
	auto scene = HomeScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void DoubleGameScene::updateGold(int different)
{
	gold += different;
	sprintf(goldarr, "GOLD: %d", gold);
	GOLD->setString(goldarr);
	GOLD->setVisible(true);

}
