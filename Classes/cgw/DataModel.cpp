//
//  DataModel.cpp
//  TowerDefenseCCX
//
//  Created by  陈广文 on 13-3-27.
//
//

#include "DataModel.h"
USING_NS_CC;
static DataModel *_sharedContext = NULL;

DataModel*DataModel::getModel()
{
	if (!_sharedContext) {
		_sharedContext =new DataModel();
        _sharedContext->init();
	}
	
	return _sharedContext;
}

//-(void)encodeWithCoder:(NSCoder *)coder {
//    
//}

//-(id)initWithCoder:(NSCoder *)coder {
//    
//	return self;
//}

bool DataModel::init()
{
//	if ((self = [super init])) {
    _targets = new CCArray();
		_waypoints =  new CCArray();
		_waves =  new CCArray();
    _towers=new CCArray();
    isDrag=true;
    _projectiles=new CCArray();
//	}
	return true;
}
DataModel::~DataModel() {
	_gameLayer = NULL;
//	_gestureRecognizer = NULL;
	
	_targets->release();
	_targets = NULL;
	
	_waypoints->release();
	_waypoints = NULL;
	
	_waves->release();
	_waves = NULL;

}