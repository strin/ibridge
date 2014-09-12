#include "TableScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* TableScene::scene()
{
        // 'scene' is an autorelease object
        CCScene *scene = CCScene::create();
        
        // 'layer' is an autorelease object
        TableScene *layer = TableScene::create();
        CCLayer* bgLayer = new CCLayer();
        
        layer->bgLayer = bgLayer;
        CCSprite* sprite = CCSprite::spriteWithFile("bg1.png");
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        double bgscalex = (double)size.width/(double)sprite->getContentSize().width,
        bgscaley = (double)size.height/(double)sprite->getContentSize().height;
        sprite->setScaleX(bgscalex);
        sprite->setScaleY(bgscaley);
        sprite->setPosition(ccp(size.width/2, size.height/2));
        bgLayer->addChild(sprite, 0);

        // add layer as a child to scene
        scene->addChild(layer, 2);
        scene->addChild(bgLayer, 1);
        // return the scene
        return scene;
}

CCScene* TableScene::scene(TableScene* tableScene)
{
        // 'scene' is an autorelease object
        CCScene *scene = CCScene::create();
        
        // 'layer' is an autorelease object
        TableScene *layer = tableScene;
        CCLayer* bgLayer = new CCLayer();
        
        layer->bgLayer = bgLayer;
        CCSprite* sprite = CCSprite::spriteWithFile("bg1.png");
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        double bgscalex = (double)size.width/(double)sprite->getContentSize().width,
        bgscaley = (double)size.height/(double)sprite->getContentSize().height;
        sprite->setScaleX(bgscalex);
        sprite->setScaleY(bgscaley);
        sprite->setPosition(ccp(size.width/2, size.height/2));
        bgLayer->addChild(sprite, 0);
        
        // add layer as a child to scene
        scene->addChild(layer, 2);
        scene->addChild(bgLayer, 1);
        // return the scene
        return scene;
}

// on "init" you need to initialize your instance
bool TableScene::init()
{
        //////////////////////////////
        // 1. super init first
        if ( !CCLayer::init() )
        {
                return false;
        }
        
        // ask director the window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        // create table backround.
                
//        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        this->setTouchEnabled(true);
        
        this->game = new Game();
        game->start();
        this->addChild(game);
        
        return true;
}

void TableScene::menuCloseCallback(CCObject* pSender)
{
        CCScaleBy* scaleActions = CCScaleBy::actionWithDuration(0.5, 0.7);
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCMoveBy* moveActions = CCMoveBy::actionWithDuration(0.5, ccp(0-size.width*0.15, 0-size.height*0.15));
        CCSpawn* spawn = (CCSpawn*)CCSpawn::actions(scaleActions,moveActions, NULL);
        this->runAction(spawn);

//        CCDirector::sharedDirector()->end();
//        
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        exit(0);
//#endif
}


void TableScene::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
        if(game != 0)
                game->ccTouchesBegan(pTouches, event);
}

void TableScene::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
        if(game != 0)
                game->ccTouchesMoved(pTouches, event);
}

void TableScene::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
        if(game != 0)
                game->ccTouchesEnded(pTouches, event);
}

void TableScene::registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

