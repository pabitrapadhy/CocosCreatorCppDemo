#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "CocosObjectFactory.h"
#include "reader/CreatorReader.h"

#define NOT !

using namespace cocos2d;
using namespace creator;
using namespace ui;  

#pragma mark - Variable Declaration & Definition
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_COCOS_UI(__className, __memberName__) __className *__memberName__;

#define GET_CHILD_BY_NAME(__parentNode__, __outNode__, __classType__, __childName) \
    { \
        __outNode__ = dynamic_cast<__classType__ *>(__parentNode__->getChildByName(__childName)); \
        CC_ASSERT(__outNode__ != NULL); \
    } \
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - Touch Event Declaration & Definition
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_TOUCH_CALLBACK \
   void onTouchBase(cocos2d::Ref *pObject, cocos2d::ui::Widget::TouchEventType type); \
   void onTouch(cocos2d::Ref *pObject, cocos2d::ui::Widget::TouchEventType type); \

#define DEFINE_TOUCH_CALLBACK(__classname__) \
    void __classname__::onTouchBase(cocos2d::Ref *pObject, cocos2d::ui::Widget::TouchEventType type) \
    { \
        if(type == cocos2d::ui::Widget::TouchEventType::ENDED) \
        { \
            onTouch(pObject, type); \
            cocos2d::ui::Button* buttonNode = dynamic_cast<cocos2d::ui::Button*>(pObject); \
            if (buttonNode) \
            { \
                CCLOG("Play Button Tap Sound here."); \
            } \
        } \
    } \

#define DECLARE_TOUCH_HANDLING_EVENTS \
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event); \
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event); \
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event); \

#define ATTACH_TOUCH_EVENT_HANDLER_AND_LISTENER(__classname__) \
    auto touchListener = EventListenerTouchOneByOne::create(); \
    touchListener->onTouchBegan = CC_CALLBACK_2(__classname__::onTouchBegan, this); \
    touchListener->onTouchMoved = CC_CALLBACK_2(__classname__::onTouchMoved, this); \
    touchListener->onTouchEnded = CC_CALLBACK_2(__classname__::onTouchEnded, this); \
    auto eventDispatcher = Director::getInstance()->getEventDispatcher(); \
    eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this); \
///////////////////////////////////////////////////////////////////////////////////////////////////////    

#pragma mark - Button Touch Callback Glue
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define GLUE_BTN_EVENT_WITH_TOUCH_CALLBACK(__classname__, __buttonObj__, __parentNode__) \
    { \
        CC_ASSERT(__buttonObj__ != NULL); \
        CC_ASSERT(dynamic_cast<cocos2d::ui::Button*>(__buttonObj__)); \
        __buttonObj__->addTouchEventListener(CC_CALLBACK_2(__classname__::onTouchBase, __parentNode__)); \
    } \
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - Custom Creator Reader
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_CREATOR_READER_FOR_SCENE_CLASS(__classname__, __classreadername__) \
    class __classreadername__ : public creator::CreatorReader \
    { \
    public: \
        static __classreadername__* createWithFilename(const std::string& filename); \
        virtual __classname__* createScene(const creator::buffers::Scene* sceneBuffer) const; \
    }; \

#define DEFINE_CREATOR_READER_FOR_SCENE_CLASS(__classname__, __classreadername__) \
    __classreadername__* __classreadername__::createWithFilename(const std::string& filename) \
    { \
        __classreadername__* reader = new(std::nothrow) __classreadername__; \
        if (reader && reader->initWithFilename(filename)) \
        { \
            reader->autorelease(); \
            return reader; \
        } \
        return nullptr; \
    } \
    \
    __classname__* __classreadername__::createScene(const creator::buffers::Scene* sceneBuffer) const { \
        __classname__* scene = __classname__::create(); \
        return scene; \
    } \

#define DECLARE_CREATOR_READER_FOR_NODE_CLASS(__classname__, __classreadername__) \
    class __classreadername__ : public creator::CreatorReader \
    { \
    public: \
        static __classreadername__* createWithFilename(const std::string& filename); \
    }; \

#define DEFINE_CREATOR_READER_FOR_NODE_CLASS(__classname__, __classreadername__) \
    __classreadername__* __classreadername__::createWithFilename(const std::string& filename) \
    { \
        __classreadername__* reader = new(std::nothrow) __classreadername__; \
        if (reader && reader->initWithFilename(filename)) \
        { \
            reader->autorelease(); \
            return reader; \
        } \
        return nullptr; \
    } \
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - Scene Creation Logic
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define CREATE_READER_FOR_SCENE_CLASS(__classname__, __classreadername__, __filename__) \
    __classname__* __classname__::createFromCCreator() \
    { \
        __classname__* rootNode = nullptr; \
        __classreadername__* reader = __classreadername__::createWithFilename(__filename__); \
        if (reader) \
        { \
            reader->setup(); \
            rootNode = static_cast<__classname__*>(reader->getSceneGraph()); \
            rootNode->loadMembers(); \
        } \
        return rootNode; \
    } \
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - Layer Creation Logic
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define CREATE_READER_FOR_NODE_CLASS(__classname__, __classreadername__, __filename__, __nodename__) \
    __classname__* __classname__::createFromCCreator() \
    { \
        __classname__* rootNode = nullptr; \
        __classreadername__* reader = __classreadername__::createWithFilename(__filename__); \
        if (reader) \
        { \
            reader->setup(); \
            rootNode = static_cast<__classname__*>(reader->getNodeGraph<__classname__>(__nodename__)); \
            rootNode->loadMembers(); \
        } \
        return rootNode; \
    } \
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - Object Factory (String To Class Type)
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_OBJECT_FACTORY(__classname__) \
    class __classname__##Factory : public CocosObjectFactory { \
    public: \
       __classname__##Factory() \
       { \
            CocosObject::registerFactory(#__classname__, this); \
       } \
       virtual CocosObject* createFactoryNode() \
       { \
           __classname__* ref = __classname__::create(); \
           return static_cast<CocosObject*>(ref); \
       } \
    }; \
    static __classname__##Factory instance;
