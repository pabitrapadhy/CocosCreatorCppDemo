#pragma once
#include "cocos2d.h"
#include "CreatorReader.h"
#include "CocosCustomMacros.h"

using namespace cocos2d;
using namespace creator;
using namespace ui;

class HelloWorld : public cocos2d::Scene {
public:
    DECLARE_TOUCH_CALLBACK;
    
    // member variables
    DECLARE_COCOS_UI(cocos2d::Node, backgroundLayer);
    DECLARE_COCOS_UI(cocos2d::ui::Button, quitBtn);
    DECLARE_COCOS_UI(cocos2d::Label, quitLabel);
    
    // member functions
    HelloWorld();
	static HelloWorld* createFromCCreator();
	virtual bool init() override;
    
    void testUI();
    void actOnTouch(Ref* sender, Widget::TouchEventType type);
    
    CREATE_FUNC(HelloWorld);
};

DECLARE_CREATOR_READER_FOR_CLASS(HelloWorld, HelloWorldReader);
