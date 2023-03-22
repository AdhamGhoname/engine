#include "Light.h"
#include "../Math/Vector3.h"
#include "../Scene/Scene.h"
#include <iostream>

Light::Light(Scene* scene) : Object(scene) {
	ambient_ = Vector3::One() * 0.2f;
	diffuse_ = Vector3::One() * 0.7f;
	specular_ = Vector3::One() * 1.0f;
}

Light::Light(Scene* scene, Vector3 ambient, Vector3 diffuse, Vector3 specular) : Object(scene) {
	ambient_ = ambient;
	diffuse_ = diffuse;
	specular_ = specular;
}

Vector3 Light::GetAmbient() {
	return ambient_;
}

Vector3 Light::GetDiffuse() {
	return diffuse_;
}

Vector3 Light::GetSpecular() {
	return specular_;
}

void Light::SetAmbient(Vector3 ambient) {
	ambient_ = ambient;
}

void Light::SetDiffuse(Vector3 diffuse) {
	diffuse_ = diffuse_;
}

void Light::SetSpecular(Vector3 specular) {
	specular_ = specular;
}