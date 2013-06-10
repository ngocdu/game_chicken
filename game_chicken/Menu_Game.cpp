//
//  Menu_Game.cpp
//  game_chicken
//
//  Created by MinhNT on 13/06/10.
//
//
#include "HelloWorldScene.h"
#include "Menu_Game.h"
#include "Help.h"
using namespace cocos2d;

CCScene * Menu_Game::scene()
{
	CCScene* scene=NULL;
	do
	{
		scene=CCScene::create();
		Menu_Game * layer=Menu_Game::create();
		scene->addChild(layer);
	}while(0);
	return scene;
}
bool Menu_Game::init()
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
		CCMenuItemFont* menuItemFontA=CCMenuItemFont::create("PLAY",this,menu_selector(Menu_Game::menu_play));
		menuItemFontA->setFontSizeObj(30);
		menuItemFontA->setColor(ccc3(1,198,1));
       
		CCMenuItemFont* menuItemFont2=CCMenuItemFont::create("HELP",this,menu_selector(Menu_Game::menu_option));
		menuItemFont2->setFontSizeObj(30);
		menuItemFont2->setColor(ccc3(1,1,1));
        
		CCMenuItemFont* menuItemFont3=CCMenuItemFont::create("EXIT",this,menu_selector(Menu_Game::menu_exit));
		menuItemFont3->setFontSizeObj(30);
		menuItemFont3->setColor(ccc3(198,198,198));
        
		CCMenu * menu=CCMenu::create(menuItemFontA,menuItemFont2,menuItemFont3,NULL);
		menu->alignItemsVertically();
		this->addChild(menu);
        
		
        
		bRet=true;
	}while(0);
	return bRet;
}

void Menu_Game::menu_play(CCObject * obj)
{
	this->play();
}

void Menu_Game::menu_option(CCObject* obj)
{
	this->option();
}
void Menu_Game::menu_exit(CCObject* obj)
{
	this->exit1();
}

void Menu_Game::play()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	
}

void Menu_Game::option()
{
	CCDirector::sharedDirector()->replaceScene(Help::scene());
}

void Menu_Game::exit1()
{
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
