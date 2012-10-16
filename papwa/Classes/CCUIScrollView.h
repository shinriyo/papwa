//
//  UIScrollView.h
//  papwa
//
//  Created by shinriyo on 12/10/16.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#ifndef cocos2dUI_CCUIScrollView_h
#define cocos2dUI_CCUIScrollView_h
#include "cocos2d.h"
USING_NS_CC;

class CCUIScrollView:public CCLayer{
public:
    ~CCUIScrollView();
    CCUIScrollView(const CCRect& mRect);
    static CCUIScrollView* scrollViewWithCCRect(const CCRect& mRect);
    static CCUIScrollView* scrollViewWithColorAndCCRect(const ccColor4B& color,const CCRect& mRect);
    virtual bool init();
    
    //addTargetedDelegate
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    //clip contentLayer
    virtual void visit();
    
    //add child to contentLayer
    virtual void addChildInContentLayer(CCNode * child){contentLayer->addChild(child); }
    virtual void addChildInContentLayer(CCNode * child, int zOrder){contentLayer->addChild(child, zOrder); }
    virtual void addChildInContentLayer(CCNode * child, int zOrder, int tag){contentLayer->addChild(child, zOrder, tag);}
    
    //set method
    void setContentLayerColor(const ccColor4B& mColor);
    void setContentLayerSize(const CCSize& mSize){contentLayer->setContentSize(mSize);}
    
    //get method
    virtual bool getIsTouchInContentLayer(CCTouch *pTouch);
    const ccColor3B& getContentLayerColor(){return contentLayer->getColor();}
    const CCSize& getContentLayerSize(){return contentLayer->getContentSize();}
#warning this method is for test.
    CCLayerColor*  getScrollLayerCellAtIndex(int i);
protected:
    CC_SYNTHESIZE(CCLayerColor*, contentLayer, ContentLayer)
    CC_SYNTHESIZE(bool, isLockHorizontal, IsLockHorizontal)
    CC_SYNTHESIZE(bool, isLockVertical, IsLockVertical)
    CC_SYNTHESIZE(bool, isScrolling, IsScrolling)
private:
    //CCPoint based on world coordinates
    CCPoint preTouchPoint;
    CCPoint currentTouchPoint;
};


#endif//cocos2dUI_CCUIScrollView_h
