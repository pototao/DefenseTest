//
//  Role.cpp
//  MyBox2d
//
//  Created by  陈广文 on 12-12-18.
//
//

#include "Role.h"
#include "data/Consts.h"
#include "cocos2d.h"
USING_NS_CC;

//IMPLEMENT_DYNAMIC_CLASS(Role, MyObject)    // 动态地实现一些用于RTTI的成员


Role::Role():state(NONE),nextState(NONE),faceDir(R),moveDir(R),color(ccWHITE),scale(ccp(1.0f,1.0f)),opacity(255){

   
}
Role::~Role(){}
void Role::update(float dt){
    
}
Role* Role::copyWithZone(CCZone* pZone)
{
    Role* temp = new Role();

    return temp;
}
void Role::changeState(byte cs, byte ns){
    nextState=ns;
    byte mode=-1;
	const char* temp="";
    switch (cs) {
        case STAND:
			temp="stand";
            mode=LOOP;
            break;
        case WALK:
			temp="stand";
            mode=LOOP;
            break;
        case RUN:
			temp="stand";
            mode=LOOP;
            break;
    }
    state=cs;
	CCString* actionName=CCString::createWithFormat("%s%s%d",prefix.c_str(),temp,ID);
/*	CCLog("changeState------------------------------------ actionName %s",actionName->getCString());*/
	changeAction(actionName->getCString(),mode);
}
void Role::init(const char* xmlName,int rID,Short1DArray info){
	CCSpriteLG::init(xmlName);
	ID=rID;
	type=info->value[0];
	
}
Role*Role::create(const char* xmlName,int rID,Short1DArray info){
	Role* role=new Role();
	if(role){
		role->init(xmlName,rID,info);
		role->autorelease();
	}
	return role;
}
bool Role::isAlive(){
    return state!=NONE;
}


void Role::setDir(byte dir, bool flag){
    moveDir=dir;
    if(flag){
        faceDir=getDir(moveDir);
    }
}
byte Role::getDir(byte dir){
    if(dir==0||dir==1){
        return dir;
    }else{
        return DIR[dir];
    }
    
}