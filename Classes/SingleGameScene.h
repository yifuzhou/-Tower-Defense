#ifndef __SINGLE_GAME_SCENE_H__
#define __SINGLE_GAME_SCENE_H__
#include"cocos2d.h"
//#include"HelloWorldScene.h"
#include"Monster.h"
#include"tower.h"
#include"bullet.h"
#include "HelloWorldScene.h"
//#include"HomeScene.h"

using namespace cocos2d;

class  SingleGameScene :public Layer
{
private:
	int nextFrameCout;
	int currentFrameIndex;
	int limitFrameIndex;
	int group = 1;
	void resetFrames(int);
	void addSoldiers(int);
	void addBase();
	void addField();
	void monsterAttack();
	void towerAttack();
	int counter = 0;
	bool wait;
	int ball1Mask = 1 << 0;
	int ball2Mask = 1 << 1;
	int d_path;

	//*************
	int score = 0;
	char scorearr[100] = { '0' };
	Label* scoreboard;

	int hitpoint = 3;
	char hitpointarr[500] = { '0' };
	Label* HP;

	int gold = 10;
	char goldarr[2000] = { '0' };
	Label* GOLD;

	int ntime = 3;
	char ntimearr[100] = { '0' };
	Label* ntimeboard;

	Label* gameover;
	Label* quitgame;

	int wave = 1;
	char wavearr[100] = { '0' };
	Label* waveboard;


	Label* winninggame;
	//*************

	//build tower
	bool buildtower(float position_x, float position_y, Sprite* field, int place);
	bool menuopened=false;
	
	
public:
	//******
	void SingleGameScene::updateGold(int gold);
	//*********

	virtual bool init();
	CREATE_FUNC(SingleGameScene);
	static Scene* createScene();
	virtual void update(float);
	Vector<Monster*> soldierVector;
	Vector<tower*> towerVector;
	bool touchToBuild(Touch*touch, Event* event);
	bool onContactBegin(const PhysicsContact& contact);
	//void OnUpdate(float dt);
	void upgradeTower(tower*,float,float);
	void menuCloseCallback(cocos2d::Ref * pSender);
	void magic(cocos2d::Ref * pSender);
	void quitgamescene(cocos2d::Ref * pSender);
	bool magicused = false;
	bool gameisover = false;
	//bool winistrue = false;
	bool hascircle = false;
	void letswin();

};
#endif // __SINGLE_GAME_SCENE_H__