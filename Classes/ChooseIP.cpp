#include "ChooseIP.h"



Scene* ChooseIP::createScene()
{
	auto scene = Scene::create();
	auto layer = ChooseIP::create();

	scene->addChild(layer);
	return scene;
}

bool ChooseIP::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	auto winSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("registerbackground.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, 0);

	auto refresh = MenuItemImage::create("Refresh-s.png", "Refresh-s.png",CC_CALLBACK_1(ChooseIP::refresh, this));	
	refresh->setPosition( winSize.width*0.2, winSize.height*0.5);

	auto connectbutton = Sprite::create("button-s.png");
	connectbutton->setPosition(winSize.width*0.8, winSize.height*0.5);
	this->addChild(connectbutton,-1);
	labelID_B.pushBack(connectbutton);
	auto connected = MenuItemFont::create("CONNECT", CC_CALLBACK_1(ChooseIP::connect, this));
	connected->setColor(Color3B::WHITE);
	connected->setPosition( winSize.width*0.8, winSize.height*0.5);
	
	auto menu = Menu::create(refresh,connected, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	auto back = Sprite::create("Back_Arrow.png");
	back->setPosition(winSize.width / 5, winSize.height / 8);
	back->setScale(0.5);
	addChild(back);

	auto listen_b = EventListenerTouchOneByOne::create();
	listen_b->onTouchBegan = [back, this](Touch* t, Event* e)
	{
		if (back->getBoundingBox().containsPoint(t->getLocation()))
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, CreateJoin::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen_b, back);

	scheduleUpdate();
	IPtoJoin = "";

	
}


void ChooseIP::connect(Ref* sender)
{
	log("11111clickON%s", IPtoJoin.c_str());
	IPtoJoin = "192.168.1.7"; // 2/18 Modified Change this IP to play double game
	if (IPtoJoin == "")
	{
		CCLOG("You need to enter IP address");
		return;
	}
	
	auto scene = DoubleGameScene::createScene(IPtoJoin,0);
	Director::getInstance()->replaceScene(scene);
}

void ChooseIP::refresh(Ref *pSender)
{
	for (int i = 0; i < labelID.size(); i++)
	{
		labelID.at(i)->removeFromParent();
		labelID.erase(i);
	}
	for (int i = 0; i < labelID_B.size(); i++)
	{
		labelID_B.at(i)->removeFromParent();
		labelID_B.erase(i);
	}
	auto request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setTag("type is get");
	request->setUrl("10.25.70.125/getalladdr.php");
	request->setResponseCallback(CC_CALLBACK_2(ChooseIP::GETcompleted, this));

	auto client = HttpClient::getInstance();
	client->setTimeoutForConnect(10);
	client->send(request);
	request->release();
}

void ChooseIP::GETcompleted(HttpClient *client, HttpResponse *response)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	CCLOG("Response Code : %d ", response->getResponseCode());
	if (response->isSucceed())
	{
		std::vector<char> *ServerResponse = response->getResponseData();
		CCLOG("Response data is:");

		std::stringstream buffer;
		//put the response code into String stream, then output
		for (int j = 0; j < ServerResponse->size(); j++)
		{
			buffer << (*ServerResponse)[j];
		}
		std::string output = buffer.str();
		CCLOG("%s", output.c_str());

		std::vector<std::string> IPs;
		std::string delimiter = "***";
		size_t pos = 0;
		std::string token;
		while ((pos = output.find(delimiter)) != std::string::npos) 
		{
			token = output.substr(0, pos);
			IPs.push_back(token.c_str());
			CCLOG("%s",token.c_str());
			output.erase(0, pos + delimiter.length());
		}
		for (int i = 0; i < IPs.size(); i++)
		{
			auto ip_b = Sprite::create("button-s.png");
			ip_b->setPosition( visibleSize.width *0.5, visibleSize.height *0.85-(i*50));
			addChild(ip_b);
			auto id_label = Label::create();
			id_label->setString(IPs.at(i).substr(0, IPs.at(i).find(":")));
			id_label->setColor(Color3B::WHITE);
			id_label->setSystemFontSize(32);
			id_label->setPosition(visibleSize.width*0.5, visibleSize.height *0.85-(i*50));
			addChild(id_label, 2);
			labelID.pushBack(id_label);
			auto listen_ip = EventListenerTouchOneByOne::create();
			listen_ip->onTouchBegan = [ip_b, i,IPs, this](Touch* t, Event* e)
			{
				if (ip_b->getBoundingBox().containsPoint(t->getLocation()))
				{
					pointer = i;
					std::string divider = ":";
					std::string substr = IPs.at(i).substr(IPs.at(i).find(divider)+1, IPs.at(i).size());
					IPtoJoin = substr;
					log("clickON%s", IPtoJoin.c_str());
				}		 
				return true;
			};
			Director::getInstance()->getEventDispatcher()->
				addEventListenerWithSceneGraphPriority(listen_ip, ip_b);

		}
		//std::string divider = ":[";
		//std::string substr = IPs.at(1).substr(IPs.at(1).find(divider), IPs.at(i).length);

		/*auto visibleSize = Director::getInstance()->getVisibleSize();
		LabelTTF *label = LabelTTF::create(output.c_str(), "fonts/arial", 20);
		label->setPosition(visibleSize.width / 2, visibleSize.height/2);
		this->addChild(label);*/
	}
}

void ChooseIP::update(float dt)
{
	for (int i = 0; i < labelID.size(); i++)
	{
		if (i==pointer)
			labelID.at(i)->setColor(Color3B::RED);
		else
			labelID.at(i)->setColor(Color3B::WHITE);
	}
}