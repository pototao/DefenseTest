//
//  Wave.cpp
//  TowerDefenseCCX
//
//  Created by  陈广文 on 13-3-27.
//
//

#include "Wave.h"

Wave*Wave::initWithCreep(Creeps *creep,float spawnrate,int redNum,int greenNum)
{

    
//	if( (self = [self init]) )
//	{
		_creepType = creep;
		_spawnRate = spawnrate;
		_redCreeps = redNum;
    _greenCreeps=greenNum;
//	}
	return this;
}