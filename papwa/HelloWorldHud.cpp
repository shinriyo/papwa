//
//  HelloWorldHud.cpp
//  papwa
//
//  Created by sugita on 12/10/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#import "HelloWorldHud.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

USING_NS_CC;

CCScene* HelloWorldHud::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
    
	// 'layer' is an autorelease object
    // deprecated in v2.0
	// HelloWorldHud *layer = HelloWorldHud::node();
	HelloWorldHud *layer = HelloWorldHud::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool HelloWorldHud::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // add "HelloWorld" splash screen"
    // change your bg sprite 
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    return true;
}
bool HelloWorldHud::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	return true;
}

void HelloWorldHud::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
}

HelloWorldHud::~HelloWorldHud()
{
}