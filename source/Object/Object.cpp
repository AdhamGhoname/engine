#include "Object.h"
#include "Components/Transform/Transform.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../Scene/Scene.h"
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
    transform_ = new Transform(this, scene == NULL ? NULL : scene->GetRootTransform(), position, rotation, scale);
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
    std::vector<Component*> to_be_deleted;
    for (auto it : components_) {
        for (auto comp : it.second) {
            to_be_deleted.push_back(comp);
        }
    }
    components_.clear();
    for (auto comp : to_be_deleted) {
        delete comp;
    }
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

Component* Object::AddComponent(Component* component) {
    components_[component->GetType()].push_back(component);
    return component;
}

void Object::RemoveComponent(std::type_index componentType) {
    components_[componentType].clear();
}

void Object::RemoveComponent(Component* c) {
    auto it = std::find(components_[c->GetType()].begin(), components_[c->GetType()].end(), c);
    if (it == components_[c->GetType()].end())
        return;
    components_[c->GetType()].erase(it);
}

Component* Object::GetComponent(std::type_index componentType) {
    return components_[componentType].empty() ? NULL : (Component*)components_[componentType][0];
}

Component* Object::GetComponentInChildren(std::type_index componentType) {

    Component* comp = this->GetComponent(componentType);
    if (comp != NULL) {
        return comp;
    }

    for (int i = 0; i < transform_->GetChildCount(); i++) {
        Transform* t = transform_->GetChild(i);
        Component* result = t->GetComponentInChildren(componentType);
        if (result != NULL) {
            return result;
        }
    }
    return NULL;
}

Component* Object::GetComponentInParent(std::type_index componentType) {

    Component* comp = this->GetComponent(componentType);
    if (comp != NULL) {
        return comp;
    }

    if (transform_->HasParent()) {
        comp = transform_->GetParent()->GetComponentInParent(componentType);
    }
    return comp;
}

std::vector<Component*> Object::GetComponents(std::type_index componentType) {
    return std::vector(components_[componentType].begin(), components_[componentType].end());
}

std::vector<Component*> Object::GetComponentsInChildren(std::type_index componentType) {
    std::vector result(components_[componentType].begin(), components_[componentType].end());
    for (int i = 0; i < transform_->GetChildCount(); i++) {
        std::vector<Component*> comps = transform_->GetChild(i)->GetComponentsInChildren(componentType);
        result.insert(result.end(), comps.begin(), comps.end());
    }
    return result;
}

std::vector<Component*> Object::GetComponentsInParent(std::type_index componentType) {
    std::vector<Component*> result = this->GetComponents(componentType);
    if (transform_->HasParent()) {
        std::vector<Component*> comps = transform_->GetParent()->GetComponentsInParent(componentType);
        result.insert(result.end(), comps.begin(), comps.end());
    }
    return result;
}


void Object::DestoryRecursive(Object* object) {
    for (int i = 0; i < object->GetTransform()->GetChildCount(); i++) {
        DestoryRecursive(object->GetTransform()->GetChild(i)->GetObject());
    }
    delete object;
}

void Object::Destory(Object* object) {
    delete object;
}