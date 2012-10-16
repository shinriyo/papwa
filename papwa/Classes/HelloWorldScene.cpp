#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#include "CCUIScrollView.h"
#include "CCBReader.h"
#include "CCNodeLoaderLibrary.h"
USING_NS_CC_EXT;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    // ページ遷移
    CCMenuItemImage *pGotogameItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::gotoGameMainCallback) );
    pGotogameItem->setPosition( ccp(size.width / 2, size.height / 2 - 50) );

    CCMenuItemImage *pGotooptionItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::gotoOptionCallback) );
    pGotooptionItem->setPosition( ccp(size.width / 2, size.height / 2 - 90) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pGotogameItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    CCMenu* pMenu2 = CCMenu::create(pGotooptionItem, NULL);
    pMenu2->setPosition( CCPointZero );
    this->addChild(pMenu2, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // フォントテスト
    CCLabelTTF* pXLabel = CCLabelTTF::create("Zapfino", "Zapfino", 34);
    pXLabel->setPosition( ccp(size.width / 2, size.height - 50) );
    this->addChild(pXLabel, 1);
    CCLabelTTF* pTLabel = CCLabelTTF::create("Thonburi", "Thonburi", 34);
    pTLabel->setPosition( ccp(size.width / 2, size.height - 80) );
    this->addChild(pTLabel, 1);
    CCLabelTTF* pSTHLabel = CCLabelTTF::create("STHeitiTC-Light", "STHeitiTC-Light", 34);
    pSTHLabel->setPosition( ccp(size.width / 2, size.height - 110) );
    this->addChild(pSTHLabel, 1);
    CCLabelTTF* pGPLabel = CCLabelTTF::create("Geeza Pro", "Geeza Pro", 34);
    pGPLabel->setPosition( ccp(size.width / 2, size.height - 140) );
    this->addChild(pGPLabel, 1);
    CCLabelTTF* pGeoPLabel = CCLabelTTF::create("Geeza Pro", "Georgia", 34);
    pGeoPLabel->setPosition( ccp(size.width / 2, size.height - 170) );
    this->addChild(pGeoPLabel, 1);
    CCLabelTTF* pVPLabel = CCLabelTTF::create("Verdana", "Verdana", 34);
    pVPLabel->setPosition( ccp(size.width / 2, size.height - 200) );
    this->addChild(pVPLabel, 1);

    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
   
    // CCUIScrollViewの実験
    CCUIScrollView *scrollView = CCUIScrollView::scrollViewWithCCRect(CCRectMake(20, 20, 444, 200));
    this->addChild(scrollView);
    
    return true;
}


// 電源落とす
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// game
void HelloWorld::gotoGameMainCallback(CCObject* pSender)
{
//    CCTransitionScene *transition = CCTransitionPageTurn::create(3.0f, GameMain::scene(), false);
//    CCDirector::sharedDirector()->replaceScene(transition);
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, GameMain::scene()));
}

// option 
void HelloWorld::gotoOptionCallback(CCObject* pSender)
{
    CCTransitionScene *transition = CCTransitionPageTurn::create(3.0f, OptionScene::scene(), false);
    //    CCDirector::sharedDirector()->pushScene(transition);
    CCDirector::sharedDirector()->replaceScene(transition);
    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
}
