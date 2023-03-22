#pragma once
#include "Light.h"
#include <typeinfo>
#include <typeindex>

class DirectionalLight : public Light {
protected:
	Vector3 direction_;
public:
	DirectionalLight(Scene* scene);
	DirectionalLight(Scene* scene, Vector3 direction);
	DirectionalLight(Scene* scene, Vector3 direction, Vector3 ambient, Vector3 diffuse, Vector3 specular);
	Vector3 GetDirection();
	void SetDirection(Vector3 direction);
	std::type_index GetTypeIndex() override;
};