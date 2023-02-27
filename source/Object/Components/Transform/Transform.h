#pragma once
#include <vector>
#include <glm/glm.hpp>
using namespace std;

class Transform {
private:
	Transform* parent;
	vector<Transform*> children;
};