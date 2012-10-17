//
//  GameMainScene.cpp
//  papwa
//
//  Created by shinriyo on 10/8/12.
//
//

#include "GameMainScene.h"
#include "SimpleAudioEngine.h"

using std::vector;
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameMain::scene()
{
    CCLOG("%s", "GameMain::scene");
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    GameMain *layer = GameMain::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    GameHud *hud = GameHud::create();
    hud->retain();
    scene->addChild(hud);
    layer->setHud(hud);
    hud->setGameLayer(layer);
    
   
    // return the scene
    return scene;
}

GameMain::~GameMain()
{
    CC_SAFE_RELEASE_NULL(_tileMap);
    CC_SAFE_RELEASE_NULL(_background);
    CC_SAFE_RELEASE_NULL(_foreground);
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_meta);
	CC_SAFE_RELEASE_NULL(_hud);
    
	CC_SAFE_RELEASE_NULL(_enemies);
	CC_SAFE_RELEASE_NULL(_projectiles);
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    CCLOG("%s", "GameMain::init");
    if ( !CCLayer::init() )
    {
        return false;
    }
   
    // 敵と弾
	_enemies = new CCArray();
	_projectiles = new CCArray();

    
//    _tileMap = CCTMXTiledMap::tiledMapWithTMXFile("TileMap.tmx");
    _tileMap = CCTMXTiledMap::create("TileMap.tmx");
    _tileMap->retain();
    
    // マップ背景だがアクセスはされてない？
    _background = _tileMap->layerNamed("Background");
    _background->retain();
    
    // アイテム・障害物レイヤー
    _foreground = _tileMap->layerNamed("Foreground");
    _foreground->retain();
    
    // 
    _meta = _tileMap->layerNamed("Meta");
    _meta->retain();

    CCTMXObjectGroup *objects = _tileMap->objectGroupNamed("Objects");
    CCAssert(objects != NULL, "'Objects' object group not found");
    
    CCDictionary *spawnPoint = objects->objectNamed("SpawnPoint");
    CCAssert(spawnPoint != NULL, "SpawnPoint object not found");
    // x=45,y=1263;
    int x = ((CCString *)spawnPoint->objectForKey("x"))->intValue();
    int y = ((CCString *)spawnPoint->objectForKey("y"))->intValue();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
 
    _player = CCSprite::create("Player.png");
    _player->retain();
    _player->setPosition(ccp (x, y));
    CCLOG("x:%d, y:%d", x, y);
 
    // 描画順
    this->addChild(_tileMap);
    this->addChild(_player);
    this->setViewpointCenter(_player->getPosition());

    // 敵の初期化
   	//CCMutableArray<CCStringToStringDictionary*> *allObjects = objects->getObjects();
   	CCArray *allObjects = objects->getObjects();
	//CCMutableArray<CCStringToStringDictionary*>::CCMutableArrayIterator it;
	//for (it = allObjects->begin(); it != allObjects->end(); ++it)
    CCObject *it = NULL;
    CCARRAY_FOREACH( allObjects, it )
	{
		//if ((*it)->objectForKey(std::string("Enemy")) != NULL)
		if (static_cast<CCDictionary*>(it)->objectForKey("Enemy") != NULL)
		{
			//int x = (*it)->objectForKey("x")->toInt();
			//int y = (*it)->objectForKey("y")->toInt();
            int x = ((CCString *)(static_cast<CCDictionary*>(it)->objectForKey("x")))->intValue();
            int y = ((CCString *)(static_cast<CCDictionary*>(it)->objectForKey("y")))->intValue();
			this->addEnemyAt(x, y);
		}
	}
    
    // これがないとタッチが有効にならない
    this->setTouchEnabled(true);
    // アイテム数の初期化
    _numCollected = 0;

    // スケジュール 
    this->schedule(schedule_selector(GameMain::testCollisions));
    
    return true;
}

// 敵の追加
void GameMain::addEnemyAt(int x, int y)
{
	//CCSprite *enemy = CCSprite::spriteWithFile("enemy1.png");
	CCSprite *enemy = CCSprite::create("enemy1.png");
	enemy->retain();
	enemy->setPosition(ccp(x, y));
	this->addChild(enemy);
	// Use our animation method and
	// start the enemy moving toward the player
	this->animateEnemy(enemy);
	_enemies->addObject(enemy);
}

// callback. starts another iteration of enemy movement.
void GameMain::enemyMoveFinished(cocos2d::CCSprite *enemy)
{
	this->animateEnemy(enemy);
}

// a method to move the enemy 10 pixels toward the player
void GameMain::animateEnemy(CCSprite *enemy)
{
	// speed of the enemy
	float actualDuration = 0.3;
    
	//rotate to face the player
	CCPoint diff = ccpSub(_player->getPosition(), enemy->getPosition());
	float angleRadians = atanf((float)diff.y / (float)diff.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = -1 * angleDegrees;
	if (diff.x < 0) {
		cocosAngle += 180;
	}
	enemy->setRotation(cocosAngle);
	
	//CCPoint moveBy = ccpMult(ccpNormalize(ccpSub(_player->getPosition(),enemy->getPosition())), 10);
	CCPoint moveBy = ccpMult(ccpNormalize(ccpSub(_player->getPosition(),enemy->getPosition())), 10);
    
	// Create the actions
	//CCFiniteTimeAction *actionMove = CCMoveBy::actionWithDuration(actualDuration, moveBy);
	CCFiniteTimeAction *actionMove = CCMoveBy::create(actualDuration, moveBy);
//	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::enemyMoveFinished));
	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameMain::enemyMoveFinished));
	//enemy->runAction(CCSequence::actions(actionMove,
	enemy->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

// レイヤーがタッチイベントを受信する方法を変更するためにこのメソッドをオーバーライドする. 
void GameMain::registerWithTouchDispatcher()
{
    CCLOG("GameMain::registerWithTouchDispatcher");

//    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    CCTouchDispatcher* touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    touchDispatcher->addTargetedDelegate(this, 0, true);
}

bool GameMain::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    return true;
}

void GameMain::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    CCLOG("GameMain::ccTouchEnded");
    // 通常移動モード
    if (_mode == 0)
    {
        /* 
        CCPoint touchLocation = touch->locationInView(touch->view());
        touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
        */
        //CCPoint touchLocation = touch->locationInView();
        CCPoint touchLocation = touch->getLocationInView();
        // OpenGL座標へ一旦置き換える
        touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
        //  画面上のワールド座標に変換
        touchLocation = this->convertToNodeSpace(touchLocation);
        
        CCPoint playerPos = _player->getPosition();
        CCPoint diff = ccpSub(touchLocation, playerPos);
        
        // using fabs because using abs throws a "abs in ambiguous" error
        if (fabs(diff.x) > fabs(diff.y)) {
            if (diff.x > 0) {
                playerPos.x += _tileMap->getTileSize().width;
            } else {
                playerPos.x -= _tileMap->getTileSize().width; 
            }    
        } else {
            if (diff.y > 0) {
                playerPos.y += _tileMap->getTileSize().height;
            } else {
                playerPos.y -= _tileMap->getTileSize().height;
            }
        }
        CCLOG("setPlayerPosition before");

        // 実際の移動
        if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
            playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
            playerPos.y >= 0 && playerPos.x >= 0 ) 
        {
            this->setPlayerPosition(playerPos);
            
        }
        
         this->setViewpointCenter(_player->getPosition());
        // 攻撃モード
    } else {
        // Find where the touch is
        CCPoint touchLocation = touch->getLocationInView();    
        // OpenGL座標へ一旦置き換える
        touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
        //  画面上のワールド座標に変換
        touchLocation = this->convertToNodeSpace(touchLocation);
        
        // Create a projectile and put it at the player's location
        CCSprite *projectile = CCSprite::create("Projectile.png");
        projectile->setPosition(_player->getPosition());
        this->addChild(projectile);
        
        // Determine where we wish to shoot the projectile to
        int realX;
        
        // Are we shooting to the left or right?
        CCPoint diff = ccpSub(touchLocation, _player->getPosition());

        // 弾の消える位置
        if (diff.x > 0)
        {
            realX = (_tileMap->getMapSize().width * _tileMap->getTileSize().width) +
            (projectile->getContentSize().width/2);
        } else {
            realX = -(_tileMap->getMapSize().width * _tileMap->getTileSize().width) -
            (projectile->getContentSize().width/2);
        }

        float ratio = (float) diff.y / (float) diff.x;
        int realY = ((realX - projectile->getPosition().x) * ratio) + projectile->getPosition().y;
        CCPoint realDest = ccp(realX, realY);
        
        
        // Determine the length of how far we're shooting
        int offRealX = realX - projectile->getPosition().x;
        int offRealY = realY - projectile->getPosition().y;
        float length = sqrtf((offRealX*offRealX) + (offRealY*offRealY));
        float velocity = 480/1; // 480pixels/1sec
        float realMoveDuration = length/velocity;
        
        // Move projectile to actual endpoint
        // 実際の終了地点まで飛ばす
        CCFiniteTimeAction *actionMoveTo = CCMoveTo::create(realMoveDuration, realDest);

        // 消す処理
        CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameMain::projectileMoveFinished));
        projectile->runAction(CCSequence::create(actionMoveTo, actionMoveDone));
        
        _projectiles->addObject(projectile);
    }
}

// Playerの座標
void GameMain::setPlayerPosition(cocos2d::CCPoint position)
{
    CCLOG("setPlayerPosition");

    CCPoint tileCoord = this->tileCoordForPosition(position);
    // 障害物
    int tileGid = _meta->tileGIDAt(tileCoord);
    if (tileGid)
    {
//        CCDictionary<std::string, CCString*> *properties = _tileMap->propertiesForGID(tileGid);
        CCDictionary *properties = _tileMap->propertiesForGID(tileGid);
        
        if (properties)
        {
            // 衝突の有無
            //CCString *collision = properties->objectForKey("Collidable");
            CCString *collision = ((CCString *)properties->objectForKey("Collidable"));
            
            //if (collision && (collision->toStdString().compare("True") == 0))
            if (collision && (collision->compare("True") == 0))
            {
                SimpleAudioEngine::sharedEngine()->playEffect("hit.caf");
                return;
            }
            
            // アイテムの有無
            //CCString *collectable = properties->objectForKey("Collectable");
            CCString *collectable = ((CCString *)properties->objectForKey("Collectable"));
            
            //if (collectable && (collectable->toStdString().compare("True") == 0))
            if (collectable && (collectable->compare("True") == 0))
            {
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);
                
                _numCollected++;
                // HUDはまだ
                _hud->numCollectedChanged(_numCollected);
                SimpleAudioEngine::sharedEngine()->playEffect("pickup.caf");
                
                // 勝利面判定
                if (_numCollected == 2) {
                    this->win();
                }
            }
        }
    }

    SimpleAudioEngine::sharedEngine()->playEffect("move.caf");
    _player->setPosition(position);
}

// タイルの座標にする
CCPoint GameMain::tileCoordForPosition(cocos2d::CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

// ビューを真ん中へ
void GameMain::setViewpointCenter(CCPoint position)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width/2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    
    this->setPosition(viewPoint);
}

void GameMain::projectileMoveFinished(CCSprite *sprite)
{
	this->removeChild(sprite, true);
	_projectiles->removeObject(sprite, true);
}

// スケジュール
void GameMain::testCollisions(cocos2d::CCTime dt)
{
    //CCMutableArray<CCSprite*> *projectilesToDelete = new CCMutableArray<CCSprite*>;
    CCArray *projectilesToDelete = new CCArray();
    
    //CCMutableArray<CCSprite *>::CCMutableArrayIterator it, jt;

    // iterate through projectiles
    //for (it = _projectiles->begin(); it != _projectiles->end(); it++) {
    CCObject *it = NULL;
    CCObject *jt = NULL;

    CCARRAY_FOREACH( _projectiles, it )
    {

        //CCSprite *projectile = *it;
        CCSprite *projectile = static_cast<CCSprite*>(it);
        CCRect projectileRect = CCRectMake(projectile->getPosition().x - (projectile->getContentSize().width/2),
                                           projectile->getPosition().y - (projectile->getContentSize().height/2),
                                           projectile->getContentSize().width,
                                           projectile->getContentSize().height);
        
        CCArray *targetsToDelete = new CCArray();
       
        // iterate through enemies, see if any intersect with current projectile
        //for (jt = _enemies->begin(); jt != _enemies->end(); jt++)
        jt = NULL;
        CCARRAY_FOREACH( _enemies, jt )
        {
            //CCSprite *target = *jt;
            CCSprite *target = static_cast<CCSprite*>(jt);
            CCRect targetRect = CCRectMake(
                                           target->getPosition().x - (target->getContentSize().width/2),
                                           target->getPosition().y - (target->getContentSize().height/2),
                                           target->getContentSize().width,
                                           target->getContentSize().height);
            
            //if (CCRect::CCRectIntersectsRect(projectileRect, targetRect)) {
            if (projectileRect.intersectsRect(targetRect))
            {
                targetsToDelete->addObject(target);
            }
        }
        
        // delete all hit enemies
        //for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
        jt = NULL;
        CCARRAY_FOREACH( targetsToDelete, jt )
        {
            //_enemies->removeObject(*jt);
            //this->removeChild((*jt), true);
            this->removeChild(static_cast<CCNode*>(jt), true);
        }
        
        if (targetsToDelete->count() > 0)
        {
            projectilesToDelete->addObject(projectile);
        }
        
        targetsToDelete->release();
    }
    
    // remove all the projectiles that hit.
    //for (it = projectilesToDelete->begin(); it != projectilesToDelete->end(); it++) {
    it = NULL;
    CCARRAY_FOREACH( projectilesToDelete, it )
    {
        //CCSprite *projectile = *it;
        CCSprite *projectile = static_cast<CCSprite*>(it);
        _projectiles->removeObject(projectile, true);
        this->removeChild(projectile, true);
    }
    
    //for (jt = _enemies->begin(); jt != _enemies->end(); jt++)
    jt = NULL;
    CCARRAY_FOREACH( _enemies, jt )
    {
        //CCSprite *target = *jt;
        CCSprite *target = static_cast<CCSprite*>(jt);
        CCRect targetRect = CCRectMake(
                                       target->getPosition().x - (target->getContentSize().width/2),
                                       target->getPosition().y - (target->getContentSize().height/2),
                                       target->getContentSize().width,
                                       target->getContentSize().height);
        
        //if (CCRect::CCRectContainsPoint(targetRect, _player->getPosition())) {
        if (targetRect.containsPoint(_player->getPosition())) {
            this->lose();
        }
    }
}

// 勝利画面
void GameMain::win()
{
    GameOverScene *gameOverScene = GameOverScene::create();
    gameOverScene->getLayer()->getLabel()->setString("You Win!");
    CCDirector::sharedDirector()->replaceScene(gameOverScene);
}

// 敗北画面
void GameMain::lose()
{
    GameOverScene *gameOverScene = GameOverScene::create();
    gameOverScene->getLayer()->getLabel()->setString("You Lose!");
    CCDirector::sharedDirector()->replaceScene(gameOverScene);
}