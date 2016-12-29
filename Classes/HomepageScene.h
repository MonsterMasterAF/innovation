#ifndef __HOMEPAGE_SCENE_H__
#define __HOMEPAGE_SCENE_H__

#include "cocos2d.h"

class Homepage : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void controlMusicCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Homepage);
    
    
};

enum BackgroundMusicStatus
{
    play,
    stop
};

#endif // __HOMEPAGE_SCENE_H__
