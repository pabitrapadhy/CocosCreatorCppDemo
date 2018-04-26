#include "CustomLayer.h"

#define SCENE_NAME "creator/Scene/TrainingScene.ccreator"
#define LAYER_NAME "Layer_CustomLayer_TopLayer"

// NOTE: These declarations must be done for every class using the creator scenes
DEFINE_CREATOR_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader);
CREATE_READER_FOR_NODE_CLASS(CustomLayer, CustomLayerReader, SCENE_NAME, LAYER_NAME);
REGISTER_OBJECT_FACTORY(CustomLayer);

CustomLayer::CustomLayer() {
    CCLOG("CustomLayer Constructor");
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
