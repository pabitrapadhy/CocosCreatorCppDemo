#pragma once

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

enum ConnectionType {
    TYPE_NOT_CONNECTED = 0,
    TYPE_WIFI = 1,
    TYPE_MOBILE = 2
};

enum AspectRatio {
    ASPECT_RATIO_4_3,
    ASPECT_RATIO_16_9,
    ASPECT_RATIO_16_10,
    ASPECT_RATIO_OTHER
};

enum DeviceType {
    TYPE_PHONE = 0,
    TYPE_TABLETS,
    TYPE_OTHER
};

enum DeviceLayout {
    LAYOUT_WIDESCREEN = 0,
    LAYOUT_NORMAL,
    LAYOUT_PHONE
};

enum DevicePlatform {
    PLATFORM_UNKNOWN = 0,
    PLATFORM_ANDROID,
    PLATFORM_IOS,
    PLATFORM_WINDOWS
};

class Globals {
public:
    static AspectRatio currentAspectRatio;
    static DeviceType deviceType;

    static DeviceLayout getApplicableLayout();
    static DevicePlatform getDevicePlatform();
    static DeviceType getDeviceType();
};
