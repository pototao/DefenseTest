#include "Creeps.h"
#include "cgw/DataModel.h"
#include "data/Consts.h"
USING_NS_CC;
Creeps::Creeps(){}
Creeps::~Creeps(){}
//此前，敌人会根据路点的间距来加速或减速。实际上我们希望看到的是敌人以相同的速度在地图上前进。
float Creeps::moveDurScale()
{

	DataModel *m = DataModel::getModel();

	WayPoint *waypoint0 = (WayPoint *) m->getWaypoints()->objectAtIndex(0);
	WayPoint *waypoint1 = (WayPoint *) m->getWaypoints()->objectAtIndex(1);
	firstDistance = ccpDistance(waypoint0->getPosition(), waypoint1->getPosition());

	WayPoint *waypoint2 = (WayPoint *) m->getWaypoints()->objectAtIndex(_curWaypoint-1);
	WayPoint *waypoint3 = (WayPoint *) m->getWaypoints()->objectAtIndex(_curWaypoint);
	float thisDistance = ccpDistance(waypoint2->getPosition(), waypoint3->getPosition());

	float moveScale = thisDistance/firstDistance;

	return (_moveDuration * moveScale);
}
WayPoint *Creeps::getCurrentWaypoint(){

	DataModel *m = DataModel::getModel();

	WayPoint *waypoint = (WayPoint *)m->getWaypoints()->objectAtIndex(_curWaypoint);

	return waypoint;
}
void Creeps::init(const char* xmlName,int rID,Short1DArray info){
	Role::init(xmlName,rID,info);
	prefix="c";
	setHp(10);
	setMoveDuration(4);
	setCurWaypoint(0);
	schedule(schedule_selector(Creeps::creepLogic),0.2);
	schedule(schedule_selector(Creeps::healthBarLogic));
	changeState(STAND,STAND);
}

Creeps*Creeps::create(const char* xmlName,int rID,Short1DArray info){
	Creeps* role=new Creeps();
	if(role){
		role->init(xmlName,rID,info);
/*		role->autorelease();*/
	}
	return role;
}
WayPoint * Creeps::getLastWaypoint(){

	DataModel *m = DataModel::getModel();
	this->setLastWaypoint(this->getCurWaypoint() -1);

	WayPoint *waypoint = (WayPoint *) m->getWaypoints()->objectAtIndex(_lastWaypoint);

	return waypoint;
}
WayPoint *Creeps::getNextWaypoint(){

	DataModel *m = DataModel::getModel();
	int lastWaypoint = m->getWaypoints()->count();
	//
	_curWaypoint++;
	if (_curWaypoint >=lastWaypoint-1){
		_curWaypoint--;
		gameHUD = GameHUD::sharedHUD();
		if (gameHUD->getBaseHpPercentage() > 0) {
			gameHUD->updateBaseHp(-10);
		}
		CCArray *endtargetsToDelete =new CCArray();
		endtargetsToDelete->addObject(this);
		for (int i=0;i<endtargetsToDelete->count();i++) {
			CCSprite *target=(CCSprite *)endtargetsToDelete->objectAtIndex(i);
			m->getTargets()->removeObject(target);
			getParent()->removeChild(target,true);
		}
		return NULL;
	}
	WayPoint *waypoint = (WayPoint *)m->getWaypoints()->objectAtIndex(_curWaypoint);

	return waypoint;
}

void Creeps::creepLogic(float dt)
{
	WayPoint *waypoint =getCurrentWaypoint();

	CCPoint waypointVector = ccpSub(waypoint->getPosition(), getPosition());
	float waypointAngle = ccpToAngle(waypointVector);
	float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * waypointAngle);

	float rotateSpeed = 0.5 / M_PI; // 1/2 second to roate 180 degrees
	float rotateDuration = fabs(waypointAngle * rotateSpeed);
	runAction(CCSequence::create(CCRotateTo::create(rotateDuration,cocosAngle),NULL));
	//	runAction(CCSequence::create(CCRotateTo::create(rotateDuration,cocosAngle),NULL));
}
void Creeps::healthBarLogic(float dt) {

	//Update health bar pos and percentage.
	healthBar->setPosition(ccp(getPosition().x, getPosition().y+20));
	healthBar->setPercentage(((float)getHp()/(float)_totalHp) *100);

	if (healthBar->getPercentage()<= 0) {
		removeChild(healthBar,true);
	}
}