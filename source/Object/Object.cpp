#include "Object.h"
#include "Components/Transform/Transform.h"
#include <type_traits>


void Object::init(Scene* scene, Object* object) {
    init(scene,
         object->GetTransform()->GetPosition(),
         object->GetTransform()->GetRotation(),
         object->GetTransform()->GetScale());
    name_ = object->GetName();
}

void Object::init(Scene* scene) {
    init(scene, Vector3::Zero());
}

void Object::init(Scene* scene, Vector3 position) {
    init(scene, position, Quaternion::Identity());
}

void Object::init(Scene* scene, Vector3 position, Quaternion rotation) {
    init(scene, position, rotation, Vector3::One());
}

void Object::init(Scene* scene, Vector3 position, Quaternion rotation, Vector3 scale) {
    transform_ = new Transform(this, scene->GetRootTransform(), position, rotation, scale);
    scene_ = scene;
    activeInHierarchy_ = activeSelf_ = true;
    components_[typeid(Transform)].push_back(transform_);
}

Object::Object(Scene* scene) {
    init(scene);
}

Object::Object(Scene* scene, Object* object) {
    init(scene, object);
}

Object::Object(Scene* scene, Vector3 position) {
    init(scene, position);
}

Object::Object(Scene* scene, Vector3 position, Quaternion rotation) {
    init(scene, position, rotation);
}

Object::Object(Scene* scene, Vector3 position, Quaternion rotation, Vector3 scale) {
    init(scene, position, rotation, scale);
}

Object::~Object() {
    delete transform_;
    for (auto it : components_) {
        for (auto comp : it.second) {
            delete comp;
        }
    }
    components_.clear();
}

Transform* Object::GetTransform() {
    return transform_;
}

Scene* Object::GetScene() {
    return scene_;
}

std::string Object::GetName() {
    return name_;
}

void Object::SetName(std::string name) {
    assert(name.size() > 0);
    name_ = name;
}

template <typename T>
T* Object::AddComponent() {
    static_assert(std::is_base_of<Component, T>::value, "Not a component");
    T* component = new T();
    components_[typeid(T)].push_back(component);
    return component;
}

template <typename T>
void Object::RemoveComponent() {
    static_assert(std::is_base_of<Component, T>::value, "Not a component");
    components_[typeid(T)].clear();
}

template <typename T>
void Object::RemoveComponent(Component* c) {
    static_assert(std::is_base_of<Component, T>::value, "Not a component");
    auto it = std::find(components_[typeid(T)].begin(),
                        components_[typeid(T)].end(),
                        c);
    if (it == components_[typeid(T)].end())
        return;
    components_[typeid(T)].erase(it);
}

template <typename T>
T* Object::GetComponent() {
    static_assert(std::is_base_of<Component, T>::value, "Not a component");
    return components_[typeid(T)].empty() ? NULL : components_[typeid(T)][0];
}

template <typename T>
T* Object::GetComponentInChildren() {
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
T* Object::GetComponentInParent() {
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
std::vector<T*> Object::GetComponents() {
    static_assert(std::is_base_of<Component, T>::value, "Not a component");

    return std::vector<T*>(components_[typeid(T)].begin(), components_[typeid(T)].end());
}

template <typename T>
std::vector<T*> Object::GetComponentsInChildren() {
    static_assert(std::is_base_of<Component, T>::value, "Not a component");

    std::vector<T*> result(components_[typeid(T)].begin(), components_[typeid(T)].end());
    for (int i = 0; i < transform_->GetChildCount(); i++) {
        std::vector<T*> comps = transform_->GetChild(i)->GetComponentsInChildren<T>();
        result.insert(result.end(), comps.begin(), comps.end());
    }
    return result;
}

template <typename T>
std::vector<T*> Object::GetComponentsInParent() {
    static_assert(std::is_base_of<Component, T>::value, "Not a component");

    std::vector<T*> result = this->GetComponents<T>();
    if (transform_->HasParent()) {
        std::vector<T*> comps = transform_->GetParent()->GetComponentsInParent<T>();
        result.insert(result.end(), comps.begin(), comps.end());
    }
    return result;
}