#pragma once
#include <string>
#include <vector>
#include "../Math/MathCommons.h"
#include "ObjectCommons.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Object {
protected:
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
    template <typename T>
    T* AddComponent() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");
        T* component = new T(this);
        components_[typeid(T)].push_back(component);
        return component;
    }

    template <typename T>
    void RemoveComponent() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");
        components_[typeid(T)].clear();
    }

    template <typename T>
    void RemoveComponent(Component* c) {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");
        auto it = std::find(components_[typeid(T)].begin(),
            components_[typeid(T)].end(),
            c);
        if (it == components_[typeid(T)].end())
            return;
        components_[typeid(T)].erase(it);
    }

    template <typename T>
    T* GetComponent() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");
        return components_[typeid(T)].empty() ? NULL : (T*)components_[typeid(T)][0];
    }

    template <typename T>
    T* GetComponentInChildren() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");

        T* comp = this->GetComponent<T>();
        if (comp != NULL) {
            return comp;
        }

        for (int i = 0; i < transform_->GetChildCount(); i++) {
            Transform* t = transform_->GetChild(i);
            Component* result = t->GetComponentInChildren<T>();
            if (result != NULL) {
                return result;
            }
        }
        return NULL;
    }

    template <typename T>
    T* GetComponentInParent() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");

        T* comp = this->GetComponent<T>();
        if (comp != NULL) {
            return comp;
        }

        if (transform_->HasParent()) {
            comp = transform_->GetParent()->GetComponentInParent<T>();
        }
        return comp;
    }

    template <typename T>
    std::vector<T*> GetComponents() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");

        return std::vector<T*>(components_[typeid(T)].begin(), components_[typeid(T)].end());
    }

    template <typename T>
    std::vector<T*> GetComponentsInChildren() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");

        std::vector<T*> result(components_[typeid(T)].begin(), components_[typeid(T)].end());
        for (int i = 0; i < transform_->GetChildCount(); i++) {
            std::vector<T*> comps = transform_->GetChild(i)->GetComponentsInChildren<T>();
            result.insert(result.end(), comps.begin(), comps.end());
        }
        return result;
    }

    template <typename T>
    std::vector<T*> GetComponentsInParent() {
        static_assert(std::is_base_of<Component, T>::value, "Not a component");

        std::vector<T*> result = this->GetComponents<T>();
        if (transform_->HasParent()) {
            std::vector<T*> comps = transform_->GetParent()->GetComponentsInParent<T>();
            result.insert(result.end(), comps.begin(), comps.end());
        }
        return result;
    }
    static void DestoryRecursive(Object* object);
    static void Destory(Object* object);
};
