#include "CustomLayer.h"

#define SCENE_NAME "creator/Scene/TrainingScene.ccreator"
#define LAYER_NAME "Layer_CustomLayer_TopLayer"

// NOTE: These declarations must be done for every class using the creator scenes
DEFINE_CREATOR_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader); // only for layer/view classes
CREATE_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader, SCENE_NAME, LAYER_NAME); // only for layer/view classes
DEFINE_TOUCH_CALLBACK(CustomLayer); // for everything
REGISTER_OBJECT_FACTORY(CustomLayer); // only for layer/view classes

CustomLayer::CustomLayer() {
    CCLOG("CustomLayer Constructor");
    this->secondBtn = nullptr;
}

void CustomLayer::test() {
    GET_CHILD_BY_NAME(this, secondBtn, cocos2d::ui::Button, "SecondButton");
    
    GLUE_BTN_EVENT_WITH_TOUCH_CALLBACK(CustomLayer, secondBtn, this);
}

void CustomLayer::loadMembers() {
   CCLOG("pabitra: Layer->> loading members");
}

void CustomLayer::unloadMembers() {
   CCLOG("pabitra: Layer->> unloading members");
}

void CustomLayer::attachToScene() {
   CCLOG("pabitra: Layer->> attaching members to scene");
}

void CustomLayer::detachFromScene() {
   CCLOG("pabitra: Layer->> detaching members from scene");
}

void CustomLayer::postAttachToScene() {
   CCLOG("pabitra: Layer->> pre-attaching members to scene");
}

void CustomLayer::preDetachFromScene() {
   CCLOG("pabitra: Layer->> post-detaching members from scene");
}

void CustomLayer::onTouch(cocos2d::Ref* sender, Widget::TouchEventType type) {
    // event is received when touch is ended.
    // modified to received only Touch Ended event callbacks.
    if (sender == secondBtn) {
        CCLOG("TOUCH RECEIVED 1");
    }
}
