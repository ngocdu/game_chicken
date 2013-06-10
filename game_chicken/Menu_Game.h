//
//  Menu_Game.h
//  game_chicken
//
//
//

#ifndef game_chicken_Menu_Game_h
#define game_chicken_Menu_Game_h
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
class Menu_Game : public cocos2d::CCLayerColor
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(Menu_Game);
    
	void menu_play(CCObject* obj);

	void menu_option(CCObject* obj);

	void menu_exit(CCObject* obj);
	void play();

	void option();
	void exit1();
private:
    
};

#endif
