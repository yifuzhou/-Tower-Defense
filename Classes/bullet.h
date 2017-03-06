#ifndef __BULLET_H__
#define __BULLET_H__
#include"cocos2d.h"
#include"tower.h"
#include"Monster.h"

using namespace cocos2d;

class  bullet :public Sprite
{
public:
	virtual bool init(tower *tower, Monster *monster, float scale, int type);
	static bullet* create(tower *tower, Monster *monster, float scale, int type);
	virtual void update(float dt);
	void nextPoint(float dt);
	float getCurrentX();
	float getCurrentY();
	Monster *monster;
	tower *Ytower;

	int bullet_type;

private:
	int speed;
	float initX;
	float initY;
	int ATK;
	int ball1Mask = 1 << 0;
	int ball2Mask = 1 << 1;
	float B_scale;
};
#endif // __BULLET_H__