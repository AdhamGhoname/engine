#include "Component.h"
#include "Object.h"

Component::Component(Object* object) {
    object_ = object;
}

std::string Component::GetName() {
    return object_->GetName();
}