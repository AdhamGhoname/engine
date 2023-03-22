#include "SpotLight.h"
#include "../Scene/Scene.h"

SpotLight::SpotLight(Scene* scene) : Light(scene) {
	direction_ = -1.0f * Vector3::One();
	attenuation_ = Vector3(1.0f, 0.09f, 0.032f);
	bounds_ = Vector2(45.0f, 50.0f);
	scene->AddLight(this);
}

SpotLight::SpotLight(Scene* scene, Vector3 direction) : Light(scene) {
	direction_ = direction;
	attenuation_ = Vector3(1.0f, 0.09f, 0.032f);
	bounds_ = Vector2(45.0f, 50.0f);
	scene->AddLight(this);
}

SpotLight::SpotLight(Scene* scene, Vector3 direction, Vector2 bounds) : Light(scene) {
	direction_ = direction;
	attenuation_ = Vector3(1.0f, 0.09f, 0.032f);
	bounds_ = bounds;
	scene->AddLight(this);
}

SpotLight::SpotLight(Scene* scene, Vector3 direction, Vector2 bounds, Vector3 attenuation) : Light(scene) {
	direction_ = direction;
	attenuation_ = attenuation;
	bounds_ = bounds;
	scene->AddLight(this);
}

SpotLight::SpotLight(Scene* scene,
	Vector3 direction,
	Vector2 bounds,
	Vector3 attenuation,
	Vector3 ambient,
	Vector3 diffuse,
	Vector3 specular) : Light(scene, ambient, diffuse, specular) {
	direction_ = direction;
	attenuation_ = attenuation;
	bounds_ = bounds;
	scene->AddLight(this);
}

Vector3 SpotLight::GetDirection() {
	return direction_;
}

void SpotLight::SetDirection(Vector3 direction) {
	direction_ = direction;
}

Vector3 SpotLight::GetAttenuation() {
	return attenuation_;
}

void SpotLight::SetAttenuation(Vector3 attenuation) {
	attenuation_ = attenuation;
}

Vector2 SpotLight::GetBounds() {
	return bounds_;
}

void SpotLight::SetBounds(Vector2 bounds) {
	bounds_ = bounds;
}

std::type_index SpotLight::GetTypeIndex() {
	return typeid(SpotLight);
}