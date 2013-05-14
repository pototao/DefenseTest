//
//  Role.h
//  cgw
//
//
//

#ifndef __MyBox2d__Role__
#define __MyBox2d__Role__

#include <iostream>
#include "framework/DataType.h"
#include "cocos2d.h"
#include "LGAD/CCSpriteLG.h"
class Role:public CCSpriteLG{

public:
    Role();
    ~Role();
	
	virtual void update(float dt);
    virtual Role* copyWithZone(CCZone* pZone);
    virtual void changeState(byte cs,byte ns);
    virtual void init(const char* xmlName,int rID,Short1DArray info);
    virtual bool isAlive();
    virtual void setDir(byte dir,bool flag);
    virtual byte getDir(byte dir);
public:
    static Role* create(const char* xmlName,int rID,Short1DArray info);
	CC_SYNTHESIZE(int, style, Style);
	CC_SYNTHESIZE(int, ID, ID);
	CC_SYNTHESIZE(int, type, Type);
	CC_SYNTHESIZE(float, width, Width);

	CC_SYNTHESIZE(float, height, Height);
	CC_SYNTHESIZE(float, radio, Radio);
	CC_SYNTHESIZE(Size,num,Num);
	CC_SYNTHESIZE(CCPoint,tempPosition,TempPosition);
protected:
	std::string prefix;
	byte  state,nextState;
	cocos2d::CCPoint scale;
    ccColor3B color;//
    GLubyte opacity;
	std::string name;//
 	byte group;//
 	byte moveDir,faceDir;
	Byte1DArray cellState;
	float cellHeight,cellWidth;
	int angleIndex;
};
#endif 