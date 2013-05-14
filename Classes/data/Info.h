//
//  Info.h
//  MyBox2d
//
//  Created by  cgw on 12-12-21.
//
//

#ifndef __MyBox2d__Info__
#define __MyBox2d__Info__

#include <iostream>
#include "framework/DataType.h"
#include "cocos2d.h"
class Info{
public:
     Short2DArray creepInfo;
     Short2DArray towerInfo;
	  Short2DArray bulletInfo;
     Short2DArray initInfo;
     Short2DArray processInfo;
     Int2DArray   achieveInfo;  
     bool loadInfo();	
	 static Info* getInfo();
	 void clear();
private:
	
};
#endif /* defined(__MyBox2d__Info__) */
