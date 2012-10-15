//
//  GameHud.h
//  papwa
//
//  Created by sugita on 12/10/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#ifndef __GameHud_H__
#define __GameHud_H__ 

#include "cocos2d.h"

USING_NS_CC;

class GameMain;

class GameHud : public cocos2d::CCLayer
{
    cocos2d::CCLabelTTF *_label;
public:
    ~GameHud();
    virtual bool init();  
	void numCollectedChanged(int numCollected);
	void projectileButtonTapped(CCObject *sender);
    
    // touch detection
   	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
   	static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    // LAYER_NODE_FUNC does not exist in version2.x
    // LAYER_NODE_FUNC(GameHud);
	CREATE_FUNC(GameHud);
    
    CC_SYNTHESIZE(GameMain *, _gameLayer, GameLayer);
};

#endif // __GameHudH__