#pragma once
#include "Singleton.h"

class SceneController : public Singleton<SceneController> {
public:
//    Node* _currentScene;
	void openView(const std::string& viewname);
};
