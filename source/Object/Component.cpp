#include "Component.h"
#include "Object.h"

std::string Component::GetName() {
    return object_->GetName();
}

template <typename T>
T* Component::GetComponent() {
    return object_->GetComponent<T>();
}

template <typename T>
T* Component::GetComponentInChildren() {
    return object_->GetComponentInChildren<T>();
}

template <typename T>
T* Component::GetComponentInParent() {
    return object_->GetComponentInParent<T>();
}

template <typename T>
T* Component::GetComponents() {
    return object_->GetComponents<T>();
}

template <typename T>
T* Component::GetComponentsInChildren() {
    return object_->GetComponentsInChildren<T>();
}

template <typename T>
T* Component::GetComponentsInParent() {
    return object_->GetComponentsInParent<T>();
}

template <typename T>
void Component::Destroy(Component* c) {
    c->object_->RemoveComponent<T>(c);
}
