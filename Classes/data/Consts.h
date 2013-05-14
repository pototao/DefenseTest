#ifndef _CONST_VALUES_H_
#define _CONST_VALUES_H_
#include "cocos2d.h"
#include "framework/DataType.h"



#define ARU ccp(1.0f,1.0f)
#define ALU ccp(0.0f,1.0f)
#define ARD ccp(1.0f,1.0f)
#define ALD ccp(0.0f,0.0f)
#define AMID ccp(0.5f,0.5f)
const  byte NONE=-1;

const  byte STAND=0,WALK=1,LIE_DOWN=2,RUN=3,JUMP=4,BE_FIGHTED=5,LOST_CONTROL=6,DEAD=7;


const  byte PLAYER=0,COMPUTER=1, NEUTRAL=2;

const  byte LOOP=0,START=1,STOP=2;

const  byte L = 0,R = 1,U = 2,D = 3,LU=4,RU=5,LD=6,RD=7;

const double acceleration=9.8;//

const double resistance=3.2;//

const  float rotation[]={0.0f,270};

const  byte fx[]={0,0,0,0,0,0,0,0};

const  byte fy[]={0,0,0,1,1,1,1,0};

const  byte DIR[]={1,1,1,0, 0,0,1,1};


#endif
