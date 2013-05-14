#include "CCSpriteLG.h"
#include "AnimatePacker.h"
#include "AnimatePackerCache.h"
#include "data/Consts.h"
USING_NS_CC;

CCSpriteLG::CCSpriteLG(void)
{
}


CCSpriteLG::~CCSpriteLG(void)
{   
	removeAllChildrenWithCleanup(true);
}
bool CCSpriteLG::init(const char* xmlName){
	AnimatePackerCache::getAnimatePackerCache()->addAnimatePacker(xmlName);
	mySprite=CCSprite::create(); 
	addChild(mySprite);
	return true;
}
void CCSpriteLG::changeAction(const char* an,byte mode){
	switch(mode){
	case LOOP:
		CCAnimate* a=AnimatePacker::getInstance()->getAnimate(an);
		mySprite->runAction(CCRepeatForever::create(a)); 
		break;
	}

}

