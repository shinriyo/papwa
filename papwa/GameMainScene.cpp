//
//  GameMainScene.cpp
//  papwa
//
//  Created by shinriyo on 10/8/12.
//
//

#include "GameMainScene.h"
#include "SimpleAudioEngine.h"

//using namespace cocos2d;
//using namespace CocosDenshion;

USING_NS_CC;

CCScene* GameMain::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	GameMain *layer = GameMain::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
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
//	int x = spawnPoint->getStrKey("x")->toInt();
    int x = (int)spawnPoint->objectForKey("x");
	int y = (int)spawnPoint->objectForKey("y");

	_player = CCSprite::create("Player.png");
	_player->retain();
	
	_player->setPosition(ccp (x, y));

	// 描画順
    this->addChild(_tileMap);
	this->addChild(_player);
	
	this->setViewpointCenter(_player->getPosition());
	
	return true;
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