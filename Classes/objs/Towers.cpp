#include "Towers.h"
#include "Creeps.h"
#include "objs/Bullet.h"
#include "cgw/DataModel.h"
#include "data/Consts.h"
#include "data/Info.h"
#include "data/GameData.h"
USING_NS_CC;
Towers::Towers(){}
Towers::~Towers(){}
void Towers::checkTarget() {
	//    if(_target){
	double curDistance = ccpDistance(getPosition(), _target->getPosition());
	if (_target->getHp()<= 0 || curDistance>_range){
		_target =getClosestTarget();
	}
	//    }

}

Creeps *Towers::getClosestTarget()
{
	Creeps *closestCreep = NULL;
	double maxDistant = 99999;

	DataModel *m = DataModel::getModel();

	for (int i=0;i<m->getTargets()->count();i++) {
		Creeps *creep=(Creeps *)m->getTargets()->objectAtIndex(i);
		double curDistance = ccpDistance(getPosition(), creep->getPosition());

		if (curDistance < maxDistant) {
			closestCreep = creep;
			maxDistant = curDistance;
		}

	}

	if (maxDistant < _range)
		return closestCreep;

	return NULL;
}
void Towers::init(const char* xmlName,int rID,Short1DArray info){
	Role::init(xmlName,rID,info);
	setRange(200);
	prefix="t";
	bulletTag=info->value[2];
	CCLog("Tower init bulletTag %d ",bulletTag);
	schedule(schedule_selector(Towers::towerLogic),0.2);
	changeState(STAND,STAND);
}
Towers* Towers::create(const char* xmlName,int rID,Short1DArray info) {
	Towers *tower = new Towers();
	tower->init(xmlName,rID,info);
	tower->autorelease();
	return tower;

}
void Towers::creepMoveFinished(CCNode* sender) {

	DataModel * m = DataModel::getModel();

	CCSprite *sprite =(CCSprite*)sender;
	this->getParent()->removeChild(sprite,true);
	m->getProjectiles()->removeObject(sprite);

}
void Towers::finishFiring() {
	if (!_target) {
		return;
	}
	DataModel *m = DataModel::getModel();

	setNextBullet(Bullet::create(BULLET_NAME[bulletTag].c_str(),bulletTag,Info::getInfo()->bulletInfo->value[bulletTag]));
	getNextBullet()->setPosition(getPosition());

	this->getParent()->addChild(getNextBullet(),1);
	m->getProjectiles()->addObject(getNextBullet());

	float delta = 1.0;
	CCPoint shootVector = ccpSub(_target->getPosition(),getPosition());
	CCPoint normalizedShootVector = ccpNormalize(shootVector);
	CCPoint overshotVector = ccpMult(normalizedShootVector, 320);
	CCPoint offscreenPoint = ccpAdd(getPosition(), overshotVector);

	getNextBullet()->runAction(CCSequence::create(CCMoveTo::create(delta,offscreenPoint),
		CCCallFuncN::create(this,callfuncN_selector( Towers::creepMoveFinished)),NULL));

	getNextBullet()->setTag(bulletTag);

	setNextBullet(NULL);

}

void Towers::towerLogic(float dt) {
	//    if(_target==NULL){
	_target = getClosestTarget();
	//    }


	if (_target != NULL) {

		//rotate the tower to face the nearest creep
		CCPoint shootVector = ccpSub(_target->getPosition(), getPosition());
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

		float rotateSpeed = 0.5 / M_PI; // 1/2 second to roate 180 degrees
		float rotateDuration = fabs(shootAngle * rotateSpeed);

		runAction(CCSequence::create(CCRotateTo::create(rotateDuration,cocosAngle),
			CCCallFunc::create(this,callfunc_selector(Towers::finishFiring)),NULL));
	}
}