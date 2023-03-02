#pragma once
#include <string>
#include <vector>
#include "../Math/MathCommons.h"
#include "../Scene/Scene.h"
#include "ObjectCommons.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

using namespace std;

class Object {
private:
    Transform* transform_;
    bool activeInHierarchy_;
    bool activeSelf_;
    Scene* scene_;
    unordered_map < type_index, vector<Component*> > components_;
    std::string name_;
public:
    Object();
    Object(Vector3 position);
    Object(Vector3 position, Quaternion rotation);
    Object(Vector3 position, Quaternion rotation, Vector3 scale);
    ~Object();

    std::string GetName();
    void SetActive(bool state);
    template<typename T> T AddComponent();
    template<typename T> T GetComponent();
    template<typename T> T GetComponentInChildren();
    template<typename T> T GetComponentInParent();
    template<typename T> T GetComponents();
    template<typename T> T GetComponentsInChildren();
    template<typename T> T GetComponentsInParent();
    static void Destory(Component c);
};
