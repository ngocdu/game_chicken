#ifndef __GamePlay_SCENE_H__
#define __GamePlay_SCENE_H__

#include "cocos2d.h"

class GamePlay : public cocos2d::CCLayer
{
private:
    cocos2d::CCArray *arrayChicken;
    cocos2d::CCArray *arrayEgg;
    cocos2d::CCArray *arrayTrough;
    cocos2d::CCSprite *basket;
    cocos2d::CCPoint touchLocation;
    int sumPoint;
    cocos2d:: CCSprite * textSumPoint;
    cocos2d:: CCSprite * textLevel;
    int level;
    bool isUpLevel1;
    bool isUpLevel2;
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    //--------------------
    void addEgg();
    void addChickenAndTrough();
    void gamelogicAddEgg(float dt);
    void update(float dt);
    void updateLevel(float dt);
    int readFile(char * c);
    void writeFile(int level, char * c);
    
    void onPause(cocos2d::CCObject *node);
    
    void removeSprite(cocos2d::CCNode *node);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touch,cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GamePlay);
};

#endif // __GamePlay_SCENE_H__
