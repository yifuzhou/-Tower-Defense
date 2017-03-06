#ifndef __MONSTER_H__
#define __MONSTER_H__
#include"iostream"
#include"cocos2d.h"


USING_NS_CC;

class Monster :public Sprite
{
public:
	virtual bool init(int, float, float, float, int, int, int);
	//virtual bool init(int, float, float, float, int);
	virtual void update(float);
	//void moveToNextPoint(float, bool, bool);
	void moveToNextPointinMap_1(float, bool, bool);
	void moveToNextPointinMap_2(float, bool, bool);
	void moveToNextPointinMap_3(float, bool, bool);
	void moveToNextPointinMap_4(float, bool, bool);
	void getBloodbar(Sprite * monsterprite, float a);
	void getHurt(int);
	float getCurrentX();
	float getCurrentY();
	bool isDead();
	static Monster* create(int, float, float, float, int, int, int);
	//static Monster* create(int, float, float, float, int);
	int AttackRange;
	bool stopAndAttack;
	int hurtVar;
	Sprite *sprite_monster;
	bool scope = false;
	bool befreeze = false;
	bool alreadyfreeze = false;
	//****************
	bool isOut = false;
	int Monster::getGoldBonus();
	int monster_type;
	//******************

private:
	//***********
	int goldBonus = 1;
	//***********
	float initMX;
	float initMY;
	float Map_X;
	float Map_Y;
	float initScale;
	int rDirection;
	int hLevel;
	int turnPoint;
	int defence;
	float Blood;
	float movingSpeed;
	int ball1Mask = 1 << 0;
	int ball2Mask = 1 << 1;
	int Map;


};
#endif // __MONSTER_H__