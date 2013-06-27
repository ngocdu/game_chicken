#include "GamePlay.h"
#include "SimpleAudioEngine.h"
#include "Egg.h"
#include "Menu_Game.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GamePlay::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GamePlay *layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
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
                                        menu_selector(GamePlay::menuCloseCallback) );
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
    pSprite->setPosition( ccp(size.width / 2, size.height / 2) );

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
    
    
    CCLabelTTF *lbPoint=CCLabelTTF::create("Point: ", "Times New Roman", 24);
    lbPoint->setPosition(ccp(35,size.height/2));
    this->addChild(lbPoint,5);
    
    CCTexture2D *txPoint=new CCTexture2D();
    char strPoint[20] ={0};
    sprintf(strPoint, "%i",sumPoint);
    txPoint->initWithString(strPoint,"Times New Roman", 24);
    
    textSumPoint=CCSprite::createWithTexture(txPoint);
    textSumPoint->setPosition(ccp(70, size.height / 2));
    this->addChild(textSumPoint);
    
    
    CCLabelTTF *lbLevel=CCLabelTTF::create("Level: ", "Times New Roman", 24);
    lbLevel->setPosition(ccp(35,size.height/ 2 - 25));
    this->addChild(lbLevel);
    
    CCTexture2D *txLevel=new CCTexture2D();
    char strLevel[20] ={0};
    sprintf(strLevel, "%i",level);
    txLevel->initWithString(strLevel,"Times New Roman", 24);
    
    textLevel=CCSprite::createWithTexture(txLevel);
    textLevel->setPosition(ccp(70,size.height / 2 - 25));
    this->addChild(textLevel);
    
    
    basket = CCSprite::create("giotrung.png");
    basket->cocos2d::CCNode::setPosition(size.width / 2, 20);
    basket->setScale(0.6);
    this->addChild(basket,1);
    
    //CCSprite *sq = (CCSprite*)i;
    
    // pause button
    CCMenuItem* item2 = CCMenuItemFont::create("Pause", this,
                                            menu_selector(GamePlay::onPause) );
    CCMenu* menuP = CCMenu::create(item2, NULL);
    menuP->setPosition( ccp(size.width - 40, 50) );
    
    this->addChild( menuP );
    
    this->addChickenAndTrough();
    this->schedule(schedule_selector(GamePlay::gamelogicAddEgg), 3);
    this->schedule(schedule_selector(GamePlay::update), 1/50);
    
    return true;
}
bool GamePlay::ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent* event)
{
	CCPoint location=touch->getLocationInView();
	location=CCDirector::sharedDirector()->convertToGL(location);
	
	this->touchLocation = location;
    return true;
}
void GamePlay::ccTouchesMoved(cocos2d::CCSet* touch,cocos2d::CCEvent* event)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCTouch *touch1 = (CCTouch*)(touch->anyObject());
	CCPoint p2 = touch1->getLocationInView();
	touchLocation=CCDirector::sharedDirector()->convertToGL(p2);
    if (touchLocation.y < size.height/2) {
        basket->setPosition(touchLocation);
    }
    
}
void GamePlay::ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event)
{
	
}
void GamePlay::addChickenAndTrough()
{
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    //-----------1----------------
    CCSprite * troughleft1 = CCSprite::create("keleft.png");
    troughleft1->setPosition(ccp(size.width / 10, size.height * 4 / 6));
    arrayTrough->addObject(troughleft1);
    this->addChild(troughleft1);
    CCSprite *chikenleft1 = CCSprite::create("gatraibt.png");
    chikenleft1->setPosition(ccp(troughleft1->getPositionX(), troughleft1->getPositionY() +
            troughleft1->getContentSize().height/2 + chikenleft1->getContentSize().height/2));
    arrayChicken->addObject(chikenleft1);
    this->addChild(chikenleft1,4);
    
    //---------2---------
    CCSprite * troughleft2 = CCSprite::create("keleft.png");
    troughleft2->setPosition(ccp(size.width * 5/10, size.height * 4/6));
    arrayTrough->addObject(troughleft2);
    this->addChild(troughleft2);
    CCSprite *chikenleft2= CCSprite::create("gatraibt.png");
    chikenleft2->setPosition(ccp(troughleft2->getPositionX(), troughleft2->getPositionY() +
            troughleft2->getContentSize().height/2+chikenleft2->getContentSize().height/2));
    arrayChicken->addObject(chikenleft2);
    this->addChild(chikenleft2, 4);

    //---------3-----------
    CCSprite * troughleft3 = CCSprite::create("keleft.png");
    troughleft3->setPosition(ccp(size.width* 8.5/10, size.height * 4/6));
    arrayTrough->addObject(troughleft3);
    this->addChild(troughleft3);
    CCSprite *chikenleft3 = CCSprite::create("gatraibt.png");
    chikenleft3->setPosition(ccp(troughleft3->getPositionX(), troughleft3->getPositionY() +
            troughleft3->getContentSize().height/2+chikenleft3->getContentSize().height/2));
    arrayChicken->addObject(chikenleft3);
    this->addChild(chikenleft3,4); 
}

void GamePlay::addEgg()
{
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
        if(d == ra)
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
    
    CCRotateTo *rotate1 = CCRotateTo::create(0.5, 25);
    CCRotateTo *rotate2 = CCRotateTo::create(0.5, 0);
    CCSequence *sq = CCSequence::createWithTwoActions(rotate1, rotate2);
    chicken->runAction(sq);
    
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
    
    e->setDuritionMove(8);
    e->setPosition(ccp(point.x - chicken->getContentSize().width / 2 + 20, point.y -
                       chicken->getContentSize().height / 2));
    
    CCPoint p1 = ccp(chicken->getPosition().x - chicken->getContentSize().width / 2 +
        20, chicken->getPosition().y - chicken->getContentSize().height/2 - trough->getContentSize().height/2);
    CCPoint p2 = ccp(p1.x + trough->getContentSize().width - 10, p1.y);
    CCPoint p3 = ccp(p2.x, 80);
    e->move(p1, p2, p3);
    arrayEgg->addObject(e);
    this->addChild(e, 3);
    
    SimpleAudioEngine::sharedEngine()->playEffect("sound3.mp3");
}
void GamePlay::gamelogicAddEgg(float dt)
{
    this->addEgg();
}
void GamePlay::update(float dt)
{
    CCObject *i;
    CCObject *j;
    CCArray *arRemoveEggTrue = new CCArray();//mang nhung qua trung duoc hung
    CCArray *arRemoveEggFalse = new CCArray();
    CCARRAY_FOREACH(arrayEgg, i)
    {
        Egg *e = (Egg*)i;
        int kc = ccpDistance(basket->getPosition(), e->getPosition());
        float kc2 = sqrtf(basket->getContentSize().height/2 * basket->getContentSize().height/2 +
                          basket->getContentSize().width/2 * basket->getContentSize().width/2);
        if(kc < basket->getContentSize().height/2 &&
           e->getPosition().x >= basket->getPosition().x - basket->getContentSize().width/2 +
           e->getContentSize().width/2
           &&  e->getPosition().x <= basket->getPosition().x +
           basket->getContentSize().width/2 - e->getContentSize().width/2 )
        {
            arRemoveEggTrue->addObject(e);
            
        }
        if(kc < kc2-5 && ((e->getPosition().x > basket->getPosition().x -
                           basket->getContentSize().width/2 - e->getContentSize().width/2
            && e->getPosition().x < basket->getPosition().x - basket->getContentSize().width/2 +
               e->getContentSize().width/2)||(e->getPosition().x < basket->getPosition().x +
               basket->getContentSize().width/2 + e->getContentSize().width/2
            && e->getPosition().x >= basket->getPosition().x +
               basket->getContentSize().width/2 - e->getContentSize().width)))
        {
            arRemoveEggTrue->addObject(e);
            CCSprite * eggV =CCSprite::create("eggVo.png");
            eggV->setScale(0.12);
            eggV->setPosition(e->getPosition());
            CCFadeOut *fade = CCFadeOut::create(3);
            CCMoveTo *move = CCMoveTo::create(2, ccp(e->getPositionX(), 50));
            CCCallFuncN *remove = CCCallFuncN::create(this,
                            callfuncN_selector(GamePlay::removeSprite));
            CCArray *ar =new CCArray();
            ar->addObject(move);
            ar->addObject(fade);
            ar->addObject(remove);
            CCSequence *sq = CCSequence::create(ar);
            eggV->runAction(sq);
            this->addChild(eggV, 5);
            
        }
        //xoa nhung qua trung roi xong
        CCSprite * eggV;
        if (e->getDeleted()==true) {
            arRemoveEggFalse->addObject(e);
            
            if (e->getPoint()==0) {
                eggV = CCSprite::create("egg1.png");
                eggV->setScale(0.15);
            }
            else if (e->getPoint() == 1)
            {
                eggV = CCSprite::create("egg2.png");
                eggV->setScale(0.12);
            }
            else {
                eggV = CCSprite::create("egg2.png");
                eggV->setScale(0.12);
            }
            
            eggV->setPosition(e->getPosition());
            CCFadeOut *fade = CCFadeOut::create(3);
            CCCallFuncN *remove = CCCallFuncN::create(this,
                                callfuncN_selector(GamePlay::removeSprite));
            CCSequence *sq = CCSequence::createWithTwoActions(fade, remove);
            eggV->runAction(sq);
            this->addChild(eggV);
        }
    }
    CCARRAY_FOREACH(arRemoveEggTrue, j)
    {
        Egg *e =(Egg*)j;
        
        if (e->getPoint() != 0) {
            sumPoint += (e->getPoint() + 1) * 2;
        }
        else if (e->getPoint() == 0)
        {
            sumPoint -= 5;
        }
        
        arrayEgg->removeObject(e);
        this->removeChild(e, true);  
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
    char strPoint[20] ={ 0 };
    sprintf(strPoint, "%i", sumPoint);
    txPoint->initWithString(strPoint, "Times New Roman", 24);
    textSumPoint->setTexture(txPoint);
    
    
    CCTexture2D *txLevel=new CCTexture2D();
    char strLevel[20] ={ 0 };
    sprintf(strLevel, "%i", level);
    txLevel->initWithString(strLevel, "Times New Roman", 24);
    textLevel->setTexture(txLevel);
    
    if (sumPoint >= level * 30) {
        level++;
        if (level <= 5) {
            this->schedule(schedule_selector(GamePlay::gamelogicAddEgg), 3-level/2);
            basket->setScale(basket->getScale() + 0.1);
        }
    }
    
    // win
    if (sumPoint>=500) {
        this->unschedule(schedule_selector(GamePlay::gamelogicAddEgg));
        CCLabelTTF *win =CCLabelTTF::create("You win", "Times New Roman", 40);
        win->setPosition(ccp(240, 200));
        this->addChild(win);
    }
    
    if (sumPoint<0) {
        this->unschedule(schedule_selector(GamePlay::gamelogicAddEgg));
        CCLabelTTF *fail =CCLabelTTF::create("You fail", "Times New Roman", 40);
        fail->setPosition(ccp(240, 200));
        this->addChild(fail);
    }
    
}
void GamePlay::updateLevel(float dt)
{
    if (sumPoint > 50*level && isUpLevel1==false) {
        level += 1;
        isUpLevel2 = true;
        this->unschedule(schedule_selector(GamePlay::gamelogicAddEgg));
        this->schedule(schedule_selector(GamePlay::gamelogicAddEgg), 4/level);
    }
}
void GamePlay::removeSprite(cocos2d::CCNode *node)
{
    CCSprite *sp = (CCSprite*)node;
    this->removeChild(sp, true);
}
void GamePlay::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(Menu_Game::scene());
}
void GamePlay::onPause(cocos2d::CCObject *node)
{
    if(CCDirector::sharedDirector()->isPaused())
        CCDirector::sharedDirector()->resume();
    else
        CCDirector::sharedDirector()->pause();
}
int GamePlay::readFile(char *filename)
{
    FILE *f;
    int level =0;
    f = fopen(filename, "rt");
    while (!feof(f)) {
        fscanf(f, "%i", &level);
    }
    fclose(f);
    return level;
}
void GamePlay::writeFile(int level, char *filename)
{
    FILE *f;
    f =fopen(filename, "w");
    fprintf(f, "%i", level);
    fclose(f);
}