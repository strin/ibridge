//
//  Game.cpp
//  iBridge
//
//  Created by Tianlin Shi on 12/9/12.
//
//

#include "Game.h"

#include "Pack.h"
#include "Card.h"
#include "Table.h"
#include "CCObject.h"
#include "pthread.h"
#include "BridgeGame.h"
#include "Utils.h"
#include "WinScene.h"

//Game::Game(void* bridgeGame){
//        this->init();
//        this->bridgeGame = bridgeGame;
//}
void* Game::bridgeGame = NULL;

Game::Game() {
        init = false;
}
void Game::start() {
        list<int>* cardNumList = new list<int>();
        list<Card::CardType>* cardTypeList = new list<Card::CardType>();
        
        BridgeGame* game  = (BridgeGame*)bridgeGame;
        
        game->game = this;
        
        this->cardArrayTolist(1, cardNumList, cardTypeList);
        userPack = new Pack(1, *cardNumList, *cardTypeList, true, Pack::top);
        this->cardArrayTolist(4, cardNumList, cardTypeList);
        if((((BridgeGame*)Game::bridgeGame)->LoadDealer()+1)%4+1 == 4)
                rightPack = new Pack(4, *cardNumList, *cardTypeList, true, Pack::left);
        else
//                rightPack = new Pack(4, *cardNumList, *cardTypeList, false, Pack::left);
                rightPack = new Pack(4, *cardNumList, *cardTypeList, true, Pack::left);
        this->cardArrayTolist(3, cardNumList, cardTypeList);
        if((((BridgeGame*)Game::bridgeGame)->LoadDealer()+1)%4+1 == 3)
                topPack = new Pack(3, *cardNumList, *cardTypeList, true, Pack::bottom);
        else
//                topPack = new Pack(3, *cardNumList, *cardTypeList, false, Pack::bottom);
                topPack = new Pack(3, *cardNumList, *cardTypeList, true, Pack::bottom);
        this->cardArrayTolist(2, cardNumList, cardTypeList);
        if((((BridgeGame*)Game::bridgeGame)->LoadDealer()+1)%4+1 == 2)
                leftPack = new Pack(2, *cardNumList, *cardTypeList, true, Pack::right);
        else
//                leftPack = new Pack(2, *cardNumList, *cardTypeList, false, Pack::right);
                leftPack = new Pack(2, *cardNumList, *cardTypeList, true, Pack::right);
        topPack->show(this);
        leftPack->show(this);
        rightPack->show(this);
        userPack->show(this);
        this->reorderChild(userPack, 100);
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        table = new Table(winSize.width/2, winSize.height/2, winSize.width*3/4, winSize.height*3/4, userPack->getCardSize().width, userPack->getCardSize().height);
        this->addChild(table,-100);
        topPack->setTable(table);
        leftPack->setTable(table);
        rightPack->setTable(table);
        userPack->setTable(table);
        
        orderedPack[1] = userPack;
        orderedPack[2] = leftPack;
        orderedPack[3] = topPack;
        orderedPack[4] = rightPack;
        
        this->userPack->disable(true);
        pthread_create(&pid,NULL,&Game::gameOn,this);
        init = true;
        finished = false;
}

void* Game::gameOn(void* _game) {
        BridgeGame* game = (BridgeGame*)Game::bridgeGame;
        game->MainPlaying();
        game->game->finished = true;
//        CCDirector::sharedDirector()->pushScene(CCTransitionFade::transitionWithDuration(2, WinScene::scene()));
}

void Game::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
        if(userPack != 0)
                userPack->ccTouchesBegan(pTouches, event);
        if(topPack != 0 && ((BridgeGame*)this->bridgeGame)->LoadDealer() == 1)
                topPack->ccTouchesBegan(pTouches, event);
        if(finished == true) {
                CCDirector::sharedDirector()->pushScene(CCTransitionFade::transitionWithDuration(0.3, WinScene::scene()));
        }
}

void Game::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
        if(userPack != 0)
                userPack->ccTouchesMoved(pTouches, event);
        if(topPack != 0 && ((BridgeGame*)this->bridgeGame)->LoadDealer() == 1)
                topPack->ccTouchesMoved(pTouches, event);
}

void Game::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
        if(userPack != 0)
                userPack->ccTouchesEnded(pTouches, event);
        if(topPack != 0 && ((BridgeGame*)this->bridgeGame)->LoadDealer() == 1)
                topPack->ccTouchesEnded(pTouches, event);
}

void Game::cardArrayTolist(int player, list<int>* cardNumList,
                           list<Card::CardType>* cardTypeList) {
        if(cardNumList == NULL || cardTypeList == NULL) {
                cardNumList = new list<int>();
                cardTypeList = new list<Card::CardType>();
        }
        cardNumList->clear();
        cardTypeList->clear();
        BridgeGame* game  = (BridgeGame*)this->bridgeGame;
        for(int i = 1; i <= 4; i++) {
                for(int j = 1; j <= 13; j++) {
                        if( game->HandCard[player][i][j] == 1) {
                                cardNumList->push_back(Utils::platformCardToGameCard(j));
                                switch(i) {
                                        case 1:
                                                cardTypeList->push_back(Card::clubs);
                                                break;
                                        case 2:
                                                cardTypeList->push_back(Card::diamonds);
                                                break;
                                        case 3:
                                                cardTypeList->push_back(Card::hearts);
                                                break;
                                        case 4:
                                                cardTypeList->push_back(Card::spades);
                                                break;
                                                
                                }
                        }
                }
        }
        
}

string Game::getPlay() {
        userPack->inInteraction = true;
        userPack->enable(true);
        while(userPack->inInteraction == true) { // Sync.
                usleep(100);
        }
        userPack->disable(true);
        sleep(3);
        return userPack->getTarget()->toString();
}

string Game::getTeamPlay() {
        topPack->inInteraction = true;
        topPack->enable(true);
        while(topPack->inInteraction == true) { // Sync.
                usleep(100);
        }
        topPack->disable(true);
        return topPack->getTargetString();
}

void Game::postPlay(int player, string play) {
//        printf( "### Post Play: %d, %s\n", player, play.c_str());
        Pack* pack = orderedPack[player];
        pack->throwOut(play);
        sleep(3);
}

void Game::postWin(int player) {
        switch(player) {
                case 2:
                        this->table->reward(Table::left);
                        break;
                case 4:
                        this->table->reward(Table::right);
                        break;
                case 1:
                        this->table->reward(Table::bottom);
                        break;
                case 3:
                        this->table->reward(Table::top);
                        break;
        }
        
}
