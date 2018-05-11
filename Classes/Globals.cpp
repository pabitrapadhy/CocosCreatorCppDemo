#include "Globals.h"

using namespace cocos2d;

AspectRatio Globals::currentAspectRatio = ASPECT_RATIO_4_3;
DeviceType Globals::deviceType = TYPE_OTHER;

DeviceLayout Globals::getApplicableLayout() {
    Application::Platform platform = Application::getInstance()->getTargetPlatform();
    
    if (platform == Application::Platform::OS_IPAD) {
        return LAYOUT_NORMAL;
    } else if(platform == Application::Platform::OS_IPHONE) {
        return LAYOUT_PHONE;
    } else if (platform == Application::Platform::OS_ANDROID) {
        if (Globals::deviceType == TYPE_TABLETS) {
            return LAYOUT_WIDESCREEN;
        } else if (Globals::deviceType == TYPE_PHONE) {
            return LAYOUT_PHONE;
        }
    } else if (platform == Application::Platform::OS_MAC) {
        return LAYOUT_WIDESCREEN;
    }
    return LAYOUT_NORMAL;
}

DeviceType Globals::getDeviceType() {
    return Globals::deviceType;
}

DevicePlatform Globals::getDevicePlatform() {
    Application::Platform platform = Application::getInstance()->getTargetPlatform();
    if (platform == Application::Platform::OS_ANDROID) {
        return PLATFORM_ANDROID;
    } else if (platform == Application::Platform::OS_IPHONE || platform == Application::Platform::OS_IPAD) {
        return PLATFORM_IOS;
    }
    return PLATFORM_UNKNOWN;
}
