#pragma once
#include "ObjectCommons.h"
#include <string>


class Component {
protected:
    Object* object_;
public:
    std::string GetName();
    template<typename T> T* GetComponent();
    template<typename T> T* GetComponentInChildren();
    template<typename T> T* GetComponentInParent();
    template<typename T> T* GetComponents();
    template<typename T> T* GetComponentsInChildren();
    template<typename T> T* GetComponentsInParent();
    template<typename T> static void Destroy(Component* c);
};
