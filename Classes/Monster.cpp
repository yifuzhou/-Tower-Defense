#include "Monster.h"

Monster* Monster::create(int speed, float x, float y, float scale, int t_path, int type, int mapSelect)
{
	auto  _ins = new Monster();

	_ins->init(speed, x, y, scale, t_path, type, mapSelect);
	_ins->autorelease();
	return _ins;
}

bool Monster::init(int speed, float x, float y, float scale, int t_path, int type, int mapSelect)
{
	Sprite::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (type == 1) {
		sprite_monster = Sprite::create("soldier_00.png");
	}
	else if (type == 2)
	{
		sprite_monster = Sprite::create("soldier1_00.png");

	}
	else if (type == 3)
	{
		sprite_monster = Sprite::create("soldier2_00.png");

	}
	else if (type == 4)
	{
		sprite_monster = Sprite::create("bird_00.png");

	}
	else if (type == 5)
	{
		sprite_monster = Sprite::create("dragon2_00.png");

	}
	else if (type == 6)
	{
		sprite_monster = Sprite::create("dragon1_00.png");

	}
	else //type 7 monster can attack tower
	{
		sprite_monster = Sprite::create("dragon1_00.png");
	}

	this->addChild(sprite_monster, 5, 1);

	Map_X = x;
	Map_Y = y;
	initScale = scale;
	Map = mapSelect;
	hLevel = t_path % 3 + 2;

	if (Map == 1)
	{
		initMX = initScale*visibleSize.width / 1.46f + Map_X - initScale*visibleSize.width / 2;
		initMY = initScale*visibleSize.height / 1.2f + Map_Y - initScale*visibleSize.height / 2;
		sprite_monster->setPosition(Point(initMX, initMY));
	}
	else if (Map == 2)
	{
		initMX = initScale*visibleSize.width *0.06f + Map_X - initScale*visibleSize.width / 2;
		initMY = initScale*visibleSize.height * (0.46 + (hLevel - 2) * 0.04) + Map_Y - initScale*visibleSize.height / 2;
	
		sprite_monster->setPosition(Point(initMX, initMY));

	}
	else if (Map == 3)
	{
		initMX = initScale*visibleSize.width * 544 / 1024 + Map_X - initScale*visibleSize.width / 2;
		initMY = initScale*visibleSize.height * 429 / 576 + Map_Y - initScale*visibleSize.height / 2;
		sprite_monster->setPosition(Point(initMX, initMY));

	}
	else if (Map==4)
	{
		initMX = initScale*visibleSize.width *28/1024+ Map_X - initScale*visibleSize.width / 2;
		initMY = initScale*visibleSize.height *82/576 + Map_Y - initScale*visibleSize.height / 2;
		sprite_monster->setPosition(Point(initMX, initMY));

	}
	
	sprite_monster->setScale(initScale);

	Animation* animation_monster = Animation::create();
	for (int i = 0; i < 4; i++)
	{
		char szName[100] = { 0 };
		if (type == 1) {
			sprintf(szName, "soldier_%02d.png", i % 4);
		}
		else if (type == 2)
		{
			sprintf(szName, "soldier1_%02d.png", i % 4);

		}
		else if (type == 3)
		{
			sprintf(szName, "soldier2_%02d.png", i % 4);

		}
		else if (type == 4)
		{
			sprintf(szName, "bird_%02d.png", i % 4);

		}
		else if (type == 5)
		{
			sprintf(szName, "dragon2_%02d.png", i % 4);

		}
		else if (type == 6)
		{
			sprintf(szName, "dragon1_%02d.png", i % 4);

		}
		else//type 7 monsters can attack towers
		{
			sprintf(szName, "dragon1_%02d.png", i % 4);
		}



		animation_monster->addSpriteFrameWithFileName(szName);
	}
	animation_monster->setDelayPerUnit(2.8f / 6.0f);
	animation_monster->setRestoreOriginalFrame(true);
	Animate *animate_monster = Animate::create(animation_monster);
	sprite_monster->runAction(RepeatForever::create(dynamic_cast<ActionInterval *>(Sequence::create(animate_monster, NULL))));

	//init all the value
	turnPoint = 0;
	rDirection = t_path;

	//replace it 
	//rDirection = rand() % 3;
	//hLevel = (rand() % 3 + 2);



	if (type == 1) {
		AttackRange = 10;
		stopAndAttack = false;
		hurtVar = 5;
		defence = 5;
		Blood = 100;
		movingSpeed = (15 + 2 * speed)*initScale;
	}
	else if (type == 2)
	{
		AttackRange = 10;
		stopAndAttack = false;
		hurtVar = 5;
		defence = 15;
		Blood = 100;
		movingSpeed = (15 + 2 * speed)*initScale;

	}
	else if (type == 3)
	{
		AttackRange = 10;
		stopAndAttack = false;
		hurtVar = 5;
		defence = -1;
		Blood = 100;
		movingSpeed = (25 + 2 * speed)*initScale;

	}
	else if (type == 4)
	{
		AttackRange = 10;
		stopAndAttack = false;
		hurtVar = 5;
		defence = 3;
		Blood = 100;
		movingSpeed = (25 + 2 * speed)*initScale;

	}
	else if (type == 5)
	{
		AttackRange = 10;
		stopAndAttack = false;
		hurtVar = 5;
		defence = 15;
		Blood = 200;
		movingSpeed = (3 + 2 * speed)*initScale;

	}
	else if (type == 6)
	{
		AttackRange = 10;
		stopAndAttack = false;
		hurtVar = 5;
		defence = 15;
		Blood = 100;
		movingSpeed = (8 + 2 * speed)*initScale;

	}
	else//type 7 monsters can attack towers
	{
		AttackRange = 10;
		stopAndAttack = false;
		hurtVar = 5;
		defence = 5;
		Blood = 100;
		movingSpeed = (15 + 2 * speed)*initScale;
	}







	//add blood bar
	getBloodbar(sprite_monster, Blood);


	/*
	setPhysicsBody(PhysicsBody::createBox(s));
	setTextureRect(Rect(0, 0, s.width, s.height));
	setColor(Color3B(0, 0, 0));
	setContentSize(s);*/

	scheduleUpdate();

	/*getPhysicsBody()->setDynamic(false);

	getPhysicsBody()->setContactTestBitmask(1);
	setTag(3);
	*/

	return true;

}

float Monster::getCurrentX()
{
	return initMX + getPositionX();
}

float Monster::getCurrentY()
{
	return initMY + getPositionY();
}

void Monster::getBloodbar(Sprite  *monstersprite, float a)
{
	CCSprite *pBloodEmptySp = CCSprite::create("emptyblood.jpg");//empty blood
	pBloodEmptySp->setPosition(Vec2(monstersprite->getContentSize().width / 2, monstersprite->getContentSize().height / 1.05));
	pBloodEmptySp->setScale(0.7f);
	//something new
	pBloodEmptySp->setOpacity(100);

	monstersprite->addChild(pBloodEmptySp);
	CCSprite *pBloodFullSp = CCSprite::create("fullblood.jpg");//full blood
	CCProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodFullSp);
	pBloodProGress->setType(kCCProgressTimerTypeBar);
	pBloodProGress->setBarChangeRate(Vec2(1, 0));
	pBloodProGress->setMidpoint(Vec2(0, 0));
	pBloodProGress->setScale(0.7f);
	pBloodProGress->setPosition(Vec2(monstersprite->getContentSize().width / 2, monstersprite->getContentSize().height / 1.05));
	pBloodProGress->setPercentage(a);
	monstersprite->addChild(pBloodProGress, 1, 1); //set Tag is 1
}

void Monster::moveToNextPointinMap_1(float dt, bool befreeze, bool already)
{
	//if (!befreeze) {
	//	log("asda");
	//}

	if (befreeze && !alreadyfreeze) {
		movingSpeed = 0.5*movingSpeed;
		alreadyfreeze = true;
	}
	if (!stopAndAttack)
	{
		if (turnPoint == 0)
		{
			this->setPositionY(getPositionY() - movingSpeed * dt);
			if (getPositionY() <= -45 * initScale / hLevel)
			{
				turnPoint = 1;
				if (rDirection != 2)
					sprite_monster->setFlippedX(true);
			}
		}
		else if (turnPoint == 1)
		{
			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				if (getPositionX() <= -520 * initScale + (70 * initScale / hLevel))
				{
					sprite_monster->setFlippedX(false);
					turnPoint = 2;
				}
			}
			else if (rDirection == 1)
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				if (getPositionX() <= -180 * initScale + (70 * initScale / hLevel))
				{
					turnPoint = 2;
				}
			}
			else
			{
				this->setPositionX(getPositionX() + movingSpeed * dt);
				if (getPositionX() >= 101 * initScale + (70 * initScale / hLevel))
				{
					sprite_monster->setFlippedX(true);
					turnPoint = 2;
				}
			}
		}
		else if (turnPoint == 2)
		{
			if (rDirection == 0)
			{
				this->setPositionY(getPositionY() + movingSpeed * dt);
				if (getPositionY() >= 70 * initScale)
				{
					Blood = 0;
					isOut = true;
					unscheduleUpdate();
					removeFromParent();
				}
			}
			else if (rDirection == 1)
			{
				this->setPositionY(getPositionY() - movingSpeed * dt);
				if (getPositionY() <= -200 * initScale + (70 * initScale / hLevel))
					turnPoint = 3;
			}
			else
			{
				this->setPositionY(getPositionY() - movingSpeed * dt);
				if (getPositionY() <= -203 * initScale + (70 * initScale / hLevel))
					turnPoint = 3;
			}
		}
		else if (turnPoint == 3)
		{
			if (rDirection == 1)
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				if (getPositionX() <= -470 * initScale + (70 * initScale / hLevel))
					turnPoint = 4;
			}
			else if (rDirection == 2)
			{
				this->setPositionX(getPositionX() - movingSpeed * 0.907 * dt);
				this->setPositionY(getPositionY() - movingSpeed * 0.423 * dt);
				if (getPositionY() <= -285 * initScale + (70 * initScale / hLevel))
				{
					sprite_monster->setFlippedX(false);
					turnPoint = 4;
				}
			}
		}
		else if (turnPoint == 4)
		{
			if (rDirection == 1)
			{
				this->setPositionX(getPositionX() - movingSpeed * 0.707 * dt);
				this->setPositionY(getPositionY() - movingSpeed * 0.707 * dt);
				if (getPositionX() <= -596 * initScale + (70 * initScale / hLevel))
					turnPoint = 5;
			}
			else if (rDirection == 2)
			{
				this->setPositionY(getPositionY() - movingSpeed * dt);
				if (getPositionY() <= -387 * initScale + (70 * initScale / hLevel))
				{
					turnPoint = 5;
				}
			}
		}
		else
		{
			if (rDirection == 1)
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				if (getPositionX() <= -686 * initScale)
				{
					Blood = 0;
					isOut = true;
					unscheduleUpdate();
					removeFromParent();
				}
			}
			else
			{
				this->setPositionX(getPositionX() + movingSpeed * dt);
				if (getPositionX() >= 286 * initScale)
				{
					Blood = 0;
					isOut = true;
					unscheduleUpdate();
					removeFromParent();
				}
			}
		}
	}
}

void Monster::moveToNextPointinMap_2(float dt, bool befreeze, bool already)
{
	if (!stopAndAttack)
	{
		if (turnPoint == 0)
		{
			this->setPositionX(getPositionX() + movingSpeed * dt);
			if (getPositionX() >= 210 * initScale)
			{
				turnPoint = 1;
			}
		}
		else if (turnPoint == 1)
		{
			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() + 0.69 * movingSpeed * dt);
				this->setPositionY(getPositionY() + 0.72 * movingSpeed * dt);
				if (getPositionX() >= 360 * initScale)
				{
					turnPoint = 2;
				}
			}
			else
			{
				this->setPositionX(getPositionX() + 0.69 * movingSpeed * dt);
				this->setPositionY(getPositionY() - 0.72 * movingSpeed * dt);
				log("here here herer!!!");
				if (getPositionX() >= 350 * initScale)
				{
					turnPoint = 2;
				}
			}
		}
		else if (turnPoint == 2)
		{
			this->setPositionX(getPositionX() + movingSpeed * dt);
			if (getPositionX() >= 570 * initScale)
			{
				turnPoint = 3;
			}
		}
		else if (turnPoint == 3)
		{
			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() + 0.7 * movingSpeed * dt);
				this->setPositionY(getPositionY() - 0.72 * movingSpeed * dt);
				if (getPositionX() >= 730 * initScale)
					turnPoint = 4;
			}
			else
			{
				this->setPositionX(getPositionX() + 0.7 * movingSpeed * dt);
				this->setPositionY(getPositionY() + 0.72 * movingSpeed * dt);
				if (getPositionX() >= 725 * initScale)
				{
					turnPoint = 4;
				}
			}
		}
		else if (turnPoint == 4)
		{

			this->setPositionX(getPositionX() + movingSpeed * dt);
			if (getPositionX() >= 970 * initScale)
			{
				Blood = 0;
				isOut = true;
				unscheduleUpdate();
				removeFromParent();

			}

		}
	}
}


void Monster::moveToNextPointinMap_3(float dt, bool befreeze, bool already)
{
	//if (!befreeze) {
	//	log("asda");
	//}

	if (befreeze && !alreadyfreeze) {
		movingSpeed = 0.5*movingSpeed;
		alreadyfreeze = true;
	}
	if (!stopAndAttack)
	{
		if (turnPoint == 0)
		{
			this->setPositionY(getPositionY() - movingSpeed * dt);
			if (getPositionY() <= -131)
			{
				turnPoint = 1;
				if (rDirection != 1)
					sprite_monster->setFlippedX(true);
			}
		}
		else if (turnPoint == 1)
		{
			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				this->setPositionY(getPositionY() + movingSpeed * 0.5 * dt);

				if (getPositionX() <= -228)
				{
					//sprite_monster->setFlippedX(false);
					turnPoint = 2;
				}
			}
			else
			{
				this->setPositionX(getPositionX() + movingSpeed * dt);
				this->setPositionY(getPositionY() + movingSpeed * 0.423 * dt);

				if (getPositionX() >= 183)
				{
					turnPoint = 2;
				}
			}
		}
		else if (turnPoint == 2)
		{
			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				this->setPositionY(getPositionY() - movingSpeed * 0.27 * dt);

				if (getPositionX() <= -433)
				{
					sprite_monster->setFlippedX(false);
					turnPoint = 3;
					//	Blood = 0;
					//	isOut = true;
					//	unscheduleUpdate();
					//	removeFromParent();
				}
			}
			else
			{
				this->setPositionX(getPositionX() + movingSpeed * dt);
				if (getPositionX() >= 390) {
					turnPoint = 3;
					sprite_monster->setFlippedX(true);
				}
			}
		}
		else if (turnPoint == 3)
		{
			if (rDirection == 0)
			{

				this->setPositionX(getPositionX() + movingSpeed * dt);
				this->setPositionY(getPositionY() - movingSpeed *1.7 * dt);
				if (getPositionX() >= -400)
				{
					turnPoint = 4;
				}
			}
			else
			{
				this->setPositionY(getPositionY() - movingSpeed * dt);
				if (getPositionY() <= -141)
				{
					turnPoint = 4;

				}
			}
		}
		else if (turnPoint == 4)
		{
			if (rDirection == 0)
			{

				this->setPositionX(getPositionX() + movingSpeed * dt);
				this->setPositionY(getPositionY() - movingSpeed *0.22 * dt);
				if (getPositionX() >= -250)
				{
					sprite_monster->setFlippedX(true);
					turnPoint = 5;
				}
			}
			else
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				this->setPositionY(getPositionY() - movingSpeed *0.22 * dt);
				if (getPositionX() <= 230) {
					turnPoint = 5;
					sprite_monster->setFlippedX(false);

				}
			}
		}
		else if (turnPoint == 5)
		{
			if (rDirection == 0)
			{

				this->setPositionX(getPositionX() - movingSpeed*0.44 * dt);
				this->setPositionY(getPositionY() - movingSpeed *0.66 * dt);
				if (getPositionX() <= -320)
				{
					turnPoint = 6;
				}
			}
			else
			{
				this->setPositionX(getPositionX() + movingSpeed*0.99 * dt);
				this->setPositionY(getPositionY() - movingSpeed * dt);
				if (getPositionX() >= 330)
				{
					turnPoint = 6;
					sprite_monster->setFlippedX(true);

				}
			}
		}
		else if (turnPoint == 6)
		{
			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				if (getPositionX() <= -545) {
					//turnPoint = 3;
					Blood = 0;
					isOut = true;
					unscheduleUpdate();
					removeFromParent();
				}
			}
			else
			{
				this->setPositionX(getPositionX() - movingSpeed * dt);
				this->setPositionY(getPositionY() - movingSpeed *0.13 * dt);

				if (getPositionX() <= 100)
				{
					turnPoint = 7;
				}
			}
		}
		else {
			this->setPositionY(getPositionY() - movingSpeed * dt);
			if (getPositionY() <= -429)
			{
				Blood = 0;
				isOut = true;
				unscheduleUpdate();
				removeFromParent();
			}
		}
	}
}

void Monster::moveToNextPointinMap_4(float dt, bool befreeze, bool already)
{
	//if (!befreeze) {
	//	log("asda");
	//}

	if (befreeze && !alreadyfreeze) {
		movingSpeed = 0.5*movingSpeed;
		alreadyfreeze = true;
	}
	if (!stopAndAttack)
	{
		if (turnPoint == 0)
		{
			this->setPositionX(getPositionX() + movingSpeed * dt);
			if (getPositionX() >= 290 )
			{
				turnPoint = 1;
				
					
			}
		}
		else if (turnPoint == 1)
		{
			this->setPositionY(getPositionY() + movingSpeed * dt);

				if (getPositionY() >=86 )
				{
					
					turnPoint = 2;
					sprite_monster->setFlippedX(true);
				}
						
		}
		else if (turnPoint == 2)
		{
		
			this->setPositionX(getPositionX() - movingSpeed * dt*0.435);
			this->setPositionY(getPositionY() + movingSpeed * dt*0.87);
			if (getPositionY() >= 263)
			{
				turnPoint = 3;
				sprite_monster->setFlippedX(false);
			}
			
		}
		else if (turnPoint == 3)
		{
			this->setPositionX(getPositionX() + movingSpeed * dt*0.435);
			this->setPositionY(getPositionY() + movingSpeed * dt*0.87);

			if (getPositionX() >= 280)
			{
				turnPoint = 4;
				
			}
		}
		else if (turnPoint == 4)
		{
		
				this->setPositionX(getPositionX() + movingSpeed * dt);
				
				if (getPositionX() >= 462 )
					turnPoint = 5;
		
		}
		else if(turnPoint==5)
		{
			this->setPositionX(getPositionX() - movingSpeed * dt*0.435);
			this->setPositionY(getPositionY() - movingSpeed * dt*0.87);
				if (getPositionX() <= 420)			
					turnPoint = 6;
	
		}
		else if(turnPoint==6)
		{
			this->setPositionX(getPositionX() + movingSpeed * dt*0.435);
			this->setPositionY(getPositionY() - movingSpeed * dt*0.87);
			if (getPositionX() >= 525)
				turnPoint = 7;
		}
		else if(turnPoint==7)
		{
			this->setPositionX(getPositionX() + movingSpeed * dt);
			if (getPositionX() >= 660)
				turnPoint = 8;
		}
		else if(turnPoint==8)
		{
			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() + movingSpeed * dt*0.435);
				this->setPositionY(getPositionY() + movingSpeed * dt*0.87);
				if (getPositionX() >= 743)
					turnPoint = 9;
			}
			else
			{
				this->setPositionX(getPositionX() + movingSpeed * dt*0.87);
				this->setPositionY(getPositionY() - movingSpeed * dt*0.435);
				if (getPositionX() >= 760)
					turnPoint = 9;
				sprite_monster->setFlippedX(true);
			}
		}
		else if(turnPoint==9)
		{

			if (rDirection == 0)
			{
				this->setPositionX(getPositionX() + movingSpeed * dt);
				if (getPositionX() >= 943)
				{
					Blood = 0;
					isOut = true;
					unscheduleUpdate();
					removeFromParent();

				}
			}
			else
			{				
				this->setPositionY(getPositionY() - movingSpeed * dt);
				if (getPositionY() <= -46)
					turnPoint = 10;
			}
		}
		else if(turnPoint==10)
		{
			this->setPositionX(getPositionX() - movingSpeed * dt);
			if (getPositionX() <= 560)
			{
				Blood = 0;
				isOut = true;
				unscheduleUpdate();
				removeFromParent();

			}

		}
		else
		{

		 }
	}
}

void Monster::getHurt(int hurt)
{
	Blood = Blood - hurt + defence;
	CCProgressTimer *poBloodProGress = (CCProgressTimer *)getChildByTag(1)->getChildByTag(1);
	if (Blood <= 0)
		Blood = 0;
	poBloodProGress->setPercentage(Blood);

}

bool Monster::isDead()
{
	if (Blood <= 0)
		return true;
	else
		return false;
}

//*************
int Monster::getGoldBonus()
{
	return goldBonus;
}
//*************

void Monster::update(float dt)
{
	if (isDead())
	{
		unscheduleUpdate();
		removeFromParent();
	}
	else
	{
		if (Map == 1) {
			moveToNextPointinMap_1(dt, befreeze, alreadyfreeze);
		}
		else if (Map == 2)
		{
			moveToNextPointinMap_2(dt, befreeze, alreadyfreeze);
		}
		else if (Map == 3) {
			moveToNextPointinMap_3(dt, befreeze, alreadyfreeze);
		}
		else if (Map == 4)
		{
			moveToNextPointinMap_4(dt, befreeze, alreadyfreeze);
		}
		

	}
}

