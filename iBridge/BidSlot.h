//
//  BidSlot.h
//  iBridge
//
//  Created by Tianlin Shi on 1/6/13.
//
//

#ifndef __iBridge__BidSlot__
#define __iBridge__BidSlot__

#include <iostream>

#include "cocos2d.h"
#include "BidGadget.h"
#include "Card.h"

using namespace cocos2d;

class BidSlot : public CCLayer{
public:
        enum Orientation {topdown,bottomup,leftright,rightleft};
        BidSlot(CCPoint head, Orientation orientation);
        bool addBid(int number, BidGadget::GadgetType type);
private:
        CCPoint tail; // Tail pixel of the queue.
        Orientation orientation;
        static const int spacing = 2; // Spacing of gadgets by 15 pt.
};
#endif /* defined(__iBridge__BidSlot__) */
