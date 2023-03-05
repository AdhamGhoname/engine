#pragma once
#include <vector>
#include "../Light/Light.h"
#include "../Object/ObjectCommons.h"
using namespace std;

class Scene {
private:
	Transform* _sceneRoot;

public:
	Transform* GetRootTransform();
};
