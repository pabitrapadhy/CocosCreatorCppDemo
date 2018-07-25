#include "AppDelegate.h"
#include "CustomScene.h"
#include "Globals.h"
#include "CocosCustomMacros.h"
#include "CustomLayer.h"
#include "PageViewItem.hpp"

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

static cocos2d::Size designResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size smallResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size largeResolutionSize = cocos2d::Size(960, 640);

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

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("CocosCreatorCppDemo", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("CocosCreatorCppDemo");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // // set FPS. the default value is 1.0/60 if you don't call this
    // director->setAnimationInterval(1.0f / 60);

    // // Set the design resolution
    // glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    // auto frameSize = glview->getFrameSize();
    // // if the frame's height is larger than the height of medium size.
    // if (frameSize.height > mediumResolutionSize.height)
    // {        
    //     director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    // }
    // // if the frame's height is larger than the height of small size.
    // else if (frameSize.height > smallResolutionSize.height)
    // {        
    //     director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    // }
    // // if the frame's height is smaller than the height of medium size.
    // else
    // {        
    //     director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    // }

    // START: EXPERIMENTAL
    //////////////////////////////////////////////////////////////////////////////////////////
    Application::Platform platform = Application::getInstance()->getTargetPlatform();
    Size screenSize = director->getOpenGLView()->getFrameSize();
    
    std::vector<std::string> resDirOrders;
    std::string pathPrefix = "";
    
    float width_height_ratio = screenSize.width/screenSize.height;
    
    if(width_height_ratio == 4.0f/3) {
        Globals::currentAspectRatio = ASPECT_RATIO_4_3;
    } else if (width_height_ratio == 16.0f/10) {
        Globals::currentAspectRatio = ASPECT_RATIO_16_10;
    } else if (width_height_ratio == 16.0f/9) {
        Globals::currentAspectRatio = ASPECT_RATIO_16_9;
    } else { // if (width_height_ratio == 1024.f/600) {
        Globals::currentAspectRatio = ASPECT_RATIO_OTHER;
    }
    

    // 1. CONTENT SCALE FACTOR
    if (platform == Application::Platform::OS_MAC || platform == Application::Platform::OS_IPHONE || platform == Application::Platform::OS_IPAD) 
    {
        if (screenSize.height > 768) {
            director->setContentScaleFactor(2.0);
            resDirOrders.push_back(pathPrefix + "Resources_HD");
            resDirOrders.push_back(pathPrefix + "Resources_SD");
            resDirOrders.push_back(pathPrefix + "Resources_LD");
        }
        else if (screenSize.height >= 640)
        {
            director->setContentScaleFactor(1.0);
            resDirOrders.push_back(pathPrefix + "Resources_SD");
            resDirOrders.push_back(pathPrefix + "Resources_HD");
        }
        else
        {
            director->setContentScaleFactor(0.5);
            resDirOrders.push_back(pathPrefix + "Resources_LD");
        }
    }
    else if (platform == Application::Platform::OS_ANDROID) {
        // removing hd for now
        if (screenSize.height > 960)
        {
            director->setContentScaleFactor(2.0);
            if (!FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_HD/hud.pvr.ccz")) 
            {
                director->setContentScaleFactor(1.0);
                if (!FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_SD/hud.pvr.ccz")) 
                {
                    director->setContentScaleFactor(0.5);
                }
            }
            resDirOrders.push_back(pathPrefix + "Resources_HD");
            resDirOrders.push_back(pathPrefix + "Resources_SD");
            resDirOrders.push_back(pathPrefix + "Resources_LD");
        }
        else if (screenSize.height > 400)
        {
            director->setContentScaleFactor(1.0);
            if (!FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_SD/hud.pvr.ccz")) 
            {
                if (FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_HD/hud.pvr.ccz")) 
                {
                    director->setContentScaleFactor(2);
                } 
                else if (FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_LD/hud.pvr.ccz")) 
                {
                    director->setContentScaleFactor(0.5);
                }
            }
            resDirOrders.push_back(pathPrefix + "Resources_SD");
            resDirOrders.push_back(pathPrefix + "Resources_HD");
            resDirOrders.push_back(pathPrefix + "Resources_LD");
        }
        else
        {
            director->setContentScaleFactor(0.5);
            if (!FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_LD/hud.pvr.ccz")) {
                if (FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_SD/hud.pvr.ccz")) {
                    director->setContentScaleFactor(1);
                } else if (FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_HD/hud.pvr.ccz")) {
                    director->setContentScaleFactor(2);
                }
            }
            resDirOrders.push_back(pathPrefix + "Resources_LD");
            resDirOrders.push_back(pathPrefix + "Resources_SD");
            resDirOrders.push_back(pathPrefix + "Resources_HD");
        }
    } 
    else if (platform == Application::Platform::OS_WINDOWS || platform == Application::Platform::OS_WINRT || platform == Application::Platform::OS_WP8) {
        //RADS: WP: Temporarily lowering the requirements of sd and hd since windows uses internal scale which is not captured.
        //RADS: WP: Need to figure out exact internal scale using c# code since cpp variant is not availbale.
        if (screenSize.height > 600)
        {
            director->setContentScaleFactor(2.0);
            resDirOrders.push_back(pathPrefix + "Resources_HD");
            resDirOrders.push_back(pathPrefix + "Resources_SD");
            resDirOrders.push_back(pathPrefix + "Resources_LD");
            if (!FileUtils::getInstance()->isFileExist(pathPrefix + "Resources_HD/cards.pvr.ccz"))
            {
                director->setContentScaleFactor(1.0);
            }
        }
        else if (screenSize.height > 333)
        {
            director->setContentScaleFactor(1.0);
            resDirOrders.push_back(pathPrefix + "Resources_SD");
            resDirOrders.push_back(pathPrefix + "Resources_LD");
        }
        else
        {
            director->setContentScaleFactor(0.5);
            resDirOrders.push_back(pathPrefix + "Resources_LD");
            resDirOrders.push_back(pathPrefix + "Resources_SD");  // TODO temporary fix for missing textures in iphone
        }
    }
    // resDirOrders.push_back("Sounds/");
    // resDirOrders.push_back("localization/");

    // 2. DEVICE TYPE
    if (platform == Application::Platform::OS_IPHONE) 
    {
        Globals::deviceType = TYPE_PHONE;
    } 
    else if (platform == Application::Platform::OS_WINDOWS || platform == Application::Platform::OS_ANDROID || platform == Application::Platform::OS_WINRT || platform == Application::Platform::OS_WP8)
    {
        float dpi = Device::getDPI();
        float screenLengthInch = screenSize.width / dpi, screenWidthInch = screenSize.height / dpi;
        if (screenLengthInch * screenLengthInch + screenWidthInch * screenWidthInch > 36.0f)
        {
            Globals::deviceType = TYPE_TABLETS;
        } 
        else 
        {
            Globals::deviceType = TYPE_PHONE;
        }
    } 
    else if (platform == Application::Platform::OS_IPAD || platform == Application::Platform::OS_MAC)
    {
        Globals::deviceType = TYPE_TABLETS;
    }

    // 3. DEVICE LAYOUT
    if (LAYOUT_PHONE == Globals::getApplicableLayout()) 
    {
        Size designSize = Size(960, 640);
        Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
    } 
    else 
    {
        Size designSize = Size(1024, 768);
        Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
    }

    FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 30);
    if (LAYOUT_PHONE == Globals::getApplicableLayout()) {
        director->setAnimationInterval(1.0 / 30.0);
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // END: EXPERIMENTAL

    register_all_packages();

    // Load SpriteFrames
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Common.plist", "Common.pvr.ccz");
    
    // Register CustomClass
    REGISTER_CLASS_TO_FACTORY(CustomLayer)
    REGISTER_CLASS_TO_FACTORY(PageViewItem)
    
    // create scene
    CustomScene* scene = CustomScene::createFromCCreator();
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
