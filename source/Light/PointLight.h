#pragma once
#include "Light.h"
#include <typeinfo>
#include <typeindex>

class PointLight : public Light {
protected:
	Vector3 attenuation_;
public:
	PointLight(Scene* scene);
	PointLight(Scene* scene, Vector3 position);
	PointLight(Scene* scene, Vector3 position, Vector3 attenuation);
	PointLight(Scene* scene, Vector3 position, Vector3 attenuation, Vector3 ambient, Vector3 diffuse, Vector3 specular);
	Vector3 GetAttenuation();
	void SetAttenuation(Vector3 attenuation);
	std::type_index GetTypeIndex() override;
};