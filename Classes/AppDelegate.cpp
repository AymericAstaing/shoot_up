#include "AppDelegate.h"
#include "GameScene.h"
#include "UserLocalStore.h"
#include "ShootUp.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2160, 1080);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("SimpleGame", Rect(0,0, 480, 320), 1.0);
        director->setOpenGLView(glview);
    }
    Size designSize = Size(1920, 780);
    Size resourceSize = Size(2160, 1080);
    director->setContentScaleFactor(resourceSize.height / designSize.height);
    director->getOpenGLView()->setDesignResolutionSize(
            designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);
    register_all_packages();

    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("spritesheet/block_color.plist");
    spritecache->addSpriteFramesWithFile("spritesheet/continue_animation.plist");
    spritecache->addSpriteFramesWithFile("spritesheet/bullets.plist");
    spritecache->addSpriteFramesWithFile("spritesheet/bonus_power.plist");
    spritecache->addSpriteFramesWithFile("spritesheet/bonus_speed.plist");
    spritecache->addSpriteFramesWithFile("spritesheet/bonus_bullet.plist");
    UserLocalStore::store_achievement_variable(FROM_SHOP, 0);
    auto scene = GameScene::createScene();
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}
// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
