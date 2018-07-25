#pragma once

#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "CocosCustomMacros.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class PageViewItem : public cocos2d::ui::Widget {
public:
    DECLARE_TOUCH_CALLBACK;
    
    PageViewItem();
    static PageViewItem* createFromCCreator();
    void loadMembers();
    
    // member variables
    DECLARE_COCOS_UI(cocos2d::Sprite, Character);
    
    // member functions
    
    CREATE_FUNC(PageViewItem);
};

DECLARE_CREATOR_READER_FOR_NODE_CLASS(PageViewItem, PageViewItemReader);
