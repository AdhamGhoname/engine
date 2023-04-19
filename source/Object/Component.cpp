#include "Component.h"
#include "Object.h"

Component::Component(Object* object) {
    object_ = object;
}

std::string Component::GetName() {
    return object_->GetName();
}

Component* Component::GetComponent(std::type_index componentType) {
    return object_->GetComponent(componentType);
}

Component* Component::GetComponentInChildren(std::type_index componentType) {
    return object_->GetComponentInChildren(componentType);
}

Component* Component::GetComponentInParent(std::type_index componentType) {
    return object_->GetComponentInParent(componentType);
}

std::vector<Component*> Component::GetComponents(std::type_index componentType) {
    return object_->GetComponents(componentType);
}

std::vector<Component*> Component::GetComponentsInChildren(std::type_index componentType) {
    return object_->GetComponentsInChildren(componentType);
}

std::vector<Component*> Component::GetComponentsInParent(std::type_index componentType) {
    return object_->GetComponentsInParent(componentType);
}

void Component::Destroy(Component* c) {
    c->object_->RemoveComponent(c);
}

std::type_index Component::Type() {
    return typeid(Component);
}