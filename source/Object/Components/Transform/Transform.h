#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../../Component.h"

using namespace std;
class Object;

class Transform {
private:
	Transform* parent_;
    Object* object_;
	vector<Transform*> children_;
    glm::vec3 position_;
    glm::fquat rotation_;
    glm::vec3 scale_;
    
public:
    Transform* GetParent();
    void SetParent(Transform* parent);
    Object* GetObject();
    int GetChildCount();
    Transform* GetChild(int index);
    
    glm::vec3 GetPosition();
    glm::vec3 SetPosition();
};
