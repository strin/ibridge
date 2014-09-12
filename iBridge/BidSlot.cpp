//
//  BidSlot.cpp
//  iBridge
//
//  Created by Tianlin Shi on 1/6/13.
//
//

#include "BidSlot.h"

BidSlot::BidSlot(CCPoint head, Orientation orientation) {
        this->tail = head;
        this->orientation = orientation;
}

bool BidSlot::addBid(int number, BidGadget::GadgetType type) {
        BidGadget* gadget = new BidGadget(this->tail, number, type);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        switch (this->orientation) {
                case bottomup:
                        gadget->setPosition(ccp(this->tail.x, -100));
                        break;
                case topdown:
                        gadget->setPosition(ccp(this->tail.x, winSize.height+100));
                        break;
                case leftright:
                        gadget->setPosition(ccp(-100, this->tail.y));
                        break;
                case rightleft:
                        gadget->setPosition(ccp(winSize.width+100, this->tail.y));
                default:
                        break;
        }
        gadget->setOpacity(0);
        this->addChild(gadget);
        CCMoveTo* moveTo = CCMoveTo::actionWithDuration(0.3, this->tail);
        CCFadeTo* fadeTo = CCFadeTo::actionWithDuration(0.3, 255);
        CCSpawn* spawn = (CCSpawn*)CCSpawn::actions(moveTo, fadeTo, NULL);
        gadget->runAction(spawn);
        switch (this->orientation) {
                case bottomup:
                        this->tail = ccp(this->tail.x, this->tail.y-gadget->getContentSize().height*gadget->getScale()-spacing);
                        break;
                case topdown:
                        this->tail = ccp(this->tail.x, this->tail.y+gadget->getContentSize().height*gadget->getScale()+spacing);
                        break;
                case leftright:
                        this->tail = ccp(this->tail.x-gadget->getContentSize().width*gadget->getScale()-spacing, this->tail.y);
                        break;
                case rightleft:
                        this->tail = ccp(this->tail.x+gadget->getContentSize().width*gadget->getScale()+spacing, this->tail.y);
                        break;
                default:
                        break;
        }
}