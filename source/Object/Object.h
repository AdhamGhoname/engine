#pragma once
#include <string>
#include <vector>
#include "../Math/MathCommons.h"
#include "ObjectCommons.h"
#include <typeinfo>
#include <typeindex>
#include <map>
#include <vector>

class Object {
protected:
    Transform* transform_;
    bool activeInHierarchy_;
    bool activeSelf_;
    Scene* scene_;
    std::map < std::type_index, std::vector<Component*> > components_;
    std::string name_;
    void init(Scene* scene);
    void init(Scene* scene, Object* object);
    void init(Scene* scene, Vector3 position);
    void init(Scene* scene, Vector3 position, Quaternion rotation);
    void init(Scene* scene, Vector3 position, Quaternion rotation, Vector3 scale);
public:
    Object(Scene* scene);
    Object(Scene* scene, Object* object);
    Object(Scene* scene, Vector3 position);
    Object(Scene* scene, Vector3 position, Quaternion rotation);
    Object(Scene* scene, Vector3 position, Quaternion rotation, Vector3 scale);
    ~Object();

    Transform* GetTransform();
    Scene* GetScene();

    std::string GetName();
    void SetName(std::string name);
    void SetActive(bool state);
    bool IsActive();
    Component* AddComponent(Component* component);
    void RemoveComponent(std::type_index componentType);
    void RemoveComponent(Component* c);
    Component* GetComponent(std::type_index componentType);
    Component* GetComponentInChildren(std::type_index componentType);
    Component* GetComponentInParent(std::type_index componentType);
    std::vector<Component*> GetComponents(std::type_index componentType);
    std::vector<Component*> GetComponentsInChildren(std::type_index componentType);
    std::vector<Component*> GetComponentsInParent(std::type_index componentType);
    static void DestoryRecursive(Object* object);
    static void Destory(Object* object);
};
