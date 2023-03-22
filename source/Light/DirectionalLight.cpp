#include "DirectionalLight.h"
#include "../Scene/Scene.h"
#include <iostream>

DirectionalLight::DirectionalLight(Scene* scene) : Light(scene) {
	direction_ = -1.0f * Vector3::One();
	scene->AddLight(this);
}

DirectionalLight::DirectionalLight(Scene* scene, Vector3 direction) : Light(scene) {
	direction_ = direction;
	scene->AddLight(this);
}

DirectionalLight::DirectionalLight(Scene* scene, 
	Vector3 direction, 
	Vector3 ambient, 
	Vector3 diffuse, 
	Vector3 specular) : Light(scene, ambient, diffuse, specular) {
	direction_ = direction;
	scene->AddLight(this);
}

Vector3 DirectionalLight::GetDirection() {
	return direction_;
}

void DirectionalLight::SetDirection(Vector3 direction) {
	direction_ = direction;
}

std::type_index DirectionalLight::GetTypeIndex() {
	return typeid(DirectionalLight);
}