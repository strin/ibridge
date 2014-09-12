#ifndef __TABLE_SCENE_H__
#define __TABLE_SCENE_H__

#include "cocos2d.h"
#include "CCTouchDispatcher.h"
#include "Game.h"
#include "Card.h"

class TableScene : public cocos2d::CCLayer
{
public:
        // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
        virtual bool init();
        
        // there's no 'id' in cpp, so we recommend to return the class instance pointer
        static cocos2d::CCScene* scene();
        static cocos2d::CCScene* scene(TableScene* tableScene);
        
        // a selector callback
        void menuCloseCallback(CCObject* pSender);
        
        // preprocessor macro for "static create()" constructor ( node() deprecated )
        CREATE_FUNC(TableScene);
        
        
        virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
        virtual void ccTouchesMoved(CCSet* pTouches, CCEvent *event);
        virtual void ccTouchesEnded(CCSet* pTouches, CCEvent *event);
        virtual void registerWithTouchDispatcher();
        
        
        // the background layer.
        CCLayer* bgLayer;
        
        Game* game;
private:
        // bridge game.
        void* bridgeGame;
};

#endif // __HELLOWORLD_SCENE_H__
