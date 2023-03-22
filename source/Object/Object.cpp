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

void Object::DestoryRecursive(Object* object) {
    for (int i = 0; i < object->GetTransform()->GetChildCount(); i++) {
        DestoryRecursive(object->GetTransform()->GetChild(i)->GetObject());
    }
    delete object;
}

void Object::Destory(Object* object) {
    delete object;
}