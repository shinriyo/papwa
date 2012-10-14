//
//  GameMainScene.h
//  papwa
//
//  Created by shinriyo on 10/8/12.
//
//

#ifndef __GameMainScene_H__
#define __GameMainScene_H__

#include "cocos2d.h"
USING_NS_CC;

class GameMain : public CCLayer
{
public:
    ~GameMain();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
    // touches
    virtual void registerWithTouchDispatcher();
   	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static CCScene* scene();
   	void setViewpointCenter(cocos2d::CCPoint point);
	void setPlayerPosition(cocos2d::CCPoint point);
	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
 
	// implement the "static node()" method manually
	CREATE_FUNC(GameMain);
    // ゲーム状態
   	CC_SYNTHESIZE(int, _mode, Mode);
 
    CC_SYNTHESIZE(CCTMXTiledMap*, _tileMap, TileMap);
    CC_SYNTHESIZE(CCTMXLayer*, _background, Background);
	CC_SYNTHESIZE(CCSprite *, _player, Player);
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _meta, Meta);
    
};

#endif // __GameMainScene_H__