#ifndef __HOMEPAGE_SCENE_H__
#define __HOMEPAGE_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

class Homepage : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void controlMusicCallback(cocos2d::Ref* pSender, CocosDenshion::SimpleAudioEngine* player);
    
    void controlEffectCallback(Ref* pSender, CocosDenshion::SimpleAudioEngine* effectGenerator);
    
    void settingsFlyoutCallback(cocos2d::Ref* pSender, cocos2d::Menu* controlledMenu);
    
    void showGamePage(CocosDenshion::SimpleAudioEngine* soundEffect);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Homepage);
    
    
};

enum EffectStatus
{
    enable,
    disable
};
enum BackgroundMusicStatus
{
    play,
    stop
};

enum SettingsStauts
{
    extended,
    warpped
};

#endif // __HOMEPAGE_SCENE_H__
