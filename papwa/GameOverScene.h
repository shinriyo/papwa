//
//  GameOverScene.h
//  TileBasedGame
//
//  Created by sugita on 12/10/11.
//  Copyright (c) 2012 __shinriyo__. All rights reserved.
//

#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

//class GameOverLayer : public cocos2d::CCLayerColor
class GameOverLayer : public CCLayerColor
{
public:
    GameOverLayer():_label(NULL) {};
    virtual ~GameOverLayer();
    bool init();
    CREATE_FUNC(GameOverLayer);
    
    void gameOverDone();
    // implement the "static node()" method manually
    
    //CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
    CC_SYNTHESIZE_READONLY(CCLabelTTF*, _label, Label);
};

class GameOverScene : public CCScene
{
public:
    GameOverScene():_layer(NULL) {};
    virtual ~GameOverScene();
    bool init();
    CREATE_FUNC(GameOverScene);
    
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};

#endif // _GAME_OVER_SCENE_H_