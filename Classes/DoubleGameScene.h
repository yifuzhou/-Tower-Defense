#ifndef __DOUBLE_GAME_SCENE_H__
#define __DOUBLE_GAME_SCENE_H__
#include"cocos2d.h"
#include"iostream"
#include"Monster.h"
#include"tower.h"
#include"bullet.h"
#include <sstream>
#include "PublicVar.h"
#include "SingleGameScene.h"


//add socket
#include "network\HttpRequest.h"
#include "network\HttpClient.h"
#include "network\HttpResponse.h"
#include <thread>
#include <winsock2.h>
#pragma comment(lib,"WS2_32.lib")

using namespace cocos2d;

class  DoubleGameScene :public Layer
{
private:
	int nextFrameCout;
	int currentFrameIndex;
	int limitFrameIndex;
	int group = 1;
	void resetFrames(int);
	void addSoldiers(int);
	void addBase(float x, float y, float scale);
	void addField();

	void Host_monsterAttack();
	void Host_towerAttack();
	void Guest_monsterAttack();
	void Guest_towerAttack();

	int counter = 0;
	bool wait;
	bool isStart;
	void StartPlay(cocos2d::Ref* pSender);

	int d_path;

	float H_X;
	float H_Y;
	float H_Scale;
	float G_X;
	float G_Y;
	float G_Scale;

	bool BUILD;
	int t_field;
	int t_tower;

	int GDeleteS;
	bool wantDeleteS;

		//For Game Part-Han
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
	/*int ntime = 3;
	char ntimearr[100] = { '0' };
	Label* ntimeboard;
*/
	Label* gameover;
	Label* quitgame;

	int wave = 1;
	char wavearr[100] = { '0' };
	Label* waveboard;


	Label* winninggame;
	//*************

	//build tower
	bool buildtower(float position_x, float position_y, Sprite* field, int place);
	bool menuopened = false;



public:
	virtual bool init();
	CREATE_FUNC(DoubleGameScene);
	static Scene* createScene(std::string IPtoJoin, int isHost);
	virtual void update(float);
	Vector<Monster*> HsoldierVector;
	Vector<tower*> HtowerVector;
	Vector<Monster*> GsoldierVector;
	Vector<tower*> GtowerVector;
	Point fieldVector[10];
	bool touchToBuild(Touch*touch, Event* event);
	void guestMapBuildTower(float x, float y);


	//For Host
	SOCKADDR_IN addrSrv;
	char sendBuf[100];
	char recvBuf[100];
	SOCKADDR_IN addrClient;
	bool jump;
	bool connected;
	SOCKET _server;
	SOCKET _client;
	void ThreadAccept(SOCKET s, sockaddr *addr, int *addrlen);
	std::string Convert(float Num);
	void POSTcompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
	void startServer();
	void startClient();
	void sendIP(std::string nickname);
	bool serverSend(std::string message);
	void BackToHome(Ref *pSender);

	//For Guest
	void receive();
	SOCKET sockClient;
	char recvBuffer[100];
	bool end;
	bool clientSend(std::string message);
	void AllClean();

	//For singleGame Part adding
	bool gameisover = false;
	void quitgamescene(cocos2d::Ref * pSender);
	void updateGold(int gold);
	void upgradeTower(tower*, float, float);
	bool magicused = false;
	//bool winistrue = false;
	bool hascircle = false;


};
#endif // __DOUBLE_GAME_SCENE_H__