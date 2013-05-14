#pragma once
#include "Role.h"
#include "cocos2d.h"
#include "Creeps.h"
#include "Bullet.h"
class Towers :
	public Role
{
public:
	Towers(void);
	~Towers(void);
public:
	CC_SYNTHESIZE(int, _range, Range);
	CC_SYNTHESIZE(Creeps *, _target, Target);
	CC_SYNTHESIZE(Bullet *, _nextBullet, NextBullet);
public:
	virtual Creeps *getClosestTarget();
	virtual void checkTarget();
	static Towers* create(const char* xmlName,int rID,Short1DArray info);
	virtual void init(const char* xmlName,int rID,Short1DArray info);
	virtual void towerLogic(float dt);
	virtual void creepMoveFinished(cocos2d::CCNode* sender);
	virtual void finishFiring();
protected:
	cocos2d::CCArray *_projectiles;
	cocos2d::CCSprite * selSpriteRange;
	int bulletTag;
};

