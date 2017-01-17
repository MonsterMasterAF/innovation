//
//  GameScene.cpp
//  pionner
//
//  Created by Andrew on 2017/1/9.
//
//

#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;
SimpleAudioEngine* effect;

Scene* GameScene::createScene(SimpleAudioEngine* soundEffect)
{
    effect = soundEffect;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SimpleAudioEngine* soundEffect = effect;
     
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto block = Sprite::create("a.jpg");
    block->setPosition(Vec2(origin.x + visibleSize.width/2 - block->getContentSize().width/2 ,
                                 origin.y + visibleSize.height/2 - block->getContentSize().height/2));
    this->addChild(block, 1);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [soundEffect,block](Touch* touch, Event* event)
    {
        soundEffect->playEffect("soundEffect.mp3");
        auto moveby = MoveBy::create(0.5, Vec2(block->getContentSize().width,0));
        
        block->runAction(moveby);
        return  true;
    };
    
    listener1->onTouchEnded = [soundEffect](Touch* touch, Event* event)
    {
        soundEffect->stopAllEffects();
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    return true;
}

