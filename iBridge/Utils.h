//
//  Utils.h
//  iBridge
//
//  Created by Tianlin Shi on 12/5/12.
//
//

#ifndef __iBridge__Utils__
#define __iBridge__Utils__

#include <iostream>
#include <cocos2d.h>
#include "CCSprite.h"
#include "CCDirector.h"


using namespace cocos2d;

class Utils {
public:
        static void rotateAroundPoint( CCSprite* sprite, CCPoint rotationPoint, float angle);
        static void animateRotationAroundTouchPoint( CCSprite* sprite, float angle, float time);
        static CCFiniteTimeAction* animateRotationAroundPoint( CCSprite* sprite, CCPoint rotationPoint, float angle, float time);
        
        static int platformCardToGameCard(int number);
        static int gameCardToplatformCard(int number);
};
#endif /* defined(__iBridge__Utils__) */
