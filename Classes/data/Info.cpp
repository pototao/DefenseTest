
//  Created by  cgw on 12-12-21.
//
//

#include "Info.h"
#include "cocos2d.h"
#include "framework/Util.h"
USING_NS_CC;
static Info* myInfo;
bool Info::loadInfo(){
		towerInfo=Util::read2DShortData("towerInfo.data");
		creepInfo=Util::read2DShortData("creepInfo.data");
		bulletInfo=Util::read2DShortData("bulletInfo.data");
		return true;

}
void Info::clear(){
	for (int i=0;i<towerInfo->length;i++)
	{
		free(towerInfo->value[i]);	
	}
	free(towerInfo);
}
Info*Info::getInfo(){
	if(myInfo==NULL){
        myInfo=new Info();
        myInfo->loadInfo();
	}
	return myInfo;
}
