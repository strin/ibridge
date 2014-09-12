//
//  Table.cpp
//  iBridge
//
//  Created by Tianlin Shi on 12/8/12.
//
//

#include "Table.h"

#include "Pack.h"
#include "Card.h"
#include "Trick.h"
#include "Game.h"
#include "BridgeGame.h"

Table::Table(int cx, int cy, int width, int height, int cardWidth, int cardHeight)
: topC(ccp(cx, cy+cardHeight/2)),
  bottomC(ccp(cx, cy)),
  leftC(ccp(cx-cardWidth/2, cy+cardHeight/4)),
  rightC(ccp(cx+cardWidth/2, cy+cardHeight/4)),
  dt(0.1){
        this->size = CCSize(width, height);
        this->center = ccp(cx,cy);
        this->inSimulation = false;
        this->order = 0;
        this->cardSize = CCSize(cardWidth, cardHeight);
}

bool Table::addCard(Card* card, Pack* pack) {
        // The orientation refers to the orientation of the pack.
        while(this->inSimulation == true) {
                usleep(100);
        }
        this->inSimulation = true;
        Pack::PackOrientation orientation = pack->getOrientation();
        
        switch (orientation) {
                case Pack::top:
                        this->cardBottom = card;
                        targetPoint = bottomC;
                        break;
                case Pack::bottom:
//                        if((((BridgeGame*)Game::bridgeGame)->LoadDealer()+1)%4+1 != 3)
//                                card->flip();
                        card->setRotation(0);
                        this->cardTop = card;
                        targetPoint = topC;
                        break;
                case Pack::left:
//                        if((((BridgeGame*)Game::bridgeGame)->LoadDealer()+1)%4+1 != 4)
//                                card->flip();
                        card->setRotation(0);
                        this->cardRight = card;
                        targetPoint = rightC;
                        break;
                case Pack::right:
//                        if((((BridgeGame*)Game::bridgeGame)->LoadDealer()+1)%4+1 != 2)
//                                card->flip();
                        card->setRotation(0);
                        this->cardLeft = card;
                        targetPoint = leftC;
                        break;
                default:
                        break;
        }
        pack->removeChild(card, false);
        while(card->getParent() != NULL) // Wait for the removal to end.
                usleep(100);
        this->addChild(card);
        this->reorderChild(card, order);
        order++;
        order = order%4;
        target = card;
        tx = target->getPositionX();
        ty = target->getPositionY();
        vx = target->velocity.x;
        vy = target->velocity.y;
        time = 0;
        oscale = target->getScale();
        this->schedule(schedule_selector(Table::simulate), 0.01);
        return true;
}

void Table::simulate(float arg) {
        // Acceleration.

        float cx = targetPoint.x;
        float cy = targetPoint.y;
        
        float dis = sqrt((tx-cx)*(tx-cx)+(ty-cy)*(ty-cy));
        
        if(dis < 0.1) {
                this->inSimulation = false;
                this->unschedule(schedule_selector(Table::simulate));
                this->getParent()->reorderChild(this, -100);
                return;
        }
        float M = 1; // Mass.
        float ita = 1.2; // Friction.
        float ax = 0-M*(tx-cx)-vx*ita;
        float ay = 0-M*(ty-cy)-vy*ita;
        
//        printf( "%lf %lf\n", vx, vy);
        vx = vx+ax*dt;
        vy = vy+ay*dt;
        tx = tx+vx*dt;
        ty = ty+vy*dt;

        target->setPosition(ccp(tx,ty));
        target->setScale(exp(0-time)*(oscale-0.5)+0.5);
        time = time+dt;
}

bool Table::reward(Location loc) {
        this->getParent()->reorderChild(this, 100);
        Trick* trick = new Trick(this);
        this->removeChild(this->cardTop, false);
        this->removeChild(this->cardBottom, false);
        this->removeChild(this->cardRight, false);
        this->removeChild(this->cardLeft, false);
        trick->addChild(this->cardTop);
        trick->addChild(this->cardLeft);
        trick->addChild(this->cardRight);
        trick->addChild(this->cardBottom);
        this->addChild(trick);
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        float cx = size.width/2;
        float cy = size.height/2;
        
        CCPoint target;
        switch (loc) {
                case Table::left:
                        target = CCPointMake(this->cardSize.height/2, cy);
                        break;
                case Table::right:
                        target = CCPointMake(size.width-this->cardSize.height/2, cy);
                        break;
                case Table::top:
                        target = CCPointMake(cx, size.height-this->cardSize.height);
                        break;
                case Table::bottom:
                        target = CCPointMake(cx, this->cardSize.height);
                        break;
        }
        trick->moveToTarget(target, 0.7);
}
