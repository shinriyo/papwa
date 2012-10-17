//
//  CCUIScrollView.cpp
//  papwa
//
//  Created by sugita on 12/10/16.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.

#include "CCUIScrollView.h"
USING_NS_CC;
#define contentViewFontColorRed  (GLubyte)(255 * 0.8) 
#define contentViewFontColorGreen  (GLubyte)(255 * 0.9) 
#define contentViewFontColorBlue  (GLubyte)(255 * 0.2) 
#define contentViewFontColorAlpha 1.0
#define kScrollLayerCellPositionY 25
#define myFontColor ccc3(contentViewFontColorRed, contentViewFontColorGreen, contentViewFontColorBlue)

CCLayerColor*  CCUIScrollView::getScrollLayerCellAtIndex(int i){
    //scrollLayer一行:scrollLayerCell
    CCLayerColor *scrollLayerCell = CCLayerColor::create(ccc4((i%2==0)?0:100,(i%2==0)?100:0,0,i*30+50), 444, 50);
    scrollLayerCell->setTouchEnabled(false);
    scrollLayerCell->setPosition(ccp(0,i*50+50));
    CCLabelTTF *pLabelInfoName  = CCLabelTTF::create("item1:", "Arial", 20);
    pLabelInfoName->setScaleX(0.65);
    pLabelInfoName->setScaleY(0.65); 
    pLabelInfoName->setColor(myFontColor);
    pLabelInfoName->setAnchorPoint(ccp(0.0,0.5));
    pLabelInfoName->setPosition(ccp(150, kScrollLayerCellPositionY));
    scrollLayerCell->addChild(pLabelInfoName);
    CCLabelTTF *pLabelInfoValue = CCLabelTTF::create("item2", "Arial", 20);
    pLabelInfoValue->setScaleX(0.65);
    pLabelInfoValue->setScaleY(0.65); 
    pLabelInfoValue->setColor(myFontColor);
    pLabelInfoValue->setPosition(ccp(300, kScrollLayerCellPositionY));
    scrollLayerCell->addChild(pLabelInfoValue);
    return scrollLayerCell;
}


CCUIScrollView::CCUIScrollView(const CCRect& mRect){
    this->setPosition(mRect.origin);
    this->setContentSize(mRect.size);
    this->setTouchEnabled(true);
    this->setIsLockHorizontal(true);
    this->setIsScrolling(false);
    contentLayer = CCLayerColor::create(
        ccc4( 120,120, 120,80), mRect.size.width, mRect.size.height);
    contentLayer->ignoreAnchorPointForPosition(false);
    contentLayer->setAnchorPoint(ccp(0.5,1.0));
#warning this is for test
    for (int i = 0; i < 5; i++) {
        contentLayer->addChild(getScrollLayerCellAtIndex(i));
    }
    CCPoint contentLayerPosition = CCPointMake(mRect.origin.x + mRect.size.width/2.0, mRect.origin.y+mRect.size.height);
    contentLayer->setPosition(contentLayerPosition);
    this->addChild(contentLayer);
}

CCUIScrollView* CCUIScrollView::scrollViewWithCCRect(const CCRect& mRect){
    CCUIScrollView *pScrollView = new CCUIScrollView(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView);
    return NULL;
}

CCUIScrollView* CCUIScrollView::scrollViewWithColorAndCCRect(const ccColor4B& color,const CCRect& mRect){
    CCUIScrollView *pScrollView = new CCUIScrollView(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->setContentLayerColor(color);
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView);
    return NULL;
}

CCUIScrollView::~CCUIScrollView(){
    
}

bool CCUIScrollView::init(){
    //TODO
    return true;
}

void CCUIScrollView::registerWithTouchDispatcher(){
    //change 0 if you need priority higher or lower.
    //swallows the touch message
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    CCTouchDispatcher* touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    touchDispatcher->addTargetedDelegate(this, 0, true);
}

bool CCUIScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
//    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    CCPoint locationInView = pTouch->getLocationInView();
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
    if (this->getIsTouchInContentLayer(pTouch)) {
        isScrolling = true;
        printf("Began Scrolling\n");
    }
    else 
        isScrolling = false;
    return isScrolling;
}

void CCUIScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
//    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    CCPoint locationInView = pTouch->getLocationInView();
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
    CCPoint deltaPoint = ccpSub(currentTouchPoint, preTouchPoint);
    if(this->getIsLockHorizontal())
        deltaPoint.x=0;
    else if(this->getIsLockVertical())
        deltaPoint.y=0; 
    contentLayer->setPosition(ccpAdd(contentLayer->getPosition(), deltaPoint));
    preTouchPoint = currentTouchPoint;
#warning this is for test
    printf("Moving\n");
}

void CCUIScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
#warning this is for test
    printf("Moving End\n");
}

void CCUIScrollView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    
}

void CCUIScrollView::setContentLayerColor(const ccColor4B &mColor){
    contentLayer->setColor(ccc3(mColor.r, mColor.g, mColor.b));
    contentLayer->setOpacity(mColor.a);
}

bool CCUIScrollView::getIsTouchInContentLayer( CCTouch *pTouch){
    CCPoint nodeSpaceLocation = this->convertTouchToNodeSpace(pTouch);
#warning this is for test
    printf("nodeSpaceLocation: %f,%f     ",nodeSpaceLocation.x,nodeSpaceLocation.y);
    CCRect contentLayerRect = CCRectZero;
    contentLayerRect.origin = CCPointZero;
    contentLayerRect.size = contentLayer->getContentSize();
#warning this is for test
    printf("RectOrigin:%f,%f  RectSize:%f,%f\n",contentLayerRect.origin.x,contentLayerRect.origin.y,contentLayerRect.size.width,contentLayerRect.size.height);
    //return CCRect::CCRectContainsPoint(contentLayerRect, nodeSpaceLocation);
    return contentLayerRect.containsPoint(nodeSpaceLocation);
}

void CCUIScrollView::visit(){
    CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
    glEnable(GL_SCISSOR_TEST);
    glScissor(convertedLocationLowerLeft.x, convertedLocationLowerLeft.y,
              this->getContentSize().width, this->getContentSize().height);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
}
