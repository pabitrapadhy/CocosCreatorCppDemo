#pragma once

#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "CocosCustomMacros.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class CustomLayer : public cocos2d::ui::Widget {
public:
    DECLARE_TOUCH_CALLBACK;

    CustomLayer();
    static CustomLayer* createFromCCreator();
    void loadMembers();

    // member variables
    DECLARE_COCOS_UI(cocos2d::Label, layerInfoLabel);
    DECLARE_COCOS_UI(cocos2d::Sprite, backgroundSprite);
    DECLARE_COCOS_UI(cocos2d::Sprite, characterSprite);
    
    // member functions
    void setInfoLabel(const std::string& info);

    CREATE_FUNC(CustomLayer);
};

DECLARE_CREATOR_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader);
