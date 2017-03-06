#include "Register.h"
#include "SimpleAudioEngine.h"
//#include "Welcome.h"


USING_NS_CC;

// declare 5 variables, the first four are to store user's register infomation
static std::string UN;
static std::string PW;
static std::string EM;
static std::string NN;
static cocos2d::Size SS;

Scene* Register::createScene()
{	
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Register::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Register::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

	auto ScreenSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SS = ScreenSize;

	// Add an editable text field -- EditBox for user to enter username
	ui::EditBox *username = ui::EditBox::create(Size(300, 40), ui::Scale9Sprite::create("grey.png"));
	username->setPosition(Vec2(ScreenSize.width / 2, ScreenSize.height*0.7));
	username->setFontSize( 20 );
	username->setFontColor(Color3B::RED);
	username->setPlaceHolder("USERNAME");
	username->setPlaceholderFontColor(Color3B::GRAY);
	username->setMaxLength(20);
	username->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	username->setInputMode(ui::EditBox::InputMode::ANY);
	username->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	username->setTag(1);

	// Add an editable text field -- EditBox for user to enter password
	ui::EditBox *password = ui::EditBox::create(Size(300, 40), ui::Scale9Sprite::create("grey.png"));
	password->setPosition(Vec2(ScreenSize.width / 2, ScreenSize.height*0.6));
	password->setFontSize(20);
	password->setFontColor(Color3B::RED);
	password->setPlaceHolder("PASSWORD");
	password->setPlaceholderFontColor(Color3B::GRAY);
	password->setMaxLength(20);
	password->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	password->setInputMode(ui::EditBox::InputMode::ANY);
	password->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	password->setTag(2);

	// Add an editable text field -- EditBox for user to enter email
	ui::EditBox *email = ui::EditBox::create(Size(300, 40), ui::Scale9Sprite::create("grey.png"));
	email->setPosition(Vec2(ScreenSize.width / 2, ScreenSize.height*0.5));
	email->setFontSize(20);
	email->setFontColor(Color3B::RED);
	email->setPlaceHolder("EMAIL");
	email->setPlaceholderFontColor(Color3B::GRAY);
	email->setMaxLength(20);
	email->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	email->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
	email->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	email->setTag(3);

	// Add an editable text field -- EditBox for user to enter nickname
	ui::EditBox *nickname = ui::EditBox::create(Size(300, 40), ui::Scale9Sprite::create("grey.png"));
	nickname->setPosition(Vec2(ScreenSize.width / 2, ScreenSize.height*0.4));
	nickname->setFontSize(20);
	nickname->setFontColor(Color3B::RED);
	nickname->setPlaceHolder("NICKNAME");
	nickname->setPlaceholderFontColor(Color3B::GRAY);
	nickname->setMaxLength(20);
	nickname->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	nickname->setInputMode(ui::EditBox::InputMode::ANY);
	nickname->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	nickname->setTag(4);

	// add these boxes to the scene
	this->addChild(username,2);
	this->addChild(password,2);
	this->addChild(email,2);
	this->addChild(nickname,2);

	// allow these EditBoxes to call related function
	username->setDelegate(this);
	password->setDelegate(this);
	email->setDelegate(this);
	nickname->setDelegate(this);

	auto sprite = Sprite::create("registerbackground.png");
	sprite->setPosition(Vec2(ScreenSize.width / 2 + origin.x, ScreenSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	auto title = Label::createWithTTF("Registration", "fonts/arial.ttf", 48);
	title->setPosition(Vec2(ScreenSize.width / 2, ScreenSize.height*0.9));
	title->setColor(Color3B::WHITE);
	this->addChild(title, 2);

	// define to buttons that let user submit their information to database or go back to last page
	auto submit = MenuItemImage::create("submit.png", "submit.png", CC_CALLBACK_1(Register::Confirm, this));
	submit->setPosition(Vec2(ScreenSize.width / 2, ScreenSize.height*0.25));
	auto toWelcome = MenuItemImage::create("Back_Arrow.png", "Back_Arrow.png", CC_CALLBACK_1(Register::goback, this));
	toWelcome->setPosition(Vec2(ScreenSize.width *0.2, ScreenSize.height/8));
	toWelcome->setScale(0.5);

	auto *Menu = Menu::create(submit,toWelcome, NULL);
	Menu->setPosition(Point(0, 0));
	this->addChild(Menu);
	    
    return true;
}

void Register::editBoxReturn(cocos2d::ui::EditBox * editBox)
{
	// store user's input(text) in declared variables according to EditBox's tag. 
	if (editBox->getTag() == 1)
	{
		UN = editBox->getText();
	}
	else if (editBox->getTag()==2)
	{
		PW = editBox->getText();
	}
	else if (editBox->getTag()==3)
	{
		EM = editBox->getText();
	}
	else if (editBox->getTag()==4)
	{
		NN = editBox->getText();
	}
	else
	{
	}
}

void Register::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	//CCLOG("begin");
}

void Register::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	//CCLOG("end");
}

void Register::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	//CCLOG("changed");
}

// this method is called when user click "submit". It sends user's registeration information to server, then to database
bool Register::Confirm(Ref *pSender)
{
	// count the spaces in username, if not zero, deny this username
	int count1=0;
	char buffer1[20] = "";
	strcpy(buffer1, UN.c_str());
	for (int i = 0; i < strlen(buffer1); i++)
	{
		if (buffer1[i] == ' ')
		{
			count1 = count1 + 1;
		}
	}

	// count the spaces in password, if not zero, deny this password
	int count2 = 0;
	char buffer2[20] = "";
	strcpy(buffer2, PW.c_str());
	for (int i = 0; i < strlen(buffer2); i++)
	{
		if (buffer2[i] == ' ')
		{
			count2 = count2 + 1;
		}
	}
	
	//If user enters nothing in "Username" or "Password" or either field contains space,
	//the program will reject the registration and print out error message
	if (UN=="" || PW=="" ||count1>0 || count2>0) //
	{
		auto errMSG = Sprite::create("invalid.png");
		errMSG->setPosition(Point(SS.width / 2, SS.height *0.8));

		this->addChild(errMSG,1);

		CCActionInterval *fadeout = CCFadeOut::create(2.5);
		errMSG->runAction(fadeout);

		return false;
	}
	//Create a request of type POST
	auto request = new HttpRequest();
	request->setTag("Type is POST");
	request->setUrl("10.25.70.125/demo2Register.php");
	//Set request type
	request->setRequestType(HttpRequest::Type::POST);

	// adjust data form to be receivable to server
	std::string combination = "username="+UN+"&userpass="+PW+"&useremail="+EM+"&usernickname="+NN;
		__String *toSend = __String::create(combination);
	request->setRequestData(toSend->getCString(), toSend->length());
	request->setResponseCallback(CC_CALLBACK_2(Register::complete1, this));

	//Create a client instance to send the request
	auto client = HttpClient::getInstance();
	client->setTimeoutForConnect(10);
	client->send(request);
	request->release();

	/*CCLOG("username is: %s",UN.c_str());
	CCLOG("password is: %s",PW.c_str());
	CCLOG("email is: %s",EM.c_str());
	CCLOG("nickname is: %s",NN.c_str());*/
	return true;
}

// this method will be called when the program receives server's response
void Register::complete1(HttpClient *client, HttpResponse *response)
{
	CCLOG("Response Tag is %s", response->getHttpRequest()->getTag());
	CCLOG("Respnse Code : %d ", response->getResponseCode());
	if (response->isSucceed())
	{
		std::vector<char> *ServerResponse = response->getResponseData();
		//CCLOG("Response data is:");
		//	for (int i = 0; i < ServerResponse->size(); i++)
		//	{
		//		CCLOG("%c", (*ServerResponse)[i]);
		//	}
		std::stringstream buffer;
		//put the response code into String stream, then output
		for (int j = 0; j < ServerResponse->size(); j++)
		{
			buffer << (*ServerResponse)[j];
		}
		std::string output = buffer.str();

		auto visibleSize = Director::getInstance()->getVisibleSize();

		LabelTTF *label = LabelTTF::create(output.c_str(), "fonts/arial", 25);
		label->setPosition(visibleSize.width / 2, visibleSize.height*0.15);
		this->addChild(label);
		Register::goback(this);// Go to Welcome page when registration is successfully done

		//CCLOG( output.c_str());
	}
	else
	{
		CCLOG("Error MSG is : %s", response->getErrorBuffer());
	}
}

// jump to Welcom scene
void Register::goback(Ref *pSender)
{
	auto scene = Welcome::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

