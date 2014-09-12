//
//  Table.h
//  iBridge
//
//  Created by Tianlin Shi on 12/8/12.
//
// Bridge Table Simulator

#ifndef __iBridge__Table__
#define __iBridge__Table__

#include <iostream>

#include "cocos2d.h"

class Pack;
class Card;

using namespace cocos2d;

class Table : public CCLayer{
public:
        // Parameters.
        const CCPoint topC, leftC, bottomC, rightC;
        const float dt;
        
        enum Location {
                left, right, top, bottom
        };
        
        // Constructor
        Table(int cx, int cy, int width, int height, int cardWidth, int cardHeight);
        
        // Physical Simulation.
        void simulate(float arg);
        
        // Add a card.
        bool addCard(Card* card, Pack* pack);
        
        // Give Reward.
        bool reward(Location loc);
        
private:
        CCPoint center;
        CCSize size;
        CCSize cardSize;
        
        Card* cardTop, *cardLeft, *cardBottom, *cardRight;
        Card* target; // The card in simulation.
        CCPoint targetPoint;
        float tx, ty; // The exact position of the target.
        float time, oscale;
        float vx, vy; // The exact velocity of the target.
        
        bool inSimulation; // During the simulation progress.
        int order; // order of card: 0~3
};

#endif /* defined(__iBridge__Table__) */
