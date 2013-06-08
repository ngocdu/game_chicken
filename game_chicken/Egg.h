//
//  Egg.h
//  game_chicken
//
//  Created by Ngoc Du on 13/06/07.
//
//

#ifndef game_chicken_Egg_h
#define game_chicken_Egg_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace std;
class Egg : public cocos2d::CCSprite
{
private:
	
	int point;
    int direction;//de biet xem qua trung nam o cac mang ben trai hay ben phai
                  //quy dinh ben trai la 0 ben phai la 1
    bool deleted;
    float duritionMove;
	
public:
	Egg();
	Egg(int  point);// ham tao co doi so
    
	int getPoint();
	void setPoint(int point );
    
    int getDirection();
	void setDirection(int point );
    void removeEgg(cocos2d::CCNode * node);
    void move(cocos2d::CCPoint point1,cocos2d::CCPoint point2,cocos2d::CCPoint point3);
    bool getDeleted();
    void setDeleted(bool deleted);
	float getDuritionMove();
    void setDuritionMove(float dt);
    
};


#endif
