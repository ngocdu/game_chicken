#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Egg.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);



    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

   
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("nenkaka.png");
    pSprite->setScaleX((float)(size.width/pSprite->getContentSize().width));
    pSprite->setScaleY((float)(size.height/pSprite->getContentSize().height));
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    //-----------------------------------------------------------
    arrayChicken = new CCArray();
    arrayEgg = new CCArray();
    arrayTrough = new CCArray();
    sumPoint = 0;
    level = 1;
    isUpLevel1 = false;
    isUpLevel2 = true;
    
    
    
    CCTexture2D *txPoint=new CCTexture2D();
    char strPoint[20] ={0};
    sprintf(strPoint, "%i",sumPoint);
    txPoint->initWithString(strPoint,"Times New Roman",24);
    
    textSumPoint=CCSprite::createWithTexture(txPoint);
    //textSumPoint->setTexture(txPoint);
    textSumPoint->setPosition(ccp(10,size.height/2));
    this->addChild(textSumPoint);
    
    
    basket = CCSprite::create("giotrung.png");
    basket->cocos2d::CCNode::setPosition(size.width/2, 20);
    this->addChild(basket,1);
    
    this->addChickenAndTrough();
    this->schedule(schedule_selector(HelloWorld::gamelogicAddEgg), 2);
    this->schedule(schedule_selector(HelloWorld::update), 1/40);
    
    return true;
}
bool HelloWorld::ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent* event)
{
	CCPoint location=touch->getLocationInView();
	location=CCDirector::sharedDirector()->convertToGL(location);
	
	this->touchLocation = location;
    return true;
}
void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touch,cocos2d::CCEvent* event)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCTouch *touch1 = (CCTouch*)(touch->anyObject());
	CCPoint p2 = touch1->getLocationInView();
	touchLocation=CCDirector::sharedDirector()->convertToGL(p2);
    if (touchLocation.y < size.height/2) {
        basket->setPosition(touchLocation);
    }
    
}
void HelloWorld::ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event)
{
	
}
void HelloWorld::addChickenAndTrough()
{
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    //-----------1----------------
    CCSprite * troughleft1 = CCSprite::create("keleft.png");
    troughleft1->setPosition(ccp(size.width/10,size.height*4/6));
    arrayTrough->addObject(troughleft1);
    this->addChild(troughleft1);
    CCSprite *chikenleft1 = CCSprite::create("gatraibt.png");
    chikenleft1->setPosition(ccp(troughleft1->getPositionX(),troughleft1->getPositionY()+troughleft1->getContentSize().height/2+chikenleft1->getContentSize().height/2));
    arrayChicken->addObject(chikenleft1);
    this->addChild(chikenleft1,4);
    
    //---------2---------
    CCSprite * troughleft2 = CCSprite::create("keleft.png");
    troughleft2->setPosition(ccp(size.width*5/10,size.height*4/6));
    arrayTrough->addObject(troughleft2);
    this->addChild(troughleft2);
    CCSprite *chikenleft2= CCSprite::create("gatraibt.png");
    chikenleft2->setPosition(ccp(troughleft2->getPositionX(),troughleft2->getPositionY()+troughleft2->getContentSize().height/2+chikenleft2->getContentSize().height/2));
    arrayChicken->addObject(chikenleft2);
    this->addChild(chikenleft2,4);

    //---------3-----------
    CCSprite * troughleft3 = CCSprite::create("keleft.png");
    troughleft3->setPosition(ccp(size.width*8.5/10,size.height*4/6));
    arrayTrough->addObject(troughleft3);
    this->addChild(troughleft3);
    CCSprite *chikenleft3 = CCSprite::create("gatraibt.png");
    chikenleft3->setPosition(ccp(troughleft3->getPositionX(),troughleft3->getPositionY()+troughleft3->getContentSize().height/2+chikenleft3->getContentSize().height/2));
    arrayChicken->addObject(chikenleft3);
    this->addChild(chikenleft3,4);

    
    
}

void HelloWorld::addEgg()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    int ra = rand() % 3;
    int ra1 = rand() % 3;
    
    int d=-1;
    CCPoint point;
    CCObject *i;
    CCObject *j;
    CCSprite * chicken;
    CCSprite * trough;
    CCARRAY_FOREACH(arrayChicken, i)
    {
        d++;
        if(d==ra)
        {
            chicken = (CCSprite*)i;
            point = chicken->getPosition();
        }
        
        
    }
    CCARRAY_FOREACH(arrayTrough, j)
    {
        trough = (CCSprite*)j;
        break;
    }
    Egg *e = new Egg(ra1);
    e->setDeleted(false);
    if (ra1==0) {
        e->initWithFile("den1.png");  
    }
    else if(ra1==1)
    {
         e->initWithFile("egg5.png"); 
    }
    else if(ra1==2)
    {
         e->initWithFile("vangegg1.png"); 
    }
    if (sumPoint<30) {
        e->setDuritionMove(8);
    }
    else if (sumPoint<60)
    {
        e->setDuritionMove(7);
    }
    else if (sumPoint<100)
    {
        e->setDuritionMove(6);
    }
    e->setPosition(ccp(point.x - chicken->getContentSize().width/2+20,point.y - chicken->getContentSize().height/2));
    
    CCPoint p1 = ccp(chicken->getPosition().x - chicken->getContentSize().width/2+20,chicken->getPosition().y - chicken->getContentSize().height/2 - trough->getContentSize().height/2);
    CCPoint p2 = ccp(p1.x + trough->getContentSize().width-10,p1.y);
    CCPoint p3 = ccp(p2.x,p2.y-150);
    
    
    e->move(p1,p2,p3);
    arrayEgg->addObject(e);
    this->addChild(e,3);
    
    
    
}
void HelloWorld::gamelogicAddEgg(float dt)
{
    this->addEgg();
}
void HelloWorld::update(float dt)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCObject *i;
    CCObject *j;
    CCArray *arRemoveEggTrue = new CCArray();
    CCArray *arRemoveEggFalse = new CCArray();
    CCARRAY_FOREACH(arrayEgg, i)
    {
        Egg *e = (Egg*)i;
        int kc = ccpDistance(basket->getPosition(), e->getPosition());
        if(kc < basket->getContentSize().height/2 && e->getPosition().x >= basket->getPosition().x-basket->getContentSize().width/2+e->getContentSize().width &&  e->getPosition().x <= basket->getPosition().x + basket->getContentSize().width/2 - e->getContentSize().width )
        {
            arRemoveEggTrue->addObject(e);
        }
        //xoa nhung qua trung roi xong
        if (e->getDeleted()==true) {
            arRemoveEggFalse->addObject(e);
        }
    }
    CCARRAY_FOREACH(arRemoveEggTrue, j)
    {
        Egg *e =(Egg*)j;
        arrayEgg->removeObject(e);
        this->removeChild(e, true);
        
        if (e->getPoint() != 0) {
            sumPoint += (e->getPoint()+1)*2;
        }
        else if (e->getPoint() == 0)
        {
            sumPoint -= 5;
        }
        
    }
    
    CCARRAY_FOREACH(arRemoveEggFalse, j)
    {
        Egg *e =(Egg*)j;
        arrayEgg->removeObject(e);
        this->removeChild(e, true);
        
        if (e->getPoint() != 0) {
            sumPoint -= 5;
        }
        
        
    }

    CCTexture2D *txPoint=new CCTexture2D();
    char strPoint[20] ={0};
    sprintf(strPoint, "%i",sumPoint);
    txPoint->initWithString(strPoint,"Times New Roman",24);
    textSumPoint->setTexture(txPoint);
    
    //-------------
//    if(sumPoint<0 || sumPoint > 200)
//    {
//        this->unschedule(schedule_selector(HelloWorld::gamelogicAddEgg));
//        this->unschedule(schedule_selector(HelloWorld::update));
//    }
    
}
void HelloWorld::updateLevel(float dt)
{
    if (sumPoint > 50*level && isUpLevel1==false) {
        level += 1;
        isUpLevel2 = true;
        this->unschedule(schedule_selector(HelloWorld::gamelogicAddEgg));
        this->schedule(schedule_selector(HelloWorld::gamelogicAddEgg), 4/level);
    }
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
