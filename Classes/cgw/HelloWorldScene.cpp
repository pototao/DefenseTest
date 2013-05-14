#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "DataModel.h"
#include "Wave.h"
#include "objs/Towers.h"
#include "objs/Creeps.h"
#include "GameHUD.h"
#include "objs/Bullet.h"
#include "data/Info.h"
#include "data/GameData.h"
using namespace cocos2d;
using namespace CocosDenshion;
CCScene*HelloWorld::scene()
{
	// 'scene' is an autorelease object.
	CCScene *scene =CCScene::create();
	
	// 'layer' is an autorelease object.
	HelloWorld *layer =HelloWorld::create();
	
	// add layer as a child to scene
	scene->addChild(layer,1);
    
	GameHUD * gameHUD = GameHUD::sharedHUD();
    
	scene->addChild(gameHUD,2);
    
	DataModel *m = DataModel::getModel();
	m->setGameLayer(layer);
	m->setGameHUDLayer(gameHUD);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
         _tileMap =CCTMXTiledMap::create("TileMap.tmx");
        _background = _tileMap->layerNamed("Background");
		_background->setAnchorPoint(ccp(0, 0));
		this->addChild(_tileMap,0);
		
		addWaypoint();
		addWaves();
		// Call game logic about every second
        schedule( schedule_selector(HelloWorld::update));
		schedule( schedule_selector(HelloWorld::gameLogic),0.1);
		_currentLevel = 0;
       
		this->setPosition(ccp(-228, -122));
        gameHUD = GameHUD::sharedHUD();
    gameHUD->schedule(schedule_selector(GameHUD::updateResourcesNom), 2.0);
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,10,true);
    return true;
}
void HelloWorld::addWaves() {
	DataModel *m = DataModel::getModel();
	
    for (int i=0; i<5; i++) {
        Wave * wave =new Wave();
		Creeps* creep=Creeps::create(ENERMY_NAME[i%2].c_str(),i%2,Info::getInfo()->creepInfo->value[i%2]);
        wave->initWithCreep(creep, 1.0,5+i*10,0+i*5);
        m->getWaves()->addObject(wave);
        wave = NULL;
    }

}

Wave *HelloWorld::getCurrentWave(){
	
	DataModel *m = DataModel::getModel();
	Wave * wave = (Wave *) m->getWaves()->objectAtIndex(_currentLevel);
	
	return wave;
}

Wave *HelloWorld::getNextWave(){
	
	DataModel *m = DataModel::getModel();
	
	_currentLevel++;
	
	if (_currentLevel >m->getWaves()->count()-1)
		_currentLevel = 0;
        
        Wave * wave = (Wave *)m->getWaves()->objectAtIndex(_currentLevel);
        
        return wave;
}

void HelloWorld::addWaypoint() {
	DataModel *m = DataModel::getModel();
	
	CCTMXObjectGroup *objects =_tileMap->objectGroupNamed("Objects");
	WayPoint *wp = NULL;
	
	int spawnPointCounter = 0;
	CCDictionary *spawnPoint;
	while ((spawnPoint =objects ->objectNamed(CCString::createWithFormat("Waypoint%d", spawnPointCounter)->getCString()))) {
		int x = spawnPoint->valueForKey("x")->intValue();
		int y = spawnPoint->valueForKey("y")->intValue();
		
		wp =(WayPoint *)WayPoint::create();
		wp->setPosition(ccp(x, y));
		m->getWaypoints()->addObject(wp);
		spawnPointCounter++;
	}
	
//	NSAssert([m->getWaypoints()->count()] > 0, @"Waypoint objects missing");
	wp = NULL;
}

void HelloWorld::addTarget() {
    
	DataModel *m = DataModel::getModel();
	Wave * wave = getCurrentWave();
    int tc=wave->getRedCreeps();
    int gn=wave->getGreenCreeps();
	if (tc <= 0&&gn<=0) {
		return; //[self getNextWave];
	}
	
//	wave->setTotalCreeps(--tc);
	
    Creeps *target = NULL;
//    if ((arc4random() % 2) == 0) {
//        target = FastRedCreep::creep();
//    } else {
//        target = StrongGreenCreep::creep();
//    }
	int random=CCRANDOM_0_1()*100;
    if ((random % 2) == 0) {
        if (wave->getRedCreeps()>0) {
           target =Creeps::create(ENERMY_NAME[0].c_str(),0,Info::getInfo()->creepInfo->value[0]);
            wave->setRedCreeps(--tc);
        }
        else if (wave->getGreenCreeps()>0){
           target = Creeps::create(ENERMY_NAME[1].c_str(),1,Info::getInfo()->creepInfo->value[1]);
            wave->setGreenCreeps(--gn);
            // NSLog(@"no more red");
        }
    }
    else {
        if (wave->getGreenCreeps()>0) {
          target = Creeps::create(ENERMY_NAME[1].c_str(),1,Info::getInfo()->creepInfo->value[1]);
            wave->setGreenCreeps(--gn);
        }
        else if (wave->getRedCreeps()>0){
            target = Creeps::create(ENERMY_NAME[0].c_str(),0,Info::getInfo()->creepInfo->value[0]);
            wave->setRedCreeps(--tc);
            //NSLog(@"no more green");
        }
        
    }
	WayPoint *waypoint = target->getCurrentWaypoint();
	target->setPosition( waypoint->getPosition());
	waypoint = target->getNextWaypoint();
	target->setVisible(true);
	addChild(target,1);
    
    target->setHealthBar(CCProgressTimer::create(CCSprite::create("health_bar_red.png")));
    target->getHealthBar()->setType(kCCProgressTimerTypeBar);
    target->getHealthBar()->setPercentage(100);
    target->getHealthBar()->setScale(0.1);
    target->getHealthBar()->setPosition(ccp(target->getPosition().x,(target->getPosition().y+20)));
    addChild(target->getHealthBar(),3);
    
	int moveDuration = target->getMoveDuration();
	CCMoveTo* actionMove = CCMoveTo::create(moveDuration,waypoint->getPosition());
	CCCallFuncN* actionMoveDone =CCCallFuncN::create(this,callfuncN_selector(HelloWorld::FollowPath));
	target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	
	// Add to targets array
	target->setTag(1);
	m->getTargets()->addObject(target);
	
}

void HelloWorld::FollowPath(CCNode* sender) {
    
	Creeps *creep = (Creeps *)sender;
	
	WayPoint * waypoint =creep->getNextWaypoint();
    if(waypoint==NULL){
        return;
    }
//	int moveDuration = creep->getMoveDuration();
    int moveDuration = creep->moveDurScale();
	CCMoveTo *actionMove =CCMoveTo::create(moveDuration,waypoint->getPosition());
	CCCallFuncN* actionMoveDone =CCCallFuncN::create(this,callfuncN_selector(HelloWorld::FollowPath));
	creep->stopAllActions();
    creep->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}
void HelloWorld::waveWait(float ft) {
    unschedule(schedule_selector(HelloWorld::waveWait));
    getNextWave();
    gameHUD->updateWaveCount();
    gameHUD->newWaveApproachingEnd();
}
void HelloWorld::gameLogic(float dt) {
	
    //	DataModel *m = [DataModel getModel];
	Wave * wave = getCurrentWave();
	static double lastTimeTargetAdded = 0;
    double now =millisecondNow();
    
    if(lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->getSpawnRate()) {
        addTarget();
        lastTimeTargetAdded = now;
    }
	
}

void HelloWorld::ResumePath(CCNode* sender) {
    Creeps *creep = (Creeps *)sender;
    
    WayPoint * cWaypoint = creep->getCurrentWaypoint();//destination
    WayPoint * lWaypoint = creep->getLastWaypoint();//startpoint
    
    float waypointDist = fabsf(cWaypoint->getPosition().x - lWaypoint->getPosition().x);
    float creepDist = fabsf(cWaypoint->getPosition().x - creep->getPosition().x);
    float distFraction = creepDist / waypointDist;
//    float moveDuration = creep->getMoveDuration() * distFraction; //Time it takes to go from one way point to another * the fraction of how far is left to
    float durScale = creep->moveDurScale();
    float moveDuration = durScale * distFraction;
//    go (meaning it will move at the correct speed)
    

    CCMoveTo* actionMove = CCMoveTo::create(moveDuration,cWaypoint->getPosition());
    CCCallFuncN* actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::FollowPath));
	creep->stopAllActions();
	creep->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}
void HelloWorld::update(float dt) {
    
    
    DataModel *m =DataModel:: getModel();
    CCArray *projectilesToDelete =new CCArray();
    
    Bullet *projectile =NULL;
	/*CCLog("projectileRect count %d",  m->getProjectiles()->count());*/
    for (int i=0;i<m->getProjectiles()->count();i++) {
        projectile=(Bullet *)m->getProjectiles()->objectAtIndex(i);
        
        CCRect projectileRect = CCRectMake(projectile->getPosition().x - (projectile->getContentSize().width/2),
                                           projectile->getPosition().y - (projectile->getContentSize().height/2),
                                           projectile->getContentSize().width,
                                           projectile->getContentSize().height);
       /* CCLog("projectileRect width %f height %f ",  projectile->getContentSize().width,  projectile->getContentSize().height);*/
        CCArray *targetsToDelete = new CCArray();
        for (int j=0;j<m->getTargets()->count();j++) {
            CCSprite *target=(CCSprite *)m->getTargets()->objectAtIndex(j);
            CCRect targetRect = CCRectMake(target->getPosition().x - (target->getContentSize().width/2),
                                           target->getPosition().y - (target->getContentSize().height/2),
                                           target->getContentSize().width,
                                           target->getContentSize().height);
            
            //                if (CGRectIntersectsRect(projectileRect, targetRect)) {
            if(projectileRect.intersectsRect(targetRect)){
                projectilesToDelete->addObject(projectile);
                
                 Creeps *creep = (Creeps *)target;
                int bulletType=projectile->getTag();
				/*CCLog("hellocpp update bullettype %d",bulletType);*/
                if (bulletType ==0){//MachineGun Projectile
                   
                    int hp=creep->getHp();
                    creep->setHp(--hp);
                    //               
                    if (creep->getHp() <= 0) {
                        targetsToDelete->addObject(target);
                        gameHUD->updateResources(1);
                         removeChild(creep->getHealthBar(),true);
                    }
                    break;
                }
                else if (bulletType ==1){//Freeze projectile
                    CCMoveTo*actionFreeze = CCMoveTo::create(1,creep->getPosition());
                    CCCallFuncN* actionMoveResume = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::ResumePath));
                    creep->stopAllActions();
                    creep->runAction(CCSequence:: create(actionFreeze, actionMoveResume, NULL));
                    break;
                }
                break;
                
            }
        }
        for (int k=0; k<targetsToDelete->count(); k++) {
            CCSprite* target=(CCSprite*)targetsToDelete->objectAtIndex(k);
            m->getTargets()->removeObject(target);
            removeChild(target, true);
        }
        targetsToDelete->release();
    }
    
    for (int k=0; k<projectilesToDelete->count(); k++) {
        CCSprite *projectile=(CCSprite *)projectilesToDelete->objectAtIndex(k);
        m->getProjectiles()->removeObject(projectile);
        removeChild(projectile,true);
    }
    projectilesToDelete->release();
    
    Wave *wave =getCurrentWave();
    
    if (wave!=NULL&&m->getTargets()->count() ==0 && wave->getRedCreeps()<=0&&wave->getGreenCreeps()<=0){
        
//        getNextWave();
//         gameHUD->updateWaveCount();
        schedule(schedule_selector(HelloWorld::waveWait),3.0);
         gameHUD->newWaveApproaching();
        }
    
}

CCPoint HelloWorld::boundLayerPos(CCPoint newPos) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint retval = newPos;
    retval.x = MIN(retval.x, 0);
    retval.x = MAX(retval.x, -_tileMap->getContentSize().width+winSize.width);
    retval.y = MIN(0, retval.y);
    retval.y = MAX(-_tileMap->getContentSize().height+winSize.height, retval.y);
    return retval;
}
bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    oldTouchLocation = convertTouchToNodeSpace(pTouch);
    oldTouchLocation =CCDirector::sharedDirector()->convertToGL(oldTouchLocation);
    oldTouchLocation =convertToNodeSpace(oldTouchLocation);
    return true;

}
void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){


}
void HelloWorld::ccTouchMoved(CCTouch *touch,CCEvent *event) {

    

    
    dragLayer(touch);

}
bool HelloWorld::canBuildOnTilePosition(CCPoint pos)
{
//    pos=ccpAdd(pos, ccp(0, 50));
	CCPoint towerLoc = tileCoordForPosition(pos);
	
	int tileGid =_background->tileGIDAt(towerLoc);
	CCDictionary *props = _tileMap->propertiesForGID(tileGid);
	const CCString *type = props->valueForKey("buildable");
	CCString* str=CCString::create("1");
   
    DataModel *m = DataModel::getModel();
     bool occupied = false;
    for (int i=0;i< m->getTowers()->count();i++) {
        Towers *tower=(Towers*)m->getTowers()->objectAtIndex(i);
        CCRect towerRect = CCRectMake(tower->getPosition().x - (tower->getContentSize().width/2),
                                      tower->getPosition().y - (tower->getContentSize().height/2),
                                      tower->getContentSize().width, tower->getContentSize().height);
        if (towerRect.containsPoint(pos)) {
            occupied = true;
        }
    }
    
	if(str->isEqual(type)&&!occupied) {
		return true;
	}
	
	return false;
}
void HelloWorld::dragLayer(CCTouch *touch){
    CCPoint touchLocation = convertTouchToNodeSpace(touch);
    CCPoint oldTouchLocation = touch->getPreviousLocationInView();
    oldTouchLocation = CCDirector::sharedDirector()->convertToGL(oldTouchLocation);
    oldTouchLocation =convertToNodeSpace(oldTouchLocation);
    CCPoint translation = ccpSub(touchLocation, oldTouchLocation);
    if(DataModel::getModel()->getIsDrag()){
        CCPoint newPos = ccpAdd(this->getPosition(), translation);
        this->setPosition(boundLayerPos(newPos));
    }
}
CCPoint  HelloWorld::tileCoordForPosition(CCPoint  position)
{
    CCSize ts=_tileMap->getTileSize();
    CCSize ms=_tileMap->getMapSize();
	int x = position.x / ts.width;
	int y = ((ms.height * ts.height) - position.y) / ts.height;
	return ccp(x,y);
}
void HelloWorld::addTower(CCPoint pos,int towerTag) {
//    pos = ccpAdd(pos, ccp(0, 50));

	CCLog("towerTag--------------- %d ",towerTag);
	DataModel *m = DataModel::getModel();
	
	Towers *target = NULL;
	
	CCPoint towerLoc =tileCoordForPosition(pos);
	
	int tileGid =_background->tileGIDAt(towerLoc);
	CCDictionary *props =_tileMap->propertiesForGID(tileGid);
	const CCString *type = props->valueForKey("buildable");
	
	 bool occupied = false;
    CCString *str=CCString::create("1");
    for (int i=0;i< m->getTowers()->count();i++) {
        Towers *tower=(Towers*)m->getTowers()->objectAtIndex(i);
        CCRect towerRect = CCRectMake(tower->getPosition().x - (tower->getContentSize().width/2),
                                      tower->getPosition().y - (tower->getContentSize().height/2),
                                      tower->getContentSize().width, tower->getContentSize().height);
        if (towerRect.containsPoint(pos)) {
            occupied = true;
        }
    }
    
	if(str->isEqual(type)&&!occupied) {
//		return true;
//	}
//	if(str->isEqual(type)) {
        int money= gameHUD->getResources();
        switch (towerTag) {
            case 1:
                if(money>=25){
                 target = Towers::create(TOWER_NAME[0].c_str(),0,Info::getInfo()->towerInfo->value[0]);
                    gameHUD->setResources(money-25);
                }else{
                    return;
                }
                
                break;
            case 2:
               
                if(money>=25){
                     target = Towers::create(TOWER_NAME[1].c_str(),1,Info::getInfo()->towerInfo->value[1]);
                    gameHUD->setResources(money-35);
                }else{
                    return;
                }
                break;
            case 3:
                if(money>=25){
                    target =Towers::create(TOWER_NAME[0].c_str(),0,Info::getInfo()->towerInfo->value[0]);
                    gameHUD->setResources(money-25);
                }else{
                    return;
                }
                break;
            case 4:
                if(money>=25){
                    target = Towers::create(TOWER_NAME[0].c_str(),0,Info::getInfo()->towerInfo->value[0]);
                    gameHUD->setResources(money-25);
                }else{
                    return;
                }
                break;
            default:
                break;
        }
		target->setPosition(ccp((towerLoc.x * 32) + 16, _tileMap->getContentSize().height - (towerLoc.y * 32) - 16));
		addChild(target,1);
		
		target->setTag(1);
		m->getTowers()->addObject(target);
//		target->release();
	} else {
//		CCLog("Tile Not Buildable");
	}
	
}
//void HelloWorld::handlePanFrom(UIPanGestureRecognizer *recognizer) {
//    
//    if (recognizer.state == UIGestureRecognizerStateBegan) {
//        
//        CGPoint touchLocation = [recognizer locationInView:recognizer.view];
//        touchLocation = [[CCDirector sharedDirector] convertToGL:touchLocation];
//        touchLocation = [self convertToNodeSpace:touchLocation];
//        
//    } else if (recognizer.state == UIGestureRecognizerStateChanged) {
//        
//        CGPoint translation = [recognizer translationInView:recognizer.view];
//        translation = ccp(translation.x, -translation.y);
//        CGPoint newPos = ccpAdd(self.position, translation);
//        self.position = [self boundLayerPos:newPos];
//        [recognizer setTranslation:CGPointZero inView:recognizer.view];
//        
//    } else if (recognizer.state == UIGestureRecognizerStateEnded) {
//        
//		float scrollDuration = 0.2;
//		CGPoint velocity = [recognizer velocityInView:recognizer.view];
//		CGPoint newPos = ccpAdd(self.position, ccpMult(ccp(velocity.x, velocity.y * -1), scrollDuration));
//		newPos = [self boundLayerPos:newPos];
//        
//		[self stopAllActions];
//		CCMoveTo *moveTo = [CCMoveTo actionWithDuration:scrollDuration position:newPos];
//		[self runAction:[CCEaseOut actionWithAction:moveTo rate:1]];
//        
//    }        
//
//}
