#include"UserInfoScene.h"

Scene* UserInfoScene::createScene()
{
	auto s = Scene::create();
	auto l = UserInfoScene::create();
	s->addChild(l);
	return s;

}

bool UserInfoScene::init()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("doubleSelect.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);

	auto back = Sprite::create("Back_Arrow.png");
	back->setPosition(visibleSize.width / 5, visibleSize.height / 8);
	back->setScale(0.5);
	addChild(back);

	auto listen_b = EventListenerTouchOneByOne::create();
	listen_b->onTouchBegan = [back, this](Touch* t, Event* e)
	{
		if (back->getBoundingBox().containsPoint(t->getLocation()))
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, HomeScene::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_b, back);

	std::string PlayerName = ACCOUNT;
	std::string Email = MAILADDR;
	std::string NickName = NICKNAME;
	int Level = LEVELLOCK;

	//CCLOG("%d", succevisibleSize)
	auto backspace1 = Sprite::create("button-s.png");
	backspace1->setPosition(visibleSize.width / 2, visibleSize.height*0.85);
	this->addChild(backspace1);
	LabelTTF *labela = LabelTTF::create("User Name", "fonts/arial", 20);
	labela->setColor(Color3B::WHITE);
	labela->setPosition(visibleSize.width / 2, visibleSize.height*0.85);
	this->addChild(labela);
	LabelTTF *label1 = LabelTTF::create(PlayerName.c_str(), "fonts/arial", 20);
	label1->setColor(Color3B::BLACK);
	label1->setPosition(visibleSize.width / 2, visibleSize.height*0.75);
	this->addChild(label1);

	auto backspace2 = Sprite::create("button-s.png");
	backspace2->setPosition(visibleSize.width / 2, visibleSize.height*0.65);
	this->addChild(backspace2);
	LabelTTF *labelb = LabelTTF::create("Email Address", "fonts/arial", 20);
	labelb->setColor(Color3B::WHITE);
	labelb->setPosition(visibleSize.width / 2, visibleSize.height*0.65);
	this->addChild(labelb);
	LabelTTF *label2 = LabelTTF::create(Email.c_str(), "fonts/arial", 20);
	label2->setColor(Color3B::BLACK);
	label2->setPosition(visibleSize.width / 2, visibleSize.height*0.55);
	this->addChild(label2);

	auto backspace3 = Sprite::create("button-s.png");
	backspace3->setPosition(visibleSize.width / 2, visibleSize.height*0.45);
	this->addChild(backspace3);
	LabelTTF *labelc = LabelTTF::create("Nickname", "fonts/arial", 20);
	labelc->setColor(Color3B::WHITE);
	labelc->setPosition(visibleSize.width / 2, visibleSize.height*0.45);
	this->addChild(labelc);
	LabelTTF *label3 = LabelTTF::create(NickName.c_str(), "fonts/arial", 20);
	label3->setColor(Color3B::BLACK);
	label3->setPosition(visibleSize.width / 2, visibleSize.height*0.35);
	this->addChild(label3);

	auto backspace4 = Sprite::create("button-s.png");
	backspace4->setPosition(visibleSize.width / 2, visibleSize.height*0.25);
	this->addChild(backspace4);
	LabelTTF *labeld = LabelTTF::create("Current Level", "fonts/arial", 20);
	labeld->setColor(Color3B::WHITE);
	labeld->setPosition(visibleSize.width / 2, visibleSize.height*0.25);
	this->addChild(labeld);
	char buf[20];
	sprintf(buf, "%d", Level);
	LabelTTF *label4 = LabelTTF::create(buf, "fonts/arial", 20);
	label4->setColor(Color3B::BLACK);
	label4->setPosition(visibleSize.width / 2, visibleSize.height*0.15);
	this->addChild(label4);

	//auto request = new HttpRequest();
	//request->setTag("Type is POST");
	//request->setUrl("10.25.70.125/demo2Login.php");
	////Set request type
	//request->setRequestType(HttpRequest::Type::POST);

	//// adjust data form to be receivable to server
	//CCLOG("%s,%s", ACCOUNT, COMBINATION);
	//std::string combination = "username=" + ACCOUNT+"&userpavisibleSize=" + COMBINATION;;

	//// build two variables in a String as the request
	//__String *toSend = __String::create(combination);
	//request->setRequestData(toSend->getCString(), toSend->length());
	//request->setResponseCallback(CC_CALLBACK_2(UserInfoScene::complete2, this));
	//// call the Welcom::complete2 when program receives server's response

	//// Build a client instance to send the request to server Register.php
	//auto client2 = HttpClient::getInstance();
	//client2->setTimeoutForConnect(10);
	//client2->send(request);
	//request->release(); // after sending, release the request

	return true;
}

//void UserInfoScene::complete2(HttpClient *client, HttpResponse *response)
//{
//	auto visibleSize = Director::getInstance()->getvisibleSize();
//	CCLOG("Response Tag is %s", response->getHttpRequest()->getTag());
//	CCLOG("Respnse Code : %d ", response->getResponseCode());
//	if (response->ivisibleSizeucceed())
//	{
//		// build a buffer to restore server's reponse
//		std::vector<char> *ServerResponse = response->getResponseData();
//		char *concatenated = (char*)malloc(ServerResponse->size() + 1);
//		// convert the response to a long, complete string
//		std::string tempString(ServerResponse->begin(), ServerResponse->end());
//		strcpy(concatenated, tempString.c_str());
//
//		// build a json object with the string and parse this object to get its variables in different index
//		Json *json = Json_create(concatenated);
//		int  succevisibleSize = Json_getInt(json, "succevisibleSize", -1);


		//if (succevisibleSize == 1) // if the "succevisibleSize" value is 1, i.e. a match, jump to the next screen
		//{
		//	auto scene = HomeScene::createScene();
		//	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
		//}
		//else  //  if the "succevisibleSize" value is 0, the username and pavisibleSizeword don't match.
		//{
		//	auto errMSG = Sprite::create("error.png");
		//	errMSG->setPosition(Point(visibleSize.width *0.5, visibleSize.height *0.525));

		//	this->addChild(errMSG, 1);

		//	CCActionInterval *fadeout = CCFadeOut::create(2.5);
		//	errMSG->runAction(fadeout);
		//}


		//LabelTTF *label = LabelTTF::create(succevisibleSize, "fonts/arial", 25);
		//label->setPosition(visibleSize.width / 2, visibleSize.height*0.15);
		//this->addChild(label);

		//CCLOG("Response data is:");
		//	for (int i = 0; i < ServerResponse->size(); i++)
		//	{
		//		CCLOG("%c", (*ServerResponse)[i]);
		//	}
		//put the response code into String stream, then output

		//std::stringstream buffer;	
		//for (int j = 0; j < ServerResponse->size(); j++)
		//{
		//	buffer << (*ServerResponse)[j];
		//}
		//std::string output = buffer.str();

		//LabelTTF *label = LabelTTF::create(output.c_str(), "fonts/arial", 10);
		//label->setPosition(visibleSize.width / 2, visibleSize.height*0.15);
		//this->addChild(label);

//	}
//	else
//	{
//		CCLOG("Error MSG is : %s", response->getErrorBuffer());
//	}
//}