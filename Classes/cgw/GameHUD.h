#ifndef __TowerDefenseCCX__GameHUD__
#define __TowerDefenseCCX__GameHUD__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class GameHUD :public CCLayer {
    
    

public:
    CC_SYNTHESIZE(int, resources, Resources);
     CC_SYNTHESIZE(int, baseHpPercentage, BaseHpPercentage);
public:
    ~GameHUD();
    bool init();
    bool ccTouchBegan(CCTouch *touch,CCEvent *event);
    void ccTouchMoved(CCTouch *touch,CCEvent *event);
    void ccTouchEnded(CCTouch *touch,CCEvent *event);
    void  updateBaseHp(int amount);
    void updateResources(int amount);
    //告诉玩家波次的来临。
    void  newWaveApproachingEnd();
    void  newWaveApproaching();
    
    void updateResourcesNom(float ft);
    void updateWaveCount();
    CREATE_FUNC(GameHUD);
public:
    static GameHUD *sharedHUD();
private:
	CCSprite * background;
    CCLabelTTF *newWaveLabel;
    CCLabelTTF *resourceLabel;
    CCLabelTTF *waveCountLabel;
    
    CCProgressTimer *healthBar;
	CCSprite * selSpriteRange;
    CCSprite * selSprite;
    CCArray * movableSprites;
};


#endif /* defined(__TowerDefenseCCX__GameHUD__) */
