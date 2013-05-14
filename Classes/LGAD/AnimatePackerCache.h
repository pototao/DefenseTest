#pragma once
#include "cocos2d.h"
USING_NS_CC;
class AnimatePackerCache :
	public CCObject
{
public:
	AnimatePackerCache(void);
	virtual ~AnimatePackerCache(void);
	virtual void addAnimatePacker(const char* XMLName);
	static AnimatePackerCache* getAnimatePackerCache();
	
private:
	bool isHaveKey(CCString* XMLName);
	CCArray* array;
};

