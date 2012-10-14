//
//  OptionScene.h
//  papwa
//
//  Created by sugita on 12/10/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#ifndef __OPTIONSCENE_H__
#define __OPTIONSCENE_H__ 

#include "cocos2d.h"
USING_NS_CC;

class OptionScene : public cocos2d::CCLayer
{
public:
    ~OptionScene();
    virtual bool init();  
    
    // touch detection
   	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
   	static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
	CREATE_FUNC(OptionScene);
};

#endif // __OPTIONSCENE_H__