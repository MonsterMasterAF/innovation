//
//  GameScene.hpp
//  pionner
//
//  Created by Andrew on 2017/1/9.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "../HomepageScene.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(CocosDenshion::SimpleAudioEngine* soundEffect);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_h */
