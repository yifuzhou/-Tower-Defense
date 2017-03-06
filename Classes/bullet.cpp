#include"bullet.h"

bullet* bullet::create(tower *_tower, Monster *_monster, float scale, int type)
{
	auto  _ins = new bullet();
	_ins->init(_tower, _monster, scale, type);
	_ins->autorelease();
	return _ins;
}

bool bullet::init(tower * _tower, Monster *_monster, float scale, int type)
{
	Sprite::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Ytower = _tower;
	monster = _monster;
	B_scale = scale;

	char* pic_name;
	if (type == 0) {
		pic_name = "bullet.png";
		bullet_type = 0;
	}
	else if (type == 1) {
		pic_name = "boombullet.png";
		bullet_type = 1;
		
	}
	else {
		pic_name = "freezebullet.png";
		bullet_type = 2;
		
	}
	Sprite *sprite_bullet = Sprite::create(pic_name);
	sprite_bullet->setScale(1.5f*B_scale);
	//sprite_bullet->setPhysicsBody(PhysicsBody::createBox(sprite_bullet->getContentSize()));
	//sprite_bullet->getPhysicsBody()->setCategoryBitmask(ball2Mask);
	//sprite_bullet->getPhysicsBody()->setCollisionBitmask(ball1Mask);
	//sprite_bullet->getPhysicsBody()->setContactTestBitmask(ball1Mask);
	//sprite_bullet->setTag(5);

	this->addChild(sprite_bullet, 6, 1);
	initX = _tower->p_x + 10;
	initY = _tower->p_y + 5;
	sprite_bullet->setPosition(initX, initY);

	//get the bullet speed
	speed = (_tower->bullet_speed)*B_scale;
	ATK = _tower->ATK;
	//if (B_scale == 0.3)
		//log("bullet created scale:%f", B_scale);

	scheduleUpdate();

	return true;
}

float bullet::getCurrentX()
{
	return initX + getPositionX();
}

float bullet::getCurrentY()
{
	return initY + getPositionY();
}

void bullet::nextPoint(float dt)
{
	float rate_y = monster->getCurrentY() - this->getCurrentY();
	float rate_x = monster->getCurrentX() - this->getCurrentX();
	float monster_height = monster->getContentSize().height;
	float monster_width = monster->getContentSize().width;
 	float tower_height = Ytower->getContentSize().height;
	float tower_width = Ytower->getContentSize().width;
	if (abs(rate_y) <= 3* B_scale&& abs(rate_x) <= 3* B_scale)
	{
		monster->getHurt(ATK);
		if (bullet_type == 1) {
			monster->scope = true;
		}
		if (bullet_type == 2) {
			monster->befreeze = true;
		}
		unscheduleUpdate();
		removeFromParent();

		
	}
	else
	{
		float rate_z = rate_y*rate_y + rate_x*rate_x;
		rate_z = sqrt(rate_z);
		rate_z = speed*dt / rate_z;

		setPositionX(getPositionX() + rate_z*rate_x);
		setPositionY(getPositionY() + rate_z*rate_y);
	}
	
}

void bullet::update(float dt)
{
	//log("bullet created scale:%f", B_scale);
	if (!monster->isDead()&&!Ytower->isDead())
		nextPoint(dt);
	else
	{
		//log("bullet end!!!!!!");
		unscheduleUpdate();
		removeFromParent();
	}
}