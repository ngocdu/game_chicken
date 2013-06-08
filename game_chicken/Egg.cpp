//
//  Egg.cpp
//  game_chicken
//
//  Created by MinhNT on 13/06/07.
//
//

#include "Egg.h"

using namespace std;
using namespace cocos2d;

// Fish *obj = new Fish("a",1);
Egg::Egg()
{
    
}

Egg::Egg(int point)
{
    this->point=point;
}

int Egg::getPoint()
{
    return this->point;
}
void Egg::setPoint(int point)
{
    this->point=point;
}

int Egg::getDirection()
{
    return this->direction;
}
void Egg::setDirection(int direction)
{
    this->direction = direction;
}
void Egg::move(cocos2d::CCPoint point,cocos2d::CCPoint point2,cocos2d::CCPoint point3)
{
    float durtion = this->getDuritionMove();
    CCMoveTo *move = CCMoveTo::create(durtion/10, point);
    CCMoveTo *move2 = CCMoveTo::create(durtion/2, point2);
    CCMoveTo *move3 = CCMoveTo::create(durtion/3, point3);
    CCCallFuncN *remove = CCCallFuncN::create(this, callfuncN_selector(Egg::removeEgg));
    CCArray *ar = new CCArray();
    ar->addObject(move);
    ar->addObject(move2);
    ar->addObject(move3);
    ar->addObject(remove);
    CCSequence *sq1 = CCSequence::create(ar);
    this->runAction(sq1);
    
    CCRotateTo *rotate1 = CCRotateTo::create(durtion/30, 45);
    CCRotateTo *rotate2 = CCRotateTo::create(durtion/30, 90);
    CCRotateTo *rotate3 = CCRotateTo::create(durtion/30, 135);
    CCRotateTo *rotate4 = CCRotateTo::create(durtion/30, 180);
    CCRotateTo *rotate5 = CCRotateTo::create(durtion/30, 225);
    CCRotateTo *rotate6 = CCRotateTo::create(durtion/30, 280);
    CCRotateTo *rotate7 = CCRotateTo::create(durtion/30, 325);
    CCRotateTo *rotate8 = CCRotateTo::create(durtion/30, 360);
    CCArray *array = new CCArray();
    array->addObject(rotate1);
    array->addObject(rotate2);
    array->addObject(rotate3);
    array->addObject(rotate4);
    array->addObject(rotate5);
    array->addObject(rotate6);
    array->addObject(rotate7);
    array->addObject(rotate8);
    CCSequence *sq = CCSequence::create(array);
    CCRepeatForever *re = CCRepeatForever::create(sq);
   
    this->runAction(re);
}
bool Egg::getDeleted()
{
    return this->deleted;
}
void Egg::setDeleted(bool deleted)
{
    this->deleted = deleted;
}
void Egg::removeEgg(cocos2d::CCNode *node)
{
    Egg *e = (Egg*)node;
    e->setDeleted(true);
}
float Egg::getDuritionMove()
{
    return this->duritionMove;
}
void Egg::setDuritionMove(float dt)
{
    this->duritionMove = dt;
}


