//
//  Level1.cpp
//  Physics
//
//  Created by Leon Wong on 15/6月.
//
//

#include "Level1.hpp"

#include "SimpleAudioEngine.h"

USING_NS_CC;

void Level1::setupMetaLayer(){
    const int mapW = map->getMapSize().width;
    const int mapH = map->getMapSize().height;
    
    const int tileW = map->getTileSize().width;
    const int tileH = map->getTileSize().height;
    
    this->mapSize = map->getMapSize();
    this->screenSize = Director::getInstance()->getWinSize();
    this->mapTileSize = map->getTileSize();
    
    for (int i = 0; i < mapW; ++i){
        for (int j = 0; j < mapH; ++j){
            if (meta->getTileGIDAt(Vec2(i, j)) != 0){
                Sprite* tile = Sprite::create("Blocks.png");
                //Sprite* tile = meta->getTileAt(Vec2(i, j));
                tile->setScale(this->mapTileSize.width / tile->getContentSize().width, this->mapTileSize.height / tile->getContentSize().height);
                PhysicsBody* tileBody = PhysicsBody::createBox(tile->getContentSize());
                tile->setPhysicsBody(tileBody);
                tile->setVisible(false);
                tileBody->setDynamic(false);
                tileBody->getShape(0)->setRestitution(0.0f);
                tileBody->getShape(0)->setFriction(0.5f);
                tile->setPosition(Vec2(i * tileW + 16, (mapH - j) * tileH - 16));
                this->metaLayer->addChild(tile);
            }
        }
    }
}

void Level1::keepHeroInLimitedRange(){
    if(this->heroManager->getPositionX() >= 400){
        CCLOG("Limit Hero PositionX from %f to 400", this->heroManager->getPositionX());
        float moveLen = this->heroManager->getPositionX() - 400;
        this->map->setPositionX(this->map->getPositionX() - moveLen);
        this->metaLayer->setPositionX(this->metaLayer->getPositionX() - moveLen);
        this->heroManager->getSprite()->setPositionX(this->heroManager->getPositionX() - moveLen);
    }
    
    if (this->heroManager->getPositionX() < 0)
        this->heroManager->getSprite()->setPositionX(0);

}

void Level1::update(float delta){
    this->heroManager->run();
    this->keepHeroInLimitedRange();
    CCLOG("Hero VelocityX: %f", this->heroManager->getPhysicsBody()->getVelocity().x);
}

Scene* Level1::createScene(){
    auto scene = Level1::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -400));
    
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = Level1::create();
    scene->addChild(layer);
    return scene;

}

// on "init" you need to initialize your instance
bool Level1::init(){
    // Super init first
    if ( !Scene::init() ){
        return false;
    }
    
    // First save the map in the scene
    this->map = TMXTiledMap::create("Level1.tmx");
    
    // Get the layers needed
    this->meta = this->map->getLayer("Meta");
    meta->setVisible(false);
    
    // Get enemies
    this->enemyObjectGroup = map->getObjectGroup("Enemy");
    
    // Add the map to this scene
    this->addChild(this->map);
    
    // Init Layers
    this->metaLayer = Layer::create();
    this->enemyLayer = Layer::create();
    
    // Set up meta Layer to include bodies
    this->setupMetaLayer();
    this->addChild(this->metaLayer);
    
    // Set up hero
    this->heroManager = new Hero(&(this->keyCode));
    // Get hero in the Scene
    this->heroManager->getSprite()->setPosition(Vec2(64, 256));
    this->heroManager->getSprite()->setAnchorPoint(Vec2(0, 0));
    this->addChild(this->heroManager->getSprite());
    
    
    
    this->scheduleUpdate();
    return true;
}



void Level1::setupEnemyLayer()
{
    auto enemy = map->getObjectGroup("Enemy");
    char buffer[20] ;
    std::string enemyName;
    int enemyNumber;
    
    // Add koopa to enemy layer
    
    enemyName = "Koopa";
    enemyNumber = 2;
    
    for(int i = 1;i <= enemyNumber;++i)
    {
        sprintf(buffer, "%d",i);
        
        auto koopaValue = enemy->getObject(enemyName + buffer);
        Koopa * koopa = new Koopa("Enemy_256.plist","Koopa_256.png",koopaValue.at("x").asFloat(),koopaValue.at("y").asFloat());
        
        this->enemyLayer->addChild(koopa->getSprite());
        
        koopaList.push_back(koopa);
    }
    
    
    //Add goomba to enemy layer
    
    enemyName = "Goomba";
    enemyNumber = 7;
    
    for (int i = 1; i <= enemyNumber; ++i)
    {
        sprintf(buffer, "%d",i);
        
        auto goombaValue = enemy->getObject(enemyName + buffer);
        
        Goomba * goomba = new Goomba("Enemy_256.plist","Goomba_256.png",goombaValue.at("x").asFloat(),goombaValue.at("y").asFloat());
        
        
        this->enemyLayer->addChild(goomba->getSprite());
        
        goombaList.push_back(goomba);
    }
    
    //Add piranha to enemy layer
    
    enemyName = "Piranha";
    enemyNumber = 4;
    
    for(int i = 1; i <= enemyNumber; ++i)
    {
        sprintf(buffer, "%d",i);

        auto piranhaValue = enemy->getObject(enemyName + buffer);
        
        Piranha * piranha = new Piranha("Enemy_256.plist","Piranha_open_256.png",piranhaValue.at("x").asFloat(),piranhaValue.at("y").asFloat());
        
        piranha->setMoveSpeed(0.0f);
        
        this->enemyLayer->addChild(piranha->getSprite());
        
        piranhaList.push_back(piranha);
    }
    
    //Add fallbricks to the enemy layer
    
    enemyName = "Falling1";
    
    auto fallBricksValue = enemy->getObject(enemyName);
    
    FallBricks * fallBricks = new FallBricks(fallBricksValue.at("x").asFloat(),fallBricksValue.at("y").asFloat());
    
    this->enemyLayer->addChild(fallBricks->getSprite(),0);
    
    fallBricksList.push_back(fallBricks);
    
    
    
    //Add static enemy to the enemy layer
    
    //add sting cloud
    
    enemyName = "stingCloud";
    
    auto stingCloudValue = enemy->getObject(enemyName);
    
    Cloud * stingCloud = new Cloud("normalCloud.png",stingCloudValue.at("x").asFloat(),stingCloudValue.at("y").asFloat());
    
    this->enemyLayer->addChild(stingCloud->getSprite());
    
    staticEnemyList.push_back(stingCloud);
    
    //add sting(on the ground)
    
    enemyName = "Sting";
    enemyNumber = 8;
    for(int i = 1; i <= 8;++i)
    {
        sprintf(buffer, "%d",i);
        
        auto stingValue = enemy->getObject(enemyName + buffer);
        auto stingX = stingValue.at("x").asFloat();
        auto stingY = stingValue.at("y").asFloat();
        
        Sting * sting = new Sting("Sting.png",stingX,stingY);
        
        this->enemyLayer->addChild(sting->getSprite());
        
        staticEnemyList.push_back(sting);
        
    }
    
    //add fake princess
    
    auto princessValue = enemy->getObject("fakePrincess");
    
    FakePrincess* fakePrincess = new FakePrincess("fakePrincess.png",princessValue.at("x").asFloat(),princessValue.at("y").asFloat());
    
    this->enemyLayer->addChild(fakePrincess->getSprite());
    
    staticEnemyList.push_back(fakePrincess);
}

void Level1::onEnter(){
    Scene::onEnter();
    
    // Listen the keyboard
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode KeyCode,cocos2d::Event * event){
        this->keyCode[KeyCode] = true;
        CCLOG("Press");
    };
    keyboardListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode KeyCode,cocos2d::Event * event){
        this->keyCode[KeyCode] = false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    // Listen the collisions
    auto contactListener=EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Utility::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

}
