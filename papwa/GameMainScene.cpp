//
//  GameMainScene.cpp
//  papwa
//
//  Created by shinriyo on 10/8/12.
//
//

#include "GameMainScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameMain::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameMain *layer = GameMain::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    CCLOG("%s", "GameMain::scene");
   
	// return the scene
	return scene;
}

GameMain::~GameMain()
{
	CC_SAFE_RELEASE_NULL(_tileMap);
	CC_SAFE_RELEASE_NULL(_background);
	CC_SAFE_RELEASE_NULL(_player);
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    CCLOG("%s", "GameMain::init");
	if ( !CCLayer::init() )
	{
		return false;
	}
    
//	_tileMap = CCTMXTiledMap::tiledMapWithTMXFile("TileMap.tmx");
    _tileMap = CCTMXTiledMap::create("TileMap.tmx");
    _tileMap->retain();
    
	_background = _tileMap->layerNamed("Background");
    _background->retain();

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

	// これがないとタッチが有効にならない
	this->setTouchEnabled(true);
	
	return true;
}

// レイヤーがタッチイベントを受信する方法を変更するためにこのメソッドをオーバーライドする. 
void GameMain::registerWithTouchDispatcher()
{
    CCLOG("GameMain::registerWithTouchDispatcher");

//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
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
        
        //  画面上のワールド座標に変換
		touchLocation = this->convertToNodeSpace(touchLocation);
        
		// Create a projectile and put it at the player's location
        /*
		CCSprite *projectile = CCSprite::create("Projectile.png");
		//projectile->setPosition(_player->getPosition());
		this->addChild(projectile);
		
		// Determine where we wish to shoot the projectile to
		int realX;
		
		// Are we shooting to the left or right?
		CCPoint diff = ccpSub(touchLocation, _player->getPosition());

		if (diff.x > 0)
		{
			realX = (_tileMap->getMapSize().width * _tileMap->getTileSize().width) +
            (projectile->getContentSize().width/2);
		} else {
			realX = -(_tileMap	->getMapSize().width * _tileMap->getTileSize().width) -
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
		CCFiniteTimeAction *actionMoveTo = CCMoveTo::create(realMoveDuration, realDest);

		CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameMain::projectileMoveFinished));
		projectile->runAction(CCSequence::create(actionMoveTo, actionMoveDone));
		
		_projectiles->addObject(projectile);
*/
	}
}

// Playerの座標
void GameMain::setPlayerPosition(cocos2d::CCPoint position)
{
    CCLOG("setPlayerPosition");

	CCPoint tileCoord = this->tileCoordForPosition(position);
        /* あとで
         int tileGid = _meta->tileGIDAt(tileCoord);
	if (tileGid)
	{
		CCDictionary<std::string, CCString*> *properties = _tileMap->propertiesForGID(tileGid);
		if (properties)
		{
			CCString *collision = properties->objectForKey("Collidable");
			if (collision && (collision->toStdString().compare("True") == 0))
			{
				SimpleAudioEngine::sharedEngine()->playEffect("hit.caf");
				return;
			}
			
			CCString *collectable = properties->objectForKey("Collectable");
			if (collectable && (collectable->toStdString().compare("True") == 0))
			{
				_meta->removeTileAt(tileCoord);
				_foreground->removeTileAt(tileCoord);
				
				_numCollected++;
				_hud->numCollectedChanged(_numCollected);
				SimpleAudioEngine::sharedEngine()->playEffect("pickup.caf");
				
				if (_numCollected == 2) {
					this->win();
				}
			}
		}
	}
         */
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

void GameMain::setViewpointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width/2);
	x = MIN(x, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
	
	CCPoint actualPosition = ccp(x, y);
	
	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
	
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	
	this->setPosition(viewPoint);
}