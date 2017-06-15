//
//  FallBricks.cpp
//  MyCppGame
//
//  Created by 梁永潮 on 2017/6/7.
//
//

#include "FallBricks.hpp"

FallBricks::FallBricks(int x,int y):trigger(false),fallSpeed(100.0f),outScene(false)
{
    sprite = cocos2d::Sprite::create("Level1Falling1.png");
    width = sprite->getContentSize().width;
    height = sprite->getContentSize().height;
    sprite->setAnchorPoint(cocos2d::Point(0,0));
    sprite->setPositionX(x);
    sprite->setPositionY(y);
    CCLOG("%d %d",x,y);
    body = cocos2d::PhysicsBody::createBox(this->getSprite()->getContentSize());
    this->getSprite()->setPhysicsBody(body);
    this->getSprite()->getPhysicsBody()->setDynamic(false);
    
    
    
    
    
}

void FallBricks::fall()
{
    if(!trigger)
    {
        return;
    }
    
    //here need to be adjusted when the map's position is changed
    
    sprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0,-fallSpeed));
    if(sprite->getPositionY() < 0)
    {
        outScene = true;
    }
    
    
}

void FallBricks::isAbove(float x,float y)
{
    auto spriteX = sprite->getPositionX();
    auto spriteY = sprite->getPositionY();
    if(x >= spriteX&&x <= spriteX + width)
    {
        trigger = true;
        if(y > spriteY)
        {
            above = true;
        }
        else
        {
            above = false;
        }
    }
    
}

void FallBricks::run(float x)
{
    if(x>getSprite()->getPositionX() && x < getSprite()->getPositionX() + getSprite()->getContentSize().width)
    {
        if(!trigger)
        {
            trigger = true;
            getSprite()->getPhysicsBody()->setDynamic(true);
        }
    }
    fall();
}
