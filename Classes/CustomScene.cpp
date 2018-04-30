#include "CustomScene.h"
#include "CustomLayer.h"

#define SCENE_NAME "creator/Scene/TrainingScene.ccreator"

// NOTE: These declarations must be done for every class using the creator scenes
DEFINE_CREATOR_READER_FOR_SCENE_CLASS(CustomScene, CustomSceneReader); // only for scene classes
CREATE_READER_FOR_SCENE_CLASS(CustomScene, CustomSceneReader, SCENE_NAME); // only for scene classes
DEFINE_TOUCH_CALLBACK(CustomScene); // for everything

CustomScene::CustomScene() {
    // NOTE: It is always better to assign nullptr to variables used in the class, which are to reference
    // the cocos creator design file. Because, if prevents from garbage value of scene persistence.
    this->backgroundLayer = nullptr;
    this->quitBtn = nullptr;
    this->quitLabel = nullptr;
    this->topLayer = nullptr;
}

bool CustomScene::init() {
    if (!Scene::init()) {
        return false;
    }
    // NOTE: if you want to set something pre-initialization of the scene UI.
    // such as Event Listeners and Message Handlers.
    
    return true;
}

void CustomScene::testUI() {
    // GLUE MEMBER VARIABLES
    GET_CHILD_BY_NAME(this, backgroundLayer, cocos2d::Node, "BackgroundLayer");
    GET_CHILD_BY_NAME(this, quitBtn, cocos2d::ui::Button, "QuitButton");
    GET_CHILD_BY_NAME(this, quitLabel, cocos2d::Label, "QuitLabel");
    GET_CHILD_BY_NAME(this, topLayer, CustomLayer, "Layer_CustomLayer_TopLayer");

    // GLUE BUTTON CALLBACK
    // NOTE: NEED TO BE DONE FOR ALL BUTTONS, ELSE NO CALLBACK RECEIVED BY DEFAULT.
    GLUE_BTN_EVENT_WITH_TOUCH_CALLBACK(CustomScene, quitBtn, this);
    
    // tests
    this->test();
}

void CustomScene::onTouch(cocos2d::Ref* sender, Widget::TouchEventType type) {
    // event is received when touch is ended.
    // modified to received only Touch Ended event callbacks.
    if (sender == quitBtn) {
        CCLOG("TOUCH RECEIVED");
    }
}

void CustomScene::test() {
    if (topLayer) {
        CCLOG("Custom Layer class found.");
        topLayer->test();
    }
}
