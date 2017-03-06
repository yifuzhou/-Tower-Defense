#ifndef __TOWER_H__
#define __TOWER_H__
#include"cocos2d.h"

using namespace cocos2d;

class  tower :public Sprite
{
public:
	virtual bool init(float x, float y, float scale,int type, int place);
	void getBloodbar(Sprite * sprite, float a, float scale);
	void isAttackedFun(int hurt);
	virtual void update(float dt);
	static tower* create(float x, float y, float scale,int type, int place);
	bool isDead();
	float p_x;
	float p_y;
	int bullet_speed;
	int range;
	int ATK;
	bool startAttack;
	Sprite *sprite_tower;
	Sprite *getSprite();
	int tower_type;
	void upgrade();
	int cost = 10;
	int field_place;
	float Blood;
private:
	
	bool isAttacked;
	int hurtVar;
	void timeCounter();
	int counter;
	int add_bullet_slot;

	
};
#endif // __TOWER_H__