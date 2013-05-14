#ifndef __TowerDefenseCCX__Wave__
#define __TowerDefenseCCX__Wave__

#include <iostream>
#include "cocos2d.h"
#include "objs/Creeps.h"
USING_NS_CC;
class Creeps;
class Wave:public CCNode{
public:
CC_SYNTHESIZE(float, _spawnRate, SpawnRate);
CC_SYNTHESIZE(int, _redCreeps, RedCreeps);
CC_SYNTHESIZE(int, _greenCreeps, GreenCreeps);
CC_SYNTHESIZE(Creeps *,_creepType, CreepType);
public:
   virtual Wave* initWithCreep(Creeps *creep,float spawnrate,int redNum,int greenNum);
};

#endif /* defined(__TowerDefenseCCX__Wave__) */
