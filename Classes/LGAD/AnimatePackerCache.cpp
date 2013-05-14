#include "AnimatePackerCache.h"
#include "AnimatePacker.h"

AnimatePackerCache::AnimatePackerCache(void)
{
	array=new CCArray();
}
static AnimatePackerCache* cache;
AnimatePackerCache* AnimatePackerCache::getAnimatePackerCache(){
	if(!cache){
	   cache=new AnimatePackerCache();
	}
	return cache;
}
bool AnimatePackerCache::isHaveKey(CCString* str){
	
	for (int i=0;i<array->count();i++)
	{
		CCString* temp=(CCString*)array->objectAtIndex(i);
		if(temp->isEqual(str)){
			return true;
		}
	}
	return false;
}
void AnimatePackerCache::addAnimatePacker(const char* XMLName){
	CCString* str=new CCString(XMLName);
	if(!isHaveKey(str)){
/*		CCLog("addAnimatePacker xmlName %s ",XMLName);*/
		array->addObject(str);
		AnimatePacker::getInstance()->loadAnimations(XMLName);
	}


}
AnimatePackerCache::~AnimatePackerCache(void)
{
	for (int i=0;i<array->count();i++)
	{
		CCString* temp=(CCString*)array->objectAtIndex(i);
		AnimatePacker::getInstance()->freeAnimations(temp->getCString());

	}
	array->removeAllObjects();
	array=NULL;
}
