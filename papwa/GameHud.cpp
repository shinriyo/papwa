//
//  GameHud.cpp
//  papwa
//
//  Created by sugita on 12/10/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#import "GameHud.h"
#include "SimpleAudioEngine.h"
#include "GameMainScene.h"

using namespace std;
using namespace CocosDenshion;

CCScene* GameHud::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
    
	// 'layer' is an autorelease object
    // deprecated in v2.0
	// GameHud *layer = GameHud::node();
	GameHud *layer = GameHud::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool GameHud::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//_label = CCLabelTTF::labelWithString("0", CCSizeMake(50, 20), CCTextAlignmentRight, "Verdana-Bold", 18.0);
	_label = CCLabelTTF::create("0", "Verdana-Bold", 18.0, CCSizeMake(50, 20), kCCTextAlignmentRight);
	_label->setColor(ccc3(0, 0, 0));
	
	int margin = 10;
	
	_label->setPosition(ccp(winSize.width - (_label->getContentSize().width / 2) - margin, 
							_label->getContentSize().height / 2 + margin));
	
	this->addChild(_label);
	
	//CCMenuItem *on = CCMenuItemImage::itemFromNormalImage("projectile-button-on.png", "projectile-button-on.png", NULL, NULL);
	CCMenuItem *on = CCMenuItemImage::create("projectile-button-on.png", "projectile-button-on.png", NULL, NULL);
	//CCMenuItem *off = CCMenuItemImage::itemFromNormalImage("projectile-button-off.png", "projectile-button-off.png", NULL, NULL);
	CCMenuItem *off = CCMenuItemImage::create("projectile-button-off.png", "projectile-button-off.png", NULL, NULL);
	
	//CCMenuItemToggle *toggleItem = CCMenuItemToggle::itemWithTarget(this, menu_selector(HelloWorldHud::projectileButtonTapped), off, on, NULL);
	CCMenuItemToggle *toggleItem = CCMenuItemToggle::createWithTarget (this, menu_selector(GameHud::projectileButtonTapped), off, on, NULL);
	
	CCMenu *toggleMenu = CCMenu::create(toggleItem, NULL);
	toggleMenu->setPosition(ccp(100, 32));
	this->addChild(toggleMenu);
	
	return true;
}
bool GameHud::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	return true;
}

void GameHud::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
}

GameHud::~GameHud()
{
    CC_SAFE_RELEASE_NULL(_label);
//    CC_SAFE_RELEASE_NULL(_gameLayer);
}


void GameHud::numCollectedChanged(int numCollected)
{
	char *str = (char *)malloc(sizeof(str) * 10);
	sprintf(str, "%d", numCollected);
	_label->setString(str);
	free(str);
}

void GameHud::projectileButtonTapped(CCObject *sender)
{
	if (_gameLayer->getMode() == 0)
	{
		_gameLayer->setMode(1);
	}
	else
    {
		_gameLayer->setMode(0);
	}
}
