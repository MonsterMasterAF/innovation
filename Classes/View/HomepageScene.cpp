#include "HomepageScene.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace rapidjson;
using namespace ui;

//Status Control Global Variable
EffectStatus EFFECTSTATUS = EffectStatus::enable;
BackgroundMusicStatus BGMUSICSTATUS = BackgroundMusicStatus::play;
SettingsStauts SETTINGSTATUS = SettingsStauts::warpped;
StringBuffer read();

Scene* Homepage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Homepage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Homepage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // menu items
    
    Vector<MenuItem*> MenuItems;
    auto soundOnMenuItem = MenuItemImage::create("soundOnEffect.png", "soundOnEffect.png");
    //auto soundOnMenuItem = MenuItemImage::create("a.jpg", "a.jpg");
    auto soundOffMenuItem = MenuItemImage::create("soundOffEffect.png","soundOffEffect.png");
    auto musicOnMenuItem = MenuItemImage::create("musicOnEffect.png", "musicOnEffect.png");
    auto musicOffMenuItem = MenuItemImage::create("musicOffEffect.png", "musicOffEffect.png");
    auto settingsMenuItem = MenuItemImage::create("settings.png", "setting.png");
    auto settingsWrapMenuItem = MenuItemImage::create("settings.png", "settings.png");
    
    auto backgroundMusic = SimpleAudioEngine::getInstance();
    auto soundEffect = SimpleAudioEngine::getInstance();
    backgroundMusic->playBackgroundMusic("music.mp3", true);
    soundEffect->preloadEffect("soundEffect.mp3");
    //soundEffect->playEffect("soundEffect.mp3");
    
    auto backgroundMusicToggleMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Homepage::controlMusicCallback, this, soundEffect),soundOnMenuItem, soundOffMenuItem, NULL);
    
    backgroundMusicToggleMenu->setScale(0.5);
    backgroundMusicToggleMenu->setPosition(Vec2(origin.x + settingsMenuItem->getContentSize().width/2 + 5 + backgroundMusicToggleMenu->getContentSize().width/4 , origin.y + backgroundMusicToggleMenu->getContentSize().height/4+5));
    
    auto effectToggleMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Homepage::controlEffectCallback, this, backgroundMusic), musicOnMenuItem,musicOffMenuItem, NULL);
    
    effectToggleMenu->setScale(0.5);
    effectToggleMenu->setPosition(Vec2(origin.x + settingsMenuItem->getContentSize().width/2 + 5 + effectToggleMenu->getContentSize().width/2 + musicOnMenuItem->getContentSize().width/4, origin.y+effectToggleMenu->getContentSize().height/4+5));
    
    MenuItems.pushBack(backgroundMusicToggleMenu);
    MenuItems.pushBack(effectToggleMenu);
    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // create menu, it's an autorelease object
    
    auto settingsToggleMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Homepage::settingsFlyoutCallback, this, menu), settingsMenuItem, settingsWrapMenuItem, NULL);
    
    settingsToggleMenu->setScale(0.5);
    settingsToggleMenu->setPosition(Vec2(origin.x + settingsToggleMenu->getContentSize().width/4 + 5, origin.y + settingsToggleMenu->getContentSize().height/4 + 5));
    auto settingMenu = Menu::create(settingsToggleMenu, NULL);
    settingMenu->setPosition(Vec2::ZERO);
    this->addChild(settingMenu, 1);
    
    //auto backDrop = Sprite::create("20160824021133607.jpg");
    //backDrop->setScale(0.1);
    //auto backDrop = Sprite::create("a.jpg");
    //backDrop->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(backDrop, 0);
    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Tian Tian Ai Xiao Chu", "fonts/Marker Felt.ttf", 48);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    menu->setVisible(false);
    Sprite* test1 = Sprite::create("a.jpg");
    test1->setPosition(Vec2(origin.x+200, origin.y+400));
    this->addChild(test1,2);
    //Sprite* test2 = Sprite::create("a.jpg");
    //test2->setColor(Color3B::GREEN);
    //test2->setPosition(Vec2(origin.x+200+test1->getContentSize().width, origin.y+400));
    //this->addChild(test2,2);
    auto startButton = Button::create();
    startButton->loadTextures("startMenu.png", "startMenu.png");
    startButton->setVisible(true);
    startButton->setTitleText("Start");
    startButton->setTouchEnabled(true);
    startButton->setPosition(Vec2(label->getPositionX(),label->getPositionY()-startButton->getContentSize().width-20));
    //startButton->setPosition(Vec2(300,300));
    this->addChild(startButton,10);
    startButton->addClickEventListener(CC_CALLBACK_0(Homepage::showGamePage, this, soundEffect));
    
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [soundEffect,test1](Touch* touch, Event* event)
    {
        soundEffect->playEffect("soundEffect.mp3");
        auto moveby = MoveBy::create(0.5, Vec2(test1->getContentSize().width,0));
        
        test1->runAction(moveby);
        return  true;
    };
    
    listener1->onTouchEnded = [soundEffect](Touch* touch, Event* event)
    {
        soundEffect->stopAllEffects();
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    //read();
    
    
    
    
    return true;
}

void Homepage::controlMusicCallback(Ref* pSender, SimpleAudioEngine* player)
{
    if(BGMUSICSTATUS == BackgroundMusicStatus::stop)
    {
        player->resumeBackgroundMusic();
        BGMUSICSTATUS = BackgroundMusicStatus::play;
    }
    else if(BGMUSICSTATUS == BackgroundMusicStatus::play)
    {
        player->pauseBackgroundMusic();
        BGMUSICSTATUS = BackgroundMusicStatus::stop;
    }
}

void Homepage::controlEffectCallback(Ref* pSender, SimpleAudioEngine* effectGenerator)
{
    if(EFFECTSTATUS == EffectStatus::enable)
    {
        effectGenerator->setEffectsVolume(0);
        EFFECTSTATUS = EffectStatus::disable;
    }
    else if(EFFECTSTATUS == EffectStatus::disable)
    {
        effectGenerator->setEffectsVolume(100);
        EFFECTSTATUS = EffectStatus::enable;
    }
}

void Homepage::settingsFlyoutCallback(Ref* pSender, Menu* controlledMenu)
{
    
    if(SETTINGSTATUS == SettingsStauts::warpped)
    {
        controlledMenu->setEnabled(true);
        controlledMenu->setVisible(true);
        SETTINGSTATUS = SettingsStauts::extended;
    }
    else if(SETTINGSTATUS == SettingsStauts::extended)
    {
        controlledMenu->setEnabled(false);
        controlledMenu->setVisible(false);
        SETTINGSTATUS = SettingsStauts::warpped;
    }
}


void Homepage::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
}

StringBuffer read()
{
    rapidjson::Document readoc;
    std::string loadstr;
    ssize_t size = 0;
    auto fileName = "JSONString.json";
    auto path = FileUtils::getInstance()->isFileExist(fileName);
    //path.append("JSONString.json");
    //unsigned char* titlech = FileUtils::getInstance()->getFileData(path, "r", &size);
}

void Homepage::showGamePage(SimpleAudioEngine* soundEffect)
{
    auto director = Director::getInstance();
    auto gameScene = GameScene::createScene(soundEffect);
    director->replaceScene(gameScene);
}
