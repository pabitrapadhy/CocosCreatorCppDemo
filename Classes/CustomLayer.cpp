#include "CustomLayer.h"

#define SCENE_NAME "creator/Scene/WelcomeScene.ccreator"
#define LAYER_NAME "Layer_CustomLayer_RootLayer"

// NOTE: These declarations must be done for every class using the creator scenes
DEFINE_CREATOR_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader); // MANDATORY: only for layer/view classes
CREATE_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader, SCENE_NAME, LAYER_NAME); // MANDATORY: only for layer/view classes
DEFINE_TOUCH_CALLBACK(CustomLayer); // for everything
REGISTER_OBJECT_FACTORY(CustomLayer); // MANDATORY: only for layer/view classes

CustomLayer::CustomLayer() {
    CCLOG("CustomLayer Constructor");
}

void CustomLayer::loadMembers() {
    GET_CHILD_BY_NAME(this, layerInfoLabel, cocos2d::Label, "LayerInfoLabel");
    GET_CHILD_BY_NAME(this, backgroundSprite, cocos2d::Sprite, "BackgroundImg");
    GET_CHILD_BY_NAME(this, characterSprite, cocos2d::Sprite, "CharacterSprite");
}

void CustomLayer::setInfoLabel(const std::string& info) {
    this->layerInfoLabel->setString(info.c_str());
}

void CustomLayer::onTouch(cocos2d::Ref* sender, Widget::TouchEventType type) {
    // event is received when touch is ended.
    // modified to received only Touch Ended event callbacks.
}
