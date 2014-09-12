//
//  Card.cpp
//  iBridge
//
//  Created by Tianlin Shi on 11/28/12.
//  Class Card is a generalized object category of bridge cards on the table.
//  The Card Inherits CCSprite, which means it is a managable game object.
//
//

#include "Card.h"

#include "Pack.h"

Card::Card() {
        this->enabled = true;
        this->visible = true;
        this->inTheHand = true;
        this->velocity = ccp(0,0);
}

Card::Card(Pack* pack, CardType cardType, int cardNumber) {
        this->cardType = cardType;
        this->cardNumber = cardNumber;
        this->enabled = true;
        this->visible = true;
        this->handsOn = false;
        this->inTheHand = true;
        this->refreshSprite();
        this->velocity = ccp(0,0);
        this->pack = pack;
        this->setColor(ccc3(255,255,255));
}

bool Card::refreshSprite() {
        // Load texture.
        if(this->visible == true) {
                switch(this->cardType) {
                        case hearts:
                                this->face = CCTextureCache::sharedTextureCache()->addImage("hearts.png");
                                break;
                        case spades:
                                this->face = CCTextureCache::sharedTextureCache()->addImage("spades.png");
                                break;
                        case diamonds:
                                this->face = CCTextureCache::sharedTextureCache()->addImage("diamonds.png");
                                break;
                        case clubs:
                                this->face = CCTextureCache::sharedTextureCache()->addImage("clubs.png");
                                break;
                        default:
                                throw new CardException("Failed to create Hearts: Unknown card type!");
                }
        }else{
                this->face = CCTextureCache::sharedTextureCache()->addImage("spades.png");
        }
        // Crop image to get bitmaps.
        CCSpriteFrame* frame = NULL;
        if(this->visible == true) {
                switch(this->cardNumber) {
                        case 1:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(0,0,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 2:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(283,0,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 3:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(565,0,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 4:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(845,0,250        ,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 5:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(1125,0,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 6:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(0,370,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 7:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(283,370,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 8:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(565,370,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 9:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(845,370,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 10:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(1130,370,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 11:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(0,740,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 12:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(283,740,250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 13:
                                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(565,740, 250,350));
                                this->initWithSpriteFrame(frame);
                                break;
                        case 14:
                        default:
                                throw new CardException("Failed to create Hearts: Unknown card number!");
                }
        }else{
                frame = CCSpriteFrame::frameWithTexture(this->face, CCRectMake(1130,740,250,350));
                this->initWithSpriteFrame(frame);

        }
        this->shadow = NULL;
        return true;
}

Card* Card::fertilizeCard(Pack* pack, CardType cardType, int cardNumber) {
        Card* card = new Card(pack, cardType, cardNumber);
        return card;
}

void Card::flip() {
        this->visible = !this->visible;
        this->refreshSprite();
}

void Card::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
        if(enabled == false) return;
        CCSetIterator it;
        for(it = pTouches->begin(); it != pTouches->end(); it++) {
                CCTouch* touch = (CCTouch*)(*it);
                CCPoint point = touch->getLocationInView();
                point = CCDirector::sharedDirector()->convertToGL(point);
                if(this->containsTouchPoint(point)) {
                        this->lastTouchPoint = point;
                        this->lastTouchTime = clock();
                        this->prevPosition = this->getPosition();
                        this->setHandsOn(true);
                }
        }
}

void Card::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
        if(enabled == false) return;
        CCSetIterator it;
        if( handsOn == false) return;
        for(it = pTouches->begin(); it != pTouches->end(); it++) {
                CCTouch* touch = (CCTouch*)(*it);
                CCPoint point = touch->getLocationInView();
                point = CCDirector::sharedDirector()->convertToGL(point);
                int lastX = lastTouchPoint.x;
                int lastY = lastTouchPoint.y;
                int x = point.x;
                int y = point.y;
                int px = this->getPosition().x;
                int py = this->getPosition().y;
                this->setPosition(CCPoint(px+x-lastX, py+y-lastY));
                clock_t now = clock();
                float vx = (double)(x-lastX)/(double)(now-lastTouchTime)*(double)CLOCKS_PER_SEC;
                float vy = (double)(y-lastY)/(double)(now-lastTouchTime)*(double)CLOCKS_PER_SEC;
                if(vx > 100) vx = 100;
                if(vx < -100) vx = -100;
                if(vy > 100) vy = 100;
                if(vy < -100) vy = -100;
                this->velocity = ccp(vx, vy);
                this->lastTouchTime = now;
                this->lastTouchPoint = point;
        }
}

void Card::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
        if(enabled == false) return;
        this->setHandsOn(false);
}

CCRect Card::rect()
{
        CCSize size = this->getContentSize();
        float scale = this->getScale();
        CCPoint pos = getPosition();
        
        return CCRectMake(pos.x - size.width*scale / 2, pos.y - size.height*scale / 2, size.width*scale, size.height*scale);
}


bool Card::getHandsOn() {
        return this->handsOn;
}

void Card::setHandsOn(int handsOn) {
        if(handsOn == true) {
                if(this->shadow == NULL) {
                        this->shadow = CCSprite::spriteWithFile("shadow.png");
                        this->shadow->setOpacity(0);
                        this->addChild(shadow, -1);
                }
                CCTintTo* tintTo = CCTintTo::actionWithDuration(0.3, 240, 240, 240);
                this->runAction(tintTo);
                this->shadow->setScale((double)this->getContentSize().height/(double)this->shadow->getContentSize().height);
                CCFadeTo* fadeTo = CCFadeTo::actionWithDuration(0.3, 255);
                this->shadow->setPosition(ccp(this->getContentSize().width*0.5,this->getContentSize().height/2));
                this->shadow->runAction(fadeTo);
        }else{
                CCTintTo* tintTo = CCTintTo::actionWithDuration(0.3, 255, 255, 255);
                this->runAction(tintTo);
                this->shadow->setScale((double)this->getContentSize().height/(double)this->shadow->getContentSize().height);
                CCFadeTo* fadeTo = CCFadeTo::actionWithDuration(0.3, 0);
                this->shadow->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
                this->shadow->runAction(fadeTo);
        }
        this->handsOn = handsOn;
}

bool Card::containsTouchPoint(CCPoint point) {
        double x = this->getPosition().x;
        double y = this->getPosition().y;
        double w = this->getContentSize().width*this->getScale();
        double h = this->getContentSize().height*this->getScale();
        double diag = sqrt((w/2)*(w/2)+(h/2)*(h/2));
        float rotation = 0-this->getRotation();
        // x1 the right-top corner, x1 ... x4 are ordered clockwise.
        CCPoint x1 = ccp(x+diag*cos(CC_DEGREES_TO_RADIANS(45+rotation)), y+diag*sin(CC_DEGREES_TO_RADIANS(45+rotation)));
        CCPoint x4 = ccp(x+diag*cos(CC_DEGREES_TO_RADIANS(135+rotation)), y+diag*sin(CC_DEGREES_TO_RADIANS(135+rotation)));
        CCPoint x3 = ccp(x+diag*cos(CC_DEGREES_TO_RADIANS(-135+rotation)), y+diag*sin(CC_DEGREES_TO_RADIANS(-135+rotation)));
        CCPoint x2 = ccp(x+diag*cos(CC_DEGREES_TO_RADIANS(-45+rotation)), y+diag*sin(CC_DEGREES_TO_RADIANS(-45+rotation)));
        CCPoint norm1 = ccp(x1.x-x2.x,x1.y-x2.y);
        double temp = sqrt(norm1.x*norm1.x+norm1.y*norm1.y);
        norm1.setPoint(norm1.x/temp, norm1.y/temp);
        norm1.setPoint(norm1.y, -norm1.x);
        CCPoint norm2 = ccp(x4.x-x3.x,x4.y-x3.y);
        temp = sqrt(norm2.x*norm2.x+norm2.y*norm2.y);
        norm2.setPoint(norm2.x/temp, norm2.y/temp);
        norm2.setPoint(norm2.y, -norm2.x);
        CCPoint norm3 = ccp(x1.x-x4.x,x1.y-x4.y);
        temp = sqrt(norm3.x*norm3.x+norm3.y*norm3.y);
        norm3.setPoint(norm3.x/temp, norm3.y/temp);
        norm3.setPoint(norm3.y, -norm3.x);
        CCPoint norm4 = ccp(x2.x-x3.x,x2.y-x3.y);
        temp = sqrt(norm4.x*norm4.x+norm4.y*norm4.y);
        norm4.setPoint(norm4.x/temp, norm4.y/temp);
        norm4.setPoint(norm4.y, -norm4.x);
        double c1 = norm1.x*x1.x+norm1.y*x1.y;
        double c2 = norm2.x*x3.x+norm2.y*x3.y;
        double c3 = norm3.x*x1.x+norm3.y*x1.y;
        double c4 = norm4.x*x2.x+norm4.y*x2.y;
        double c1p = norm1.x*point.x+norm1.y*point.y;
        double c2p = norm2.x*point.x+norm2.y*point.y;
        double c3p = norm3.x*point.x+norm3.y*point.y;
        double c4p = norm4.x*point.x+norm4.y*point.y;
        if((c1p-c1)*(c2p-c2) <= 0 && (c3p-c3)*(c4p-c4) <= 0) {
                return true;
        }else return false;
}

void Card::throwOut(CCPoint touch) {
        if(this->inTheHand == false) return;
        prevRotate = this->getRotation();
        Utils::animateRotationAroundTouchPoint(this, 0-this->getRotation(), 0.01);
        this->inTheHand = false;
}

void Card::throwIn(CCPoint touch) {
        if(this->inTheHand == true) return;
        Utils::animateRotationAroundTouchPoint(this, prevRotate, 0.01);
        this->prevRotate = 0;
        this->inTheHand = true;
}

void Card::throwOnTable() {
        this->onTheTable = true;
        this->inTheHand = false;
}
void Card::rotateAroundTouch(float arg) {
        Utils::rotateAroundPoint(sprite,  this->lastTouchPoint, dangle);
        ang += dangle;
        t += mesh;
        if( t > time)
                this->unschedule(schedule_selector(Card::rotateAroundTouch));
}

void Card::recoverPosition() {
        CCMoveBy* moveby = CCMoveBy::actionWithDuration(0.5, ccp(this->prevPosition.x-this->getPosition().x, this->prevPosition.y-this->getPosition().y));
        this->prevPosition = ccp(0,0);
        this->runAction(moveby);
}

void Card::autoThrowOut() {
        if(this->pack->getOrientation() == Pack::right) {
                this->velocity = ccp(100,0);
        }else if(this->pack->getOrientation() == Pack::left) {
                this->velocity = ccp(-100,0);
        }else if(this->pack->getOrientation() == Pack::bottom) {
                this->velocity = ccp(0,-100);
        }
        this->table->addCard(this, this->pack);
}

void Card::disable(bool tint) {
        enabled = false;
        if(tint) {
                CCTintTo* tintTo = CCTintTo::actionWithDuration(0.4, 200, 200, 200);
                this->runAction(tintTo);
                usleep(100);
        }
}

void Card::enable(bool tint) {
        enabled = true;
        if(tint) {
                CCTintTo* tintTo = CCTintTo::actionWithDuration(0.4, 255, 255, 255);
                this->runAction(tintTo);
                usleep(100);
        }
}

string Card::toString() {
        string res = "";
        if(cardNumber == 1) {
                res.push_back('A');
        }else if(cardNumber == 12) {
                res.push_back('Q');
        }else if(cardNumber == 11) {
                res.push_back('J');
        }else if(cardNumber == 10) {
                res.push_back('X');
        }else if(cardNumber == 13) {
                res.push_back('K');
        }else{
                res.push_back('0'+this->cardNumber);
        }
        switch(cardType) {
                case Card::clubs:
                        res.push_back('C');
                        break;
                case Card::diamonds:
                        res.push_back('D');
                        break;
                case Card::spades:
                        res.push_back('S');
                        break;
                case Card::hearts:
                        res.push_back('H');
                        break;
        }
        return res;
}