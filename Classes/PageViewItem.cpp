#include "PageViewItem.hpp"

#define SCENE_NAME "creator/Scene/WelcomeScene.ccreator"
#define LAYER_NAME "Layer_PageViewItem_Item"

// NOTE: These declarations must be done for every class using the creator scenes
DEFINE_CREATOR_READER_FOR_NODE_CLASS(PageViewItem, PageViewItemReader); // MANDATORY: only for layer/view classes
CREATE_READER_FOR_NODE_CLASS(PageViewItem, PageViewItemReader, SCENE_NAME, LAYER_NAME); // MANDATORY: only for layer/view classes
DEFINE_TOUCH_CALLBACK(PageViewItem); // for everything

PageViewItem::PageViewItem() {
    CCLOG("PageViewItem Constructor");
}

void PageViewItem::loadMembers() {
    GET_CHILD_BY_NAME(this, Character, cocos2d::Sprite, "Character");
}

void PageViewItem::onTouch(cocos2d::Ref* sender, Widget::TouchEventType type) {
    // event is received when touch is ended.
    // modified to received only Touch Ended event callbacks.
}
