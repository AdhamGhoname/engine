#pragma once
#include <string>
#include <vector>
#include "../Math/MathCommons.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "ObjectCommons.h"
#include "../Scene/Scene.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Object {
private:
    Transform* transform_;
    bool activeInHierarchy_;
    bool activeSelf_;
    Scene* scene_;
    std::unordered_map < std::type_index, std::vector<Component*> > components_;
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
    template<typename T> T* AddComponent();
    template<typename T> void RemoveComponent();
    template<typename T> void RemoveComponent(Component* c);
    template<typename T> T* GetComponent();
    template<typename T> T* GetComponentInChildren();
    template<typename T> T* GetComponentInParent();
    template<typename T> std::vector<T*> GetComponents();
    template<typename T> std::vector<T*> GetComponentsInChildren();
    template<typename T> std::vector<T*> GetComponentsInParent();
};
