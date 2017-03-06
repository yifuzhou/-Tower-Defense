#include"tower.h"

tower* tower::create(float x, float y, float scale, int type, int place)
{
	auto  _ins = new tower();
	_ins->init(x, y, scale,type, place);
	_ins->autorelease();
	return _ins;
}

bool tower::init(float x, float y, float scale, int type, int place)
{
	Sprite::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (type == 0) {
		sprite_tower = Sprite::create("towerss_00.png");
		tower_type = 0;
	}
	else if (type == 1) {
		sprite_tower = Sprite::create("towers-hd.png");
		tower_type = 1;
	}
	else{
		sprite_tower = Sprite::create("freezetower_02.png");
		tower_type = 2;
	}
	p_x = x;
	p_y = y;
	sprite_tower->setPosition(Point(p_x, p_y));
	sprite_tower->setScale(0.6*scale);
	addChild(sprite_tower, 5, 1);
	//sprite_tower->setFlippedX(true);
	//log("Init char*Y :%f", this->getPositionY());
	//log("Init char*X :%f", this->getPositionX());

/**	
	Animation* animation_tower = Animation::create();
	for (int i = 1; i <= 3; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "towerss_%02d.png", i % 3);
		animation_tower->addSpriteFrameWithFileName(szName);
	}
	animation_tower->setDelayPerUnit(2.8f / 6.0f);
	animation_tower->setRestoreOriginalFrame(true);
	Animate *animate_tower = Animate::create(animation_tower);
	sprite_tower->runAction(RepeatForever::create(dynamic_cast<ActionInterval *>(Sequence::create(animate_tower, NULL))));
*/

	if (type == 0) {
		Blood = 100;
		//temporary value for this moment
		bullet_speed = 200;
		range = 200;
		ATK = 40;
		startAttack = true;
		counter = 0;
		add_bullet_slot = 40;
		field_place = place;
	}
	else if (type == 1) {
		Blood = 100;
		//temporary value for this moment
		bullet_speed = 140;
		range = 150;
		ATK = 30;
		startAttack = true;
		counter = 0;
		add_bullet_slot = 65;
		field_place = place;

	}
	else {
		Blood = 100;
		//temporary value for this moment
		bullet_speed = 140;
		range = 300;
		ATK = 20;
		startAttack = true;
		counter = 0;
		add_bullet_slot = 20;
		field_place = place;

	}


	getBloodbar(sprite_tower, Blood, scale);
	isAttacked = false;

	return true;
}
void tower::getBloodbar(Sprite  *sprite, float a, float scale)
{
	CCSprite *pBloodEmptySp = CCSprite::create("emptyblood.jpg");//empty blood
	pBloodEmptySp->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 1.05));
	pBloodEmptySp->setScale(1);
	pBloodEmptySp->setOpacity(100);
	sprite->addChild(pBloodEmptySp);
	CCSprite *pBloodFullSp = CCSprite::create("fullblood.jpg");//full blood
	CCProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodFullSp);
	pBloodProGress->setType(kCCProgressTimerTypeBar);
	pBloodProGress->setBarChangeRate(Vec2(1, 0));
	pBloodProGress->setMidpoint(Vec2(0, 0));
	pBloodProGress->setScale(1);
	pBloodProGress->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 1.05));
	pBloodProGress->setPercentage(a);
	sprite->addChild(pBloodProGress, 1, 1); //set Tag is 1
	scheduleUpdate();
}

void tower::isAttackedFun(int hurt)
{
	isAttacked = true;
	hurtVar = hurt;
}

bool tower::isDead()
{
	bool id = false;
	if (Blood <= 0)
		id = true;
	return id;
}

void tower::timeCounter()
{
	if (counter == add_bullet_slot)
	{
		startAttack = true;
		counter = 0;
	}
	else
		counter++;
}


void tower::update(float dt)
{
	
	if (Blood == 0)
	{
		unscheduleUpdate();
		removeFromParent();
	}
	else
	{
		if (!startAttack)
			timeCounter();
		if (isAttacked)
		{
			Blood = Blood - hurtVar * dt;
			CCProgressTimer *poBloodProGress = (CCProgressTimer *)getChildByTag(1)->getChildByTag(1);
			if (Blood <= 0)
				Blood = 0;
			poBloodProGress->setPercentage(Blood);
			isAttacked = false;
		}
	
	}
}

Sprite* tower::getSprite() {
	return sprite_tower;
}

void tower::upgrade() {
	sprite_tower->setScale(0.75);
	ATK *= 1.73;
}