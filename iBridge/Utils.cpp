//
//  Utils.cpp
//  iBridge
//
//  Created by Tianlin Shi on 12/5/12.
//
//

#include "Utils.h"
#include "Card.h"

void Utils::rotateAroundPoint( CCSprite* sprite, CCPoint rotationPoint, float angle) {
        float x = cos(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().x-rotationPoint.x) - sin(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().y-rotationPoint.y) + rotationPoint.x;
        float y = sin(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().x-rotationPoint.x) + cos(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().y-rotationPoint.y) + rotationPoint.y;
        angle = angle+sprite->getRotation();
        sprite->setPosition(ccp(x, y));
        sprite->setRotation(angle);
}

CCFiniteTimeAction* Utils::animateRotationAroundPoint( CCSprite* sprite, CCPoint rotationPoint, float angle, float time) {
        float x = cos(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().x-rotationPoint.x) - sin(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().y-rotationPoint.y) + rotationPoint.x;
        float y = sin(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().x-rotationPoint.x) + cos(CC_DEGREES_TO_RADIANS(-angle)) * (sprite->getPosition().y-rotationPoint.y) + rotationPoint.y;
        // Set up waypoints.
        const int meshSize = 100;
        CCArray* array = CCArray::arrayWithCapacity(meshSize);
        float prevX = sprite->getPosition().x, prevY = sprite->getPosition().y;
        for(int i = 0; i <= meshSize; i++) {
                float wayAngle = angle/(double)meshSize*(double)i;
                float wayX = cos(CC_DEGREES_TO_RADIANS(-wayAngle)) * (sprite->getPosition().x-rotationPoint.x) - sin(CC_DEGREES_TO_RADIANS(-wayAngle)) * (sprite->getPosition().y-rotationPoint.y) + rotationPoint.x;
                float wayY = sin(CC_DEGREES_TO_RADIANS(-wayAngle)) * (sprite->getPosition().x-rotationPoint.x) + cos(CC_DEGREES_TO_RADIANS(-wayAngle)) * (sprite->getPosition().y-rotationPoint.y) + rotationPoint.y;
                array->addObject(CCMoveBy::actionWithDuration(time/(double)meshSize, ccp(wayX-prevX,wayY-prevY)));
                prevX = wayX;
                prevY = wayY;
        }
        CCFiniteTimeAction* moveActions = CCSequence::actionWithArray(array);
        CCRotateBy* rotateActions = CCRotateBy::actionWithDuration(time, angle);
        return CCSpawn::actions(moveActions, rotateActions, NULL);
}

void Utils::animateRotationAroundTouchPoint( CCSprite* sprite, float angle, float time) {
        Card* card = (Card*)sprite;
        card->mesh = 0.001;
        card->t = 0;
        card->dangle = angle/(time/card->mesh);
        card->ang = 0;
        card->sprite = sprite;
        card->time = time;
        card->schedule(schedule_selector(Card::rotateAroundTouch), card->mesh);
}

int Utils::platformCardToGameCard(int number) {
        switch(number)
        {
                case 1:
                        return 2;
                case 2:
                        return 3;
                case 3:
                        return 4;
                case 4:
                        return 5;
                case 5:
                        return 6;
                case 6:
                        return 7;
                case 7:
                        return 8;
                case 8:
                        return 9;
                case 9:
                        return 10;
                case 10:
                        return 11;
                case 11:
                        return 12;
                case 12:
                        return 13;
                case 13:
                        return 1;
                default:
                        return 0;
        }
}

int Utils::gameCardToplatformCard(int number) {
        switch(number)
        {
                case 2:
                        return 1;
                case 3:
                        return 2;
                case 4:
                        return 3;
                case 5:
                        return 4;
                case 6:
                        return 5;
                case 7:
                        return 6;
                case 8:
                        return 7;
                case 9:
                        return 8;
                case 10:
                        return 9;
                case 11:
                        return 10;
                case 12:
                        return 11;
                case 13:
                        return 12;
                case 1:
                        return 13;
                default:
                        return 0;
        }
}