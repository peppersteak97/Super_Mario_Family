//
//  Enemy.hpp
//  SuperMarioFamily
//
//  Created by 梁永潮 on 2017/5/30.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Utility.h"
#include "cocos2d.h"

class Enemy
{
    
private:
    bool trigger;
    Direction dir;
    cocos2d::Sprite * sprite;
    cocos2d::PhysicsBody * body;
    bool isDead;
    float moveSpeed;
    float jumpSpeed;
    float fallSpeed;
     bool fall;
    float height;
    float width;
    bool isDeleted;
public:
    enum KIND
    {
        GOOMBA,
        KOOPA,
        KOOPADEAD,
        PIRANHA,
        REDMUSHROOM,
        TOXICMUSHROOM
        
        
    };
    
    
    
    
    bool normalSpeed;
    void deleteFromNode(){isDeleted = true;}
    bool deleted(){return isDeleted;}
    void dead(bool isDead){this->isDead = isDead;}
    cocos2d::Sprite * getSprite(){return sprite;}
    void setMoveSpeed(float speed){moveSpeed = speed;}
    void setFallSpeed(float speed){fallSpeed = speed;}
    float getWidth(){return width;}
    float getHeight(){return height;}
    
    
   
    int moveTime;
    int setEnemyX;
    int setEnemyY;
    KIND kind;
    
    cocos2d::Label * label;
    
    
    Enemy(const char *frameName,const char * filename,int x,int y,KIND kind);
    ~Enemy(){};
    bool move(cocos2d::TMXTiledMap * tmxmap);
    void update(cocos2d::TMXTiledMap * tmxmap);
    bool gravity(cocos2d::TMXTiledMap * tmxmap);
    void judge(cocos2d::TMXTiledMap * tmxmap,float x,float y);
    void setDirection(Direction dir){this->dir = dir;}
    
    bool getTrigger(){return trigger;}
    
    
    
};

#endif /* Enemy_hpp */
