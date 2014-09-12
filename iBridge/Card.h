//
//  Card.h
//  iBridge
//
//  Created by Tianlin Shi on 11/28/12.
//
//

#ifndef __iBridge__Card__
#define __iBridge__Card__

#include <iostream>
#include <cocos2d.h>
#include "CCSprite.h"
#include "CCDirector.h"

#include "CardException.h"
#include "Utils.h"
#include "Table.h"
#include "time.h"
#include <string>

using namespace cocos2d;
using namespace std;

class Pack;

class Card : public CCSprite, public CCStandardTouchDelegate
{
public:
        static const double cardRatio = 5.0/7.0; // Ratio Width by Height.
        
        enum CardType {clubs,diamonds,hearts,spades};
        
        // Internal Properties.
        bool visible; // Whether the card faces upward.
        bool enabled; // Whether the card accepts user input.
        bool inTheHand; // Whether the card is in our hand.
        bool onTheTable;
        CardType cardType; //
        int cardNumber; // The number on the card.
        Table* table; // The table we are playing on.
        
        // Physical Properties.
        CCPoint velocity;
        
        // Constructor.
        Card(); // Default Constructor.
        Card(Pack* pack, CardType cardType, int CardNumber);
        
        void flip(); // Flip the card.
        void throwOut(CCPoint touch); // Throw the card out of hand.
        void throwIn(CCPoint touch); // Throw in the card.
        void autoThrowOut(); // Computer! Throw the card out of hand.
        
        void recoverPosition(); // Recover the position in hand.
        
        void throwOnTable();
        static Card* fertilizeCard(Pack* pack, CardType cardType, int CardNumber); // The Factory Module.
        
        CCRect rect(); // Get rect of the card.
        bool containsTouchPoint(CCPoint point); // Test if the touch is in region.
        
        // Handle Touch Events.
        CCPoint lastTouchPoint;
        clock_t lastTouchTime;
        virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
        virtual void ccTouchesMoved(CCSet* pTouches, CCEvent *event);
        virtual void ccTouchesEnded(CCSet* pTouches, CCEvent *event);
        
        // Geometry.
        double mesh, t, time;
        double dangle, ang;
        void rotateAroundTouch(float);
        CCSprite* sprite;
        
        // State.
        bool getHandsOn();
        void setHandsOn(int handsOn);
        void disable(bool tint);
        void enable(bool tint);
        
        // Get String Abstraction.
        string toString();
private:
        bool refreshSprite();
        CCTexture2D* face, *bottom; // The Image Texture.
        CCSprite* shadow; // The shadow of this sprite.
        bool handsOn; // Indicator of whether the hands are on.
        float prevRotate; // Record prev rotation angle.
        CCPoint prevPosition;
        
        Pack* pack;
};

#endif /* defined(__iBridge__Card__) */
