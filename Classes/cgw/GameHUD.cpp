//
//  GameHUD.cpp
//  TowerDefenseCCX
//
//  Created by  陈广文 on 13-3-27.
//
//

#include "GameHUD.h"
#include "DataModel.h"
#include "HelloWorldScene.h"

static GameHUD *_sharedHUD = NULL;
int waveCount;
GameHUD* GameHUD::sharedHUD()
{
//	@synchronized([GameHUD class])
//	{
//		if (!_sharedHUD)
//			[[self alloc] init];
//		return _sharedHUD;
    
//	}
    if(!_sharedHUD){
        _sharedHUD=new GameHUD();
        _sharedHUD->init();
    }
	// to avoid compiler warning
	return _sharedHUD;
}

//+(id)alloc
//{
//	@synchronized([GameHUD class])
//	{
//		NSAssert(_sharedHUD == nil, @"Attempted to allocate a second instance of a singleton.");
//		_sharedHUD = [super alloc];
//		return _sharedHUD;
//	}
//	// to avoid compiler warning
//	return nil;
//}

bool GameHUD::init()
{
//	if ((self=[super init]) ) {
		
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
    background = CCSprite::create("hud.png");
        background->setAnchorPoint(ccp(0,0));
        addChild(background);
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);
		
        movableSprites =new CCArray();
        movableSprites->init();
        CCArray *images =CCArray::create(CCString::create("t0.png"),CCString::create("t1.png"), CCString::create("t0.png"),CCString::create("t0.png"), NULL);
    
    for(int i = 0; i < images->count(); ++i) {
            CCString *image = (CCString*)images->objectAtIndex(i);
        CCSprite *sprite =CCSprite::create(image->getCString());
            float offsetFraction = ((float)(i+1))/(images->count()+1);
            sprite->setPosition(ccp(winSize.width*offsetFraction, 35));
            sprite->setTag(i+1);//individual tag for each Turret.
            addChild(sprite);
            movableSprites->addObject(sprite);
        
        
        //Set up and place towerCost labels
		CCLabelTTF *towerCost =CCLabelTTF::create("$","Marker Felt",10);
        towerCost->setPosition(ccp(winSize.width*offsetFraction, 15));
        towerCost->setColor(ccc3(0, 0, 0));
        addChild(towerCost,1);
        
        //Set cost values
        switch (i) {
            case 0:
                towerCost->setString(CCString::create("$ 25")->getCString());
                break;
            case 1:
                 towerCost->setString(CCString::create("$ 35")->getCString());
                break;
            case 2:
                towerCost->setString(CCString::create("$ 25")->getCString());
                break;
            case 3:
                towerCost->setString(CCString::create("$ 25")->getCString());
                break;
            default:
                break;
        }

        }
    images->release();
    images=NULL;
    
    // Set up Resources and Resource label
    resources = 100;
	resourceLabel = CCLabelTTF::create("Money $100","Marker Felt",20,CCSizeMake(150, 25),kCCTextAlignmentRight);
    resourceLabel->setPosition (ccp(30, (winSize.height - 15)));
    resourceLabel->setColor(ccc3(255,80,20));
    addChild(resourceLabel,1);
    
    // Set up BaseHplabel
	CCLabelTTF *baseHpLabel = CCLabelTTF::create("Base Health","Marker Felt",20,CCSizeMake(150, 25),kCCTextAlignmentRight );
    baseHpLabel->setPosition(ccp((winSize.width - 185), (winSize.height - 15)));
    baseHpLabel->setColor(ccc3(255,80,20));
    addChild(baseHpLabel,1);
    
    // Set up wavecount label
    waveCount = 1;
    waveCountLabel =CCLabelTTF::create("Wave 1","Marker Felt",20,CCSizeMake(150, 25),kCCTextAlignmentRight);
    waveCountLabel->setPosition(ccp(((winSize.width/2) - 80), (winSize.height - 15)));
    waveCountLabel->setColor(ccc3(100,0,100));
    addChild(waveCountLabel,1);
    
    baseHpPercentage = 100;
    // Set up new Wave label
    newWaveLabel =CCLabelTTF::create("","TrebuchetMS-Bold",30,CCSizeMake(300, 50),kCCTextAlignmentRight);
    newWaveLabel->setPosition(ccp((winSize.width/2)-20, (winSize.height/2)+30));
    newWaveLabel->setColor(ccc3(255,50,50));
    addChild(newWaveLabel,1);
    //Set up helth Bar
    healthBar = CCProgressTimer::create(CCSprite::create("health_bar_green.png"));
    healthBar->setType(kCCProgressTimerTypeBar);
    healthBar->setPercentage(baseHpPercentage);
    healthBar->setScale(0.5);
    healthBar->setPosition(ccp(winSize.width -55, winSize.height -15));
    addChild(healthBar,1);
    
    
    this->setTouchEnabled(true);
    
    
		 CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
//	}
	return true;
}
void  GameHUD::newWaveApproaching()
{
    newWaveLabel->setString(CCString::create("HERE THEY COME!")->getCString());
}
void  GameHUD::newWaveApproachingEnd(){
    newWaveLabel->setString(CCString::createWithFormat(" ")->getCString());
}
void  GameHUD::updateBaseHp(int amount){
    baseHpPercentage += amount;
    
    if (baseHpPercentage <= 25) {
		healthBar->setSprite(CCSprite::create("health_bar_red.png"));
        healthBar->setScale(0.5);
    }
    
    if (baseHpPercentage <= 0) {
        //Game Over Scenario
        printf("Game Over\n");
        //Implement Game Over Scenario
    }
    
    healthBar->setPercentage(baseHpPercentage);
}

void GameHUD::updateResources(int amount){
    resources += amount;
    resourceLabel->setString(CCString::createWithFormat("Money %i",resources)->getCString());
}

void GameHUD::updateResourcesNom(float ft){
    resources += 1;
    resourceLabel->setString(CCString::createWithFormat("Money %i",resources)->getCString());
}
void GameHUD::updateWaveCount(){
    waveCount++;
    waveCountLabel->setString(CCString::createWithFormat("Wave %i",waveCount)->getCString());
}
bool GameHUD::ccTouchBegan(CCTouch *touch,CCEvent *event) {
    CCPoint touchLocation = convertTouchToNodeSpace(touch);
    
	CCSprite * newSprite = NULL;
    for (int i=0;i<movableSprites->count();i++) {
        CCSprite *sprite=(CCSprite *)movableSprites->objectAtIndex(i);
        
        if (sprite->boundingBox().containsPoint(touchLocation)) {
			DataModel *m = DataModel::getModel();
//			m._gestureRecognizer.enabled = NO;
			m->setIsDrag(false);
			selSpriteRange =CCSprite::create("Range.png");
			selSpriteRange->setScale(4);
			addChild(selSpriteRange,-1);
			selSpriteRange->setPosition(sprite->getPosition());
			
            newSprite = CCSprite::createWithTexture(sprite->getTexture()); //sprite;
			newSprite->setPosition(sprite->getPosition());
			selSprite = newSprite;
            selSprite->setTag(sprite->getTag());
			addChild(newSprite);
			
            return true;
        }
    }
    return false;
}

void GameHUD::ccTouchMoved(CCTouch *touch,CCEvent *event) {
    CCPoint touchLocation =convertTouchToNodeSpace(touch);
    
    CCPoint oldTouchLocation = touch->getPreviousLocationInView();
    oldTouchLocation = CCDirector::sharedDirector()->convertToGL(oldTouchLocation);
    oldTouchLocation = convertToNodeSpace(oldTouchLocation);
    
    CCPoint translation = ccpSub(touchLocation, oldTouchLocation);
	
	if (selSprite) {
		CCPoint newPos = ccpAdd(selSprite->getPosition(), translation);
        selSprite->setPosition(newPos);
		selSpriteRange->setPosition(newPos);
		
		DataModel *m = DataModel::getModel();
		CCPoint touchLocationInGameLayer = m->getGameLayer()->convertTouchToNodeSpace(touch);
		HelloWorld* hello=(HelloWorld*)m->getGameLayer();
		bool isBuildable = hello->canBuildOnTilePosition(touchLocationInGameLayer);
		if (isBuildable) {
			selSprite->setOpacity(200);
		} else {
			selSprite->setOpacity(50);
		}
	}
}

void GameHUD::ccTouchEnded(CCTouch *touch,CCEvent *event) {
	CCPoint touchLocation =convertTouchToNodeSpace(touch);
	DataModel *m = DataModel::getModel();
    
	if (selSprite) {
		CCRect backgroundRect = CCRectMake(background->getPosition().x,background->getPosition().y,
                                           background->getContentSize().width,
                                           background->getContentSize().height);
		if(!backgroundRect.containsPoint(touchLocation)){
			CCPoint touchLocationInGameLayer = m->getGameLayer()->convertTouchToNodeSpace(touch);
            HelloWorld* hello=(HelloWorld*)m->getGameLayer();
			hello->addTower(touchLocationInGameLayer,selSprite->getTag());
        }
		
		removeChild(selSprite,true);
		selSprite = NULL;
		removeChild(selSpriteRange,true);
		selSpriteRange = NULL;
	}
	m->setIsDrag(true);
//	m._gestureRecognizer.enabled = YES;
}
//- (void) registerWithTouchDispatcher
//{
//	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:0 swallowsTouches:YES];
//}

// on "dealloc" you need to release all your retained objects
GameHUD::~GameHUD()
{
	movableSprites->release();
    movableSprites = NULL;
	
}