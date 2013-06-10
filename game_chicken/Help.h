//
//  Help.h
//  game_chicken
//
//
//

#ifndef game_chicken_Help_h
#define game_chicken_Help_h
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
class Help : public cocos2d::CCLayerColor
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(Help);
    
	void menu_home(CCObject* obj);

	void home();
private:
    
};



#endif
