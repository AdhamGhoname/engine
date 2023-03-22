#pragma once
#include "../Object/Object.h"
#include "../Math/Vector3.h"
#include <typeinfo>
#include <typeindex>

class Light : public Object {
protected:
	Vector3 ambient_;
	Vector3 diffuse_;
	Vector3 specular_;
public:
	Light(Scene* scene);
	Light(Scene* scene, Vector3 ambient, Vector3 diffuse, Vector3 specular);
	Vector3 GetAmbient();
	Vector3 GetDiffuse();
	Vector3 GetSpecular();
	void SetAmbient(Vector3 ambient);
	void SetDiffuse(Vector3 diffuse);
	void SetSpecular(Vector3 specular);
	virtual std::type_index GetTypeIndex() = 0;
	static void Destroy(Light* light);
};