#ifndef __TowerDefenseCCX__DataModel__
#define __TowerDefenseCCX__DataModel__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;


class DataModel : public cocos2d::CCObject{
public:
    //CCLayer是我们所定义的真正游戏层，你和敌人的真正战斗将发生在这里，因此我们务必要随时追踪这个层，以便其它类都可以访问。
    CC_SYNTHESIZE( cocos2d::CCLayer*, _gameLayer, GameLayer);
    //我们的敌人
    CC_SYNTHESIZE( cocos2d::CCArray *, _targets, Targets);
    //是敌人要经过的路点
    CC_SYNTHESIZE( cocos2d::CCArray *, _waypoints, Waypoints);
    //存储敌人的数量和出现速度等信息
    CC_SYNTHESIZE( cocos2d::CCArray *, _waves, Waves);
    CC_SYNTHESIZE( cocos2d::CCArray *, _projectiles, Projectiles);
    
    CC_SYNTHESIZE( cocos2d::CCArray *, _towers, Towers);
    CC_SYNTHESIZE( cocos2d::CCLayer *, _gameHUDLayer, GameHUDLayer);
    CC_SYNTHESIZE(bool,  isDrag, IsDrag);
    
    //UIPanGestureRecognizer可以让你滚动地图，而不是让地图限制在区区480*320这么小的范围内
//    CC_SYNTHESIZE_RETAIN( UIPanGestureRecognizer *, _gestureRecognizer, GestureRecognizer);
public:
    ~DataModel();
    static DataModel*getModel();
    bool init();
};

#endif /* defined(__TowerDefenseCCX__DataModel__) */
