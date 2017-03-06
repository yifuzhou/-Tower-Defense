#include "Welcome.h"
#include "SimpleAudioEngine.h"
#include "Register.h"
#include "spine\Json.h"
//#include "HomeScene.h"

USING_NS_CC;

// declare to variables to store username and password
std::string EN;
std::string EC;

Scene* Welcome::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Welcome::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance, this is usually the "main" method
bool Welcome::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	// get the size of the screen in preparation for later positioning
    auto ScreenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto sprite = Sprite::create("background.png");
	sprite->setPosition(Vec2(ScreenSize.width / 2 + origin.x, ScreenSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	//Draw the background color
	/**
	auto background = DrawNode::create();
	background->drawSolidRect(origin, ScreenSize,Color4F::BLACK);
	this->addChild(background,0);
	*/
	//Add the "POKEMON" title with TTF
	auto title = Label::createWithTTF("POKEMON TD", "fonts/arial.ttf", 48);
	title->setPosition(Vec2(ScreenSize.width / 2, ScreenSize.height*0.8));
	title->setColor(Color3B::WHITE);
	this->addChild(title,2); // add the created component to the the current scene

	//Add the button for "Login" "Exit" and "Register" respectively
	auto submenu1 = MenuItemImage::create("login.png", "login.png", CC_CALLBACK_1(Welcome::toLogin, this));
	// the CALLBACK function calls the designated function when this submenu is clicked ,such as Welcome::toLogin
	auto submenu2 = MenuItemImage::create("register.png", "register.png", CC_CALLBACK_1(Welcome::toRegister, this));
	auto submenu3 = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(Welcome::toExit, this));

	//Set menu position
	submenu1->setPosition(Point((ScreenSize.width / 4)*2, ScreenSize.height*0.2));
	submenu2->setPosition(Point(ScreenSize.width / 4, ScreenSize.height*0.2));
	submenu3->setPosition(Point((ScreenSize.width / 4) * 3, ScreenSize.height*0.2));

	//Add the parent menu to include all three submenus
	auto *Menu = Menu::create(submenu1, submenu2, submenu3, NULL);
	Menu->setPosition(Point(0,0));
	this->addChild(Menu,2);

	// Add an editable text field -- EditBox for user to enter username
	ui::EditBox *entername = ui::EditBox::create(Size(220, 32), ui::Scale9Sprite::create("grey.png"));
	entername->setPosition(Vec2(ScreenSize.width*0.5, ScreenSize.height*0.685));
	entername->setFontSize(20);
	entername->setFontColor(Color3B::RED);
	entername->setPlaceHolder("Enter Username");//set the text in EditBox when nothing is entered
	entername->setPlaceholderFontColor(Color3B::GRAY);
	entername->setMaxLength(20); // limit the max number of letters this box can accept
	entername->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	entername->setInputMode(ui::EditBox::InputMode::ANY); 
	entername->setInputFlag(ui::EditBox::InputFlag::SENSITIVE); // sensitve means lower case is allowed
	entername->setTag(1);

	// Add an editable text field -- EditBox for user to enter password
	ui::EditBox *entercode = ui::EditBox::create(Size(220, 32), ui::Scale9Sprite::create("grey.png"));
	entercode->setPosition(Vec2(ScreenSize.width*0.5, ScreenSize.height*0.615));
	entercode->setFontSize(20);
	entercode->setFontColor(Color3B::RED);
	entercode->setPlaceHolder("Enter Password");
	entercode->setPlaceholderFontColor(Color3B::GRAY);
	entercode->setMaxLength(20);
	entercode->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	entercode->setInputMode(ui::EditBox::InputMode::ANY);
	entercode->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	entercode->setTag(2);

	// add these boxes to the scene
	this->addChild(entername,0);
	this->addChild(entercode,0);

	// Allow EditBox to call functions linked to it
	entername->setDelegate(this);
	entercode->setDelegate(this);

    return true;
}

// this method leads to the specific scene
void Welcome::toRegister(Ref *pSender)
{
	auto scene = Register::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

// When this method is called, the program send server data and check in database if username and password matches
void Welcome::toLogin(Ref *pSender)
{

	//Create a request of type POST
	auto request = new HttpRequest();
	request->setTag("Type is POST");
	request->setUrl("10.25.70.125/demo2Login.php");
	//Set request type
	request->setRequestType(HttpRequest::Type::POST);

	// adjust data form to be receivable to server
	std::string combination = "username=" + EN + "&userpass=" + EC;

	// build two variables in a String as the request
	__String *toSend = __String::create(combination);
	request->setRequestData(toSend->getCString(), toSend->length());
	request->setResponseCallback(CC_CALLBACK_2(Welcome::complete2, this));
	// call the Welcom::complete2 when program receives server's response

	// Build a client instance to send the request to server Register.php
	auto client2 = HttpClient::getInstance();
	client2->setTimeoutForConnect(10);
	client2->send(request);
	request->release(); // after sending, release the request


	//auto scene = HomeScene::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));

}

// The close method that end the program on clicking the button
void Welcome::toExit(Ref *pSender)
{

	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
}

// This method is called when an EditBox finished taking its input
void Welcome::editBoxReturn(cocos2d::ui::EditBox * editBox)
{
	// Different EditBox will all call this method, so we need to differentiate them using tags
	if (editBox->getTag() == 1)
	{
		EN = editBox->getText();
	}
	else 
	{
		EC = editBox->getText();
	}
}

void Welcome::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	//CCLOG("begin");
}

void Welcome::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	//CCLOG("end");

}

void Welcome::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	//CCLOG("changed");
}

// this method will be called when the program receives server's response
void Welcome::complete2(HttpClient *client, HttpResponse *response) 
{
	auto SS = Director::getInstance()->getVisibleSize();
	CCLOG("Response Tag is %s", response->getHttpRequest()->getTag());
	CCLOG("Respnse Code : %d ", response->getResponseCode());
	if (response->isSucceed())
	{
		// build a buffer to restore server's reponse
		std::vector<char> *ServerResponse = response->getResponseData();
		char *concatenated = (char*)malloc(ServerResponse->size() + 1);
		// convert the response to a long, complete string
		std::string tempString(ServerResponse->begin(), ServerResponse->end());
		strcpy(concatenated, tempString.c_str());

		// build a json object with the string and parse this object to get its variables in different index
		Json *json = Json_create(concatenated);
		int  success = Json_getInt(json, "success", -1);
		CCLOG("%d",success);
		
		if (success == 1) // if the "success" value is 1, i.e. a match, jump to the next screen
		{
			ACCOUNT = Json_getString(json, "username", "error");
			COMBINATION = EC;
			MAILADDR = Json_getString(json, "useremail", "error");
			NICKNAME = Json_getString(json, "usernickname", "error");
			LEVELLOCK = Json_getInt(json, "userscore", -1);
			EN = "";
			EC = "";
			auto scene = HomeScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
		}
		else  //  if the "success" value is 0, the username and password don't match.
		{
			auto errMSG = Sprite::create("error.png");
			errMSG->setPosition(Point(SS.width *0.5, SS.height *0.525));

			this->addChild(errMSG, 1);

			CCActionInterval *fadeout = CCFadeOut::create(2.5);
			errMSG->runAction(fadeout);
		}
		

		//LabelTTF *label = LabelTTF::create(success, "fonts/arial", 25);
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

	}
	else
	{
		CCLOG("Error MSG is : %s", response->getErrorBuffer());
	}
}