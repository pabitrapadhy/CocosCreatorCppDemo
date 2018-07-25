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
    DECLARE_COCOS_UI(cocos2d::Sprite, helloWorldSprite);
    DECLARE_COCOS_UI(CustomLayer, grossiniLayer);
    DECLARE_COCOS_UI(cocos2d::ui::Button, createLayerButton);
    
    DECLARE_COCOS_UI(cocos2d::ui::PageView, pageView);
    
    // member functions
    CustomScene();
	static CustomScene* createFromCCreator();
	virtual bool init() override;
    void loadMembers();
    
    void createLayerNode();
    
    CREATE_FUNC(CustomScene);
};

DECLARE_CREATOR_READER_FOR_SCENE_CLASS(CustomScene, CustomSceneReader);
