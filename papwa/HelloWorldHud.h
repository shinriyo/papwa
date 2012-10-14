//
//  HelloWorldHud.h
//  papwa
//
//  Created by sugita on 12/10/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#ifndef __HelloWorldHud_H__
#define __HelloWorldHud_H__ 

#include "cocos2d.h"

class HelloWorldHud : public cocos2d::CCLayer
{
public:
    ~HelloWorldHud();
    virtual bool init();  
    
    // touch detection
   	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
   	static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    // LAYER_NODE_FUNC does not exist in version2.x
    // LAYER_NODE_FUNC(HelloWorldHud);
	CREATE_FUNC(HelloWorldHud);
};

#endif // __HelloWorldHudH__