#pragma once
#include "ObjectCommons.h"
#include <string>
#include <vector>
#include <typeindex>
#include <typeinfo>


class Component {
protected:
    Object* object_;
public:
    Component(Object* object);
    std::string GetName();
    virtual std::type_index GetType() = 0;
    Component* GetComponent(std::type_index componentType);
    Component* GetComponentInChildren(std::type_index componentType);
    Component* GetComponentInParent(std::type_index componentType);
    std::vector<Component*> GetComponents(std::type_index componentType);
    std::vector<Component*> GetComponentsInChildren(std::type_index componentType);
    std::vector<Component*> GetComponentsInParent(std::type_index componentType);
    void Destroy(Component* c);
    static std::type_index Type();
};
