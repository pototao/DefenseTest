#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "Wave.h"
#include "GameHUD.h"
USING_NS_CC;
class Wave;
class HelloWorld : public cocos2d::CCLayer
{

    CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXTiledMap *, _tileMap, TileMap);
    CC_SYNTHESIZE_RETAIN(cocos2d:: CCTMXLayer *, _background, Background);
    CC_SYNTHESIZE(int, _currentLevel, CurrentLevel);
    
    cocos2d::CCPoint oldTouchLocation;
private:
    GameHUD * gameHUD;
public:
    long millisecondNow()
    {
        struct cocos2d::cc_timeval now;
        cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
        return (now.tv_sec * 1000 + now.tv_usec / 1000);
    }
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    virtual void addWaypoint();
    bool canBuildOnTilePosition(CCPoint pos);
    virtual void addWaves();
    virtual  Wave *getCurrentWave();
    virtual Wave *getNextWave();
    virtual void addTarget();
    void addTower(CCPoint pos,int tag);
    void waveWait(float ft);//波次速度调整
    void ResumePath(CCNode* sender);
    CCPoint  tileCoordForPosition(CCPoint  position);
    virtual void gameLogic(float dt);
    virtual void update(float dt);
    void dragLayer(CCTouch *touch);
    virtual void FollowPath(cocos2d::CCNode* sender);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    // a selector callback
//    void handlePanFrom(UIPanGestureRecognizer *recognizer);
//    virtual void menuCloseCallback(CCObject* pSender);
    cocos2d::CCPoint boundLayerPos(cocos2d::CCPoint newPos);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
