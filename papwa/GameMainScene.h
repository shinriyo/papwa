//
//  GameMainScene.h
//  papwa
//
//  Created by shinriyo on 10/8/12.
//
//

#ifndef __papwa__GameMainScene__
#define __papwa__GameMainScene__

#include "cocos2d.h"

class GameMain : public cocos2d::CCLayer
{
public:
    ~GameMain();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	void setViewpointCenter(cocos2d::CCPoint point);
    
	// implement the "static node()" method manually
	CREATE_FUNC(GameMain);
    
    CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
    
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _background, Background);
    
	CC_SYNTHESIZE(cocos2d::CCSprite *, _player, Player);
};

#endif // __HELLOWORLD_SCENE_H__