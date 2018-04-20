#include "HelloWorldScene.h"
#define COCOS_VIEW_ROOTLAYER "creator/Scene/TrainingScene.ccreator"

// NOTE: These declarations must be done for every class using the creator scenes
DEFINE_CREATOR_READER_FOR_CLASS(HelloWorld, HelloWorldReader);
CREATE_READER_FOR_CLASS(HelloWorld, HelloWorldReader, COCOS_VIEW_ROOTLAYER);
DEFINE_TOUCH_CALLBACK(HelloWorld);

HelloWorld::HelloWorld() {
    // NOTE: It is always better to assign nullptr to variables used in the class, which are to reference
    // the cocos creator design file. Because, if prevents from garbage value of scene persistence.
    this->backgroundLayer = nullptr;
    this->quitBtn = nullptr;
    this->quitLabel = nullptr;
}

bool HelloWorld::init() {
    if (!Scene::init()) {
        return false;
    }
    // NOTE: if you want to set something pre-initialization of the scene UI.
    // such as Event Listeners and Message Handlers.
    return true;
}

void HelloWorld::testUI() {
    // GLUE MEMBER VARIABLES
    GET_CHILD_BY_NAME(this, backgroundLayer, cocos2d::Node, "BackgroundLayer");
    GET_CHILD_BY_NAME(this, quitBtn, cocos2d::ui::Button, "QuitButton");
    GET_CHILD_BY_NAME(this, quitLabel, cocos2d::Label, "QuitLabel");

    // GLUE BUTTON CALLBACK
    // NOTE: NEED TO BE DONE FOR ALL BUTTONS, ELSE NO CALLBACK RECEIVED BY DEFAULT.
    GLUE_BTN_EVENT_WITH_TOUCH_CALLBACK(HelloWorld, quitBtn, this);
}

void HelloWorld::onTouch(cocos2d::Ref* sender, Widget::TouchEventType type) {
    // event is received when touch is ended.
    // modified to received only Touch Ended event callbacks.
    if (sender == quitBtn) {
        CCLOG("TOUCH RECEIVED");
    }
}
