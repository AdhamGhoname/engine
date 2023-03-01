#pragma once
#include "Object.h"
#include "Components/Transform/Transform.h"
#include <string>


class Component {
private:
    Object* object_;
    Transform* transform_;    
public:
    Component();
    ~Component();

    std::string GetName();
    template<typename T> T GetComponent();
    template<typename T> T GetComponentInChildren();
    template<typename T> T GetComponentInParent();
    template<typename T> T GetComponents();
    template<typename T> T GetComponentsInChildren();
    template<typename T> T GetComponentsInParent();
    static void Destory(Component c);
};
