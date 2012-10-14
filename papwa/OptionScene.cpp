//
//  OptionScene.cpp
//  papwa
//
//  Created by sugita on 12/10/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#import "OptionScene.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

CCScene* OptionScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	OptionScene *layer = OptionScene::create();
    
	// add layer as a child to scene
	scene->addChild(layer);

    
	// return the scene
	return scene;
}

bool OptionScene::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}
bool OptionScene::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	return true;
}

void OptionScene::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
}

OptionScene::~OptionScene()
{
}