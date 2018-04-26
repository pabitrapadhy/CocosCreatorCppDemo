#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "CocosViews/ICocosViewLifeCycle.h"
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
    } \
    return rootNode; \
} \
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - Layer Creation Logic
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_COCOS_CUSTOM_VIEW(__classname__) \
using namespace cocos2d; \
using namespace cocos2d::ui; \
class __classname__ : public cocos2d::ui::Widget, public ICocosViewLifeCycle, public CocosObject

#define CREATE_READER_FOR_NODE_CLASS(__classname__, __classreadername__, __filename__, __nodename__) \
__classname__* __classname__::createFromCCreator() \
{ \
    __classname__* rootNode = nullptr; \
    __classreadername__* reader = __classreadername__::createWithFilename(__filename__); \
    if (reader) \
    { \
        reader->setup(); \
        void* ref; \
        rootNode = static_cast<__classname__*>(reader->getNodeGraph((__classname__*)ref, __nodename__)); \
    } \
    return rootNode; \
} \
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - CocosView Lifecycle Events
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_CUSTOM_VIEW_LIFECYCLE_ONATTACHONDETACH \
virtual void            attachToScene(); \
virtual void            detachFromScene(); \

#define DECLARE_CUSTOM_VIEW_LIFECYCLE_ONLOADONUNLOAD \
virtual void            loadMembers(); \
virtual void            unloadMembers(); \

#define DECLARE_CUSTOM_VIEW_LIFECYCLE_ONPOSTATTACH \
virtual void            postAttachToScene(); \

#define DECLARE_CUSTOM_VIEW_LIFECYCLE_ONPREDETTACH \
virtual void            preDetachFromScene(); \
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
   virtual CocosObject* createFactoryNode() { \
       return static_cast<CocosObject*>(__classname__::create()); \
   } \
}; \
static __classname__##Factory instance;
