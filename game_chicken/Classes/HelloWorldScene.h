#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
private:
    cocos2d::CCArray *arrayChicken;
    cocos2d::CCArray *arrayEgg;
    cocos2d::CCArray *arrayTrough;
    cocos2d::CCSprite *basket;
    cocos2d::CCPoint touchLocation;
    int sumPoint;
    cocos2d:: CCSprite * textSumPoint;
    int level;
    bool isUpLevel1;
    bool isUpLevel2;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    
    //--------------------
    void addEgg();
    void addChickenAndTrough();
    void gamelogicAddEgg(float dt);
    void update(float dt);
    void updateLevel(float dt);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touch,cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
