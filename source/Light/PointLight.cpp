#include "PointLight.h"
#include "../Scene/Scene.h"
#include "../Object/Components/Transform/Transform.h"

PointLight::PointLight(Scene* scene) : Light(scene) {
	transform_->SetPosition(Vector3::Zero());
	attenuation_ = Vector3(1.0f, 0.09f, 0.032f);
	scene->AddLight(this);
}

PointLight::PointLight(Scene* scene, Vector3 position) : Light(scene) {
	transform_->SetPosition(position);
	attenuation_ = Vector3(1.0f, 0.09f, 0.032f);
	scene->AddLight(this);
}

PointLight::PointLight(Scene* scene, Vector3 position, Vector3 attenuation) : Light(scene) {
	transform_->SetPosition(position);
	attenuation_ = attenuation;
	scene->AddLight(this);
}

PointLight::PointLight(Scene* scene, 
	Vector3 position, 
	Vector3 attenuation, 
	Vector3 ambient, 
	Vector3 diffuse, 
	Vector3 specular) : Light(scene, ambient, diffuse, specular) {
	transform_->SetPosition(position);
	attenuation_ = attenuation;
	scene->AddLight(this);
}

Vector3 PointLight::GetAttenuation() {
	return attenuation_;
}

void PointLight::SetAttenuation(Vector3 attenuation) {
	attenuation_ = attenuation;
}

std::type_index PointLight::GetTypeIndex() {
	return typeid(PointLight);
}