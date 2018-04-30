#pragma once
#include "cocos2d.h"
#include "CreatorReader.h"
#include "CocosCustomMacros.h"

using namespace cocos2d;
using namespace creator;
using namespace ui;

class CustomLayer;
class CustomScene : public cocos2d::Scene {
public:
    DECLARE_TOUCH_CALLBACK;

    // member variables
    DECLARE_COCOS_UI(cocos2d::Node, backgroundLayer);
    DECLARE_COCOS_UI(cocos2d::ui::Button, quitBtn);
    DECLARE_COCOS_UI(cocos2d::Label, quitLabel);
    DECLARE_COCOS_UI(CustomLayer, topLayer);
    
    // member functions
    CustomScene();
	static CustomScene* createFromCCreator();
	virtual bool init() override;
    
    void testUI();    
    void test();
    
    CREATE_FUNC(CustomScene);
};

DECLARE_CREATOR_READER_FOR_SCENE_CLASS(CustomScene, CustomSceneReader);
