#include "CustomScene.h"
#include "CustomLayer.h"
#include "PageViewItem.hpp"

#define SCENE_NAME "creator/Scene/WelcomeScene.ccreator"

// NOTE: These declarations must be done for every class using the creator scenes
DEFINE_CREATOR_READER_FOR_SCENE_CLASS(CustomScene, CustomSceneReader); // MANDATORY: only for scene classes
CREATE_READER_FOR_SCENE_CLASS(CustomScene, CustomSceneReader, SCENE_NAME); // MANDATORY: only for scene classes
DEFINE_TOUCH_CALLBACK(CustomScene); // for everything

CustomScene::CustomScene() {
    // NOTE: It is always better to assign nullptr to variables used in the class, which are to reference
    // the cocos creator design file. Because, if prevents from garbage value of scene persistence.
    this->backgroundLayer = nullptr;
    this->helloWorldSprite = nullptr;
    this->grossiniLayer = nullptr;
    this->createLayerButton = nullptr;
}

bool CustomScene::init() {
    if (!Scene::init()) {
        return false;
    }
    // NOTE: if you want to set something pre-initialization of the scene UI.
    // such as Event Listeners and Message Handlers.
    
    return true;
}

void CustomScene::loadMembers() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // GLUE MEMBER VARIABLES
    GET_CHILD_BY_NAME(this, backgroundLayer, cocos2d::Node, "BackgroundLayer");
    GET_CHILD_BY_NAME(this, createLayerButton, cocos2d::ui::Button, "CreateLayerButton");
    GET_CHILD_BY_NAME(this, helloWorldSprite, cocos2d::Sprite, "HelloWorldSprite");

    // NOTE: As per current implementation, loadMembers() is not called, if CustomLayer objects are created
    // while creating the scene. So, have to call the loadMembers() explicitly.
    GET_CHILD_BY_NAME(this, grossiniLayer, CustomLayer, "Layer_CustomLayer_RootLayer");
    this->grossiniLayer->loadMembers();

    // GLUE BUTTON CALLBACK
    // NOTE: NEED TO BE DONE FOR ALL BUTTONS, ELSE NO CALLBACK RECEIVED BY DEFAULT.
    GLUE_BTN_EVENT_WITH_TOUCH_CALLBACK(CustomScene, createLayerButton, this);
    
    this->grossiniLayer->setPositionX(visibleSize.width*0.1);
    
    // Testing the loadMembers() worked or not.
    this->grossiniLayer->setInfoLabel("test");
    
    // Adding custom elements into PageView
    GET_CHILD_BY_NAME(this, pageView, cocos2d::ui::PageView, "PageView");
    int numElements = 3;
    for (int i = 0; i < numElements; ++i) {
        auto page = PageViewItem::createFromCCreator(); // keep this node outside the scene, else it will draw that as well.
        pageView->addPage(page); // auto positioning and auto sizing of the scrollview.
    }
}

void CustomScene::onTouch(cocos2d::Ref* sender, Widget::TouchEventType type) {
    // event is received when touch is ended.
    // modified to received only Touch Ended event callbacks.
    if (sender == createLayerButton) {
        CCLOG("TOUCH RECEIVED : CustomScene");

        // creating a Layer class runtime.
        this->createLayerNode();
        this->createLayerButton->setEnabled(false);
    }
}

void CustomScene::createLayerNode() {
    // NOTE: creating a blank scene with only the node ("Layer_CustomLayer_RootLayer") is read
    // as a CustomLayer class.
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    CustomLayer* myLayer = CustomLayer::createFromCCreator();
    myLayer->setPositionX(visibleSize.width*0.7);
    myLayer->setInfoLabel("CustomLayer created in Runtime");
    this->addChild(myLayer);
}
