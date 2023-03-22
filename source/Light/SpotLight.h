#pragma once
#include "Light.h"
#include <typeinfo>
#include <typeindex>

class SpotLight : public Light {
protected:
	Vector3 direction_;
	Vector3 attenuation_;
	Vector2 bounds_;
public:
	SpotLight(Scene* scene);
	SpotLight(Scene* scene, Vector3 direction);
	SpotLight(Scene* scene, Vector3 direction, Vector2 bounds);
	SpotLight(Scene* scene, Vector3 direction, Vector2 bounds, Vector3 attenuation);
	SpotLight(Scene* scene, Vector3 direction, Vector2 bounds, Vector3 attenuation, Vector3 ambient, Vector3 diffuse, Vector3 specular);
	Vector3 GetDirection();
	void SetDirection(Vector3 direction);
	Vector3 GetAttenuation();
	void SetAttenuation(Vector3 attenuation);
	Vector2 GetBounds();
	void SetBounds(Vector2 bounds);
	std::type_index GetTypeIndex() override;
};