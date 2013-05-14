#pragma once
#include "cocos2d.h"
#include "framework/DataType.h"
USING_NS_CC;
class CCSpriteLG :
	public cocos2d::CCNode
{
public:
	CCSpriteLG(void);
	virtual ~CCSpriteLG(void);
	virtual void changeAction(const char* an,byte mode);
	virtual bool init(const char* xmlName);
protected:
	cocos2d::CCSprite* mySprite;
};

