#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional>

class CocosObjectFactory {
private:
    std::map<std::string, std::function<void* ()>> registry;
    
public:
    static CocosObjectFactory* getInstance() {
        static CocosObjectFactory instance;
        return &instance;
    }
    
    // register class
    void registerClass(const std::string& id, std::function<void* ()> functr) {
        if (registry.find(id) == registry.end()) {
            registry[id] = functr;
        }
    }
    
    // create object
    cocos2d::Node* createObject(std::string id) {
        if (registry.find(id) != registry.end()) {
            auto& functr = registry[id];
            return static_cast<cocos2d::Node*>(functr());
        }
        return nullptr;
    }
};
