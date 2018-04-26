#pragma once

typedef std::map<std::string, CocosObjectFactory*> FACTORY_MAP;
class CocosObject {
public:
    static void registerFactory(const string& classname_str, CocosObjectFactory *factory) {
        fatories[name] = factory;
    }    
private:
    static FACTORY_MAP factories;
};

class CocosObjectFactory {
public:
	virtual static CocosObject* createFactoryNode() = 0;
};