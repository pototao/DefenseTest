#pragma once
#include "Role.h"
#include "cgw/WayPoint.h"
#include "cgw/GameHUD.h"
class Creeps :
	public Role
{
public:
	Creeps(void);
	virtual ~Creeps(void);
	static Creeps* create(const char* xmlName,int rID,Short1DArray info);
	virtual void init(const char* xmlName,int rID,Short1DArray info);
	CC_SYNTHESIZE(int, _curHp, Hp);
	CC_SYNTHESIZE(int, _moveDuration, MoveDuration);
	CC_SYNTHESIZE(int, _curWaypoint, CurWaypoint);
	CC_SYNTHESIZE(int, _lastWaypoint, LastWaypoint);
	CC_SYNTHESIZE(int, _totalHp, TotalHp);
	CC_SYNTHESIZE(CCProgressTimer *, healthBar, HealthBar);
	virtual WayPoint * getLastWaypoint();
	virtual  WayPoint * getCurrentWaypoint();
	virtual WayPoint * getNextWaypoint();
	virtual void creepLogic(float dt);
	virtual float moveDurScale();
	virtual void healthBarLogic(float dt);
private:
	GameHUD * gameHUD;
	float firstDistance;
};

