//
//  Game.h
//  iBridge
//
//  Created by Tianlin Shi on 12/9/12.
//
//

#ifndef __iBridge__Game__
#define __iBridge__Game__

#include <iostream>
#include <list>

#include "Table.h"
#include "cocos2d.h"
#include "Card.h"

using namespace std;
using namespace cocos2d;

class Game : public CCLayer{
public:
//        Game(void* bridgeGame);
        Game();
        
        void start();
        static void* gameOn(void* game);
        
        virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
        virtual void ccTouchesMoved(CCSet* pTouches, CCEvent *event);
        virtual void ccTouchesEnded(CCSet* pTouches, CCEvent *event);
        
        void cardArrayTolist(int player, list<int>* cardNumList,
                             list<Card::CardType>* cardTypeList);
        
        static void* bridgeGame;
        
        // Platform IO.
        string getPlay();
        string getTeamPlay();
        void postPlay(int player, string play);
        void postWin(int player);
        
        // State Indicator.s
        bool init;
        bool finished;
private:
        
        Pack* leftPack, *rightPack, *topPack, *userPack;
        Pack* orderedPack[5];
        Table* table;
        pthread_t pid; // The game thread.
};


#endif /* defined(__iBridge__Game__) */
