#pragma once
#include "CocosView.h"

DECLARE_COCOS_CUSTOM_VIEW(CustomLayer) {
protected:
    DECLARE_CUSTOM_VIEW_LIFECYCLE_ONATTACHONDETACH
    DECLARE_CUSTOM_VIEW_LIFECYCLE_ONLOADONUNLOAD
    DECLARE_CUSTOM_VIEW_LIFECYCLE_ONPOSTATTACH
    DECLARE_CUSTOM_VIEW_LIFECYCLE_ONPREDETTACH

public:
    DECLARE_TOUCH_CALLBACK;

    int value;
    CustomLayer();
    static CustomLayer* createFromCCreator();
    void test();

    DECLARE_COCOS_UI(cocos2d::ui::Button, secondBtn);

    CREATE_FUNC(CustomLayer);
};

DECLARE_CREATOR_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader);
