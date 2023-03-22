#pragma once
#include "ObjectCommons.h"
#include <string>


class Component {
protected:
    Object* object_;
public:
    Component(Object* object);
    std::string GetName();
    template <typename T>
    T* GetComponent() {
        return object_->GetComponent<T>();
    }

    template <typename T>
    T* GetComponentInChildren() {
        return object_->GetComponentInChildren<T>();
    }

    template <typename T>
    T* GetComponentInParent() {
        return object_->GetComponentInParent<T>();
    }

    template <typename T>
    T* GetComponents() {
        return object_->GetComponents<T>();
    }

    template <typename T>
    T* GetComponentsInChildren() {
        return object_->GetComponentsInChildren<T>();
    }

    template <typename T>
    T* GetComponentsInParent() {
        return object_->GetComponentsInParent<T>();
    }

    template <typename T>
    void Destroy(Component* c) {
        c->object_->RemoveComponent<T>(c);
    }

};
