//
//  Help.cpp
//  game_chicken
//
//
//

#include "Help.h"
#include "HelloWorldScene.h"
#include "Menu_Game.h"
using namespace cocos2d;

CCScene * Help::scene()
{
	CCScene* scene=NULL;
	do
	{
		scene=CCScene::create();
		Help * layer=Help::create();
		scene->addChild(layer);
	}while(0);
	return scene;
}
bool Help::init()
{
	bool bRet=false;
	do
	{
		if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		{
			return false;
		}
		this->setTouchEnabled(true);
        // ask director the window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        
        // add "HelloWorld" splash screen"
        CCSprite* pSprite = CCSprite::create("nenf.png");
        pSprite->setScaleX((float)(size.width/pSprite->getContentSize().width));
        pSprite->setScaleY((float)(size.height/pSprite->getContentSize().height));
        // position the sprite on the center of the screen
        pSprite->setPosition( ccp(size.width/2, size.height/2) );
        
        
        // add the sprite as a child to this layer
        this->addChild(pSprite, 0);
		//menu Font
		CCMenuItemFont* menuItemFontA=CCMenuItemFont::create("Back",this,menu_selector(Help::menu_home));
		menuItemFontA->setFontSizeObj(30);
		menuItemFontA->setColor(ccc3(1,198,1));

		CCMenu * menu=CCMenu::create(menuItemFontA,NULL);
		menu->setPosition(size.width-30, 10);
		this->addChild(menu);
        
		CCLabelTTF *fail =CCLabelTTF::create("You have to move the basket to catch the eggs \n the eggs attention black dodge\n and avoid the eggs fall to the floor.", "Times New Roman", 18);
        fail->setPosition(ccp(240, 200));
        //fail->setColor(ccc3(100, 100, 240));
        this->addChild(fail);
        
		bRet=true;
	}while(0);
	return bRet;
}

void Help::menu_home(CCObject * obj)
{
	this->home();
}

void Help::home()
{
    CCDirector::sharedDirector()->replaceScene(Menu_Game::scene());
	
}