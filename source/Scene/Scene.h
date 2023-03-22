#pragma once
#include <vector>
#include "../Light/Light.h"
#include "../Object/ObjectCommons.h"
#include <unordered_map>
#include <vector>
#include "../Camera/Camera.h"
#include "../Shader/Shader.h"
#include <typeinfo>
#include <typeindex>

class Scene {
private:
	Object* sceneRoot_;
	Camera* activeCamera_;
	std::string name_;
	std::unordered_map < std::type_index, std::vector<Light*>> lights_;
	void RenderRecursive(Transform* node);
public:
	Scene();
	Scene(std::string name);
	~Scene();
	std::string GetName();
	void SetName(std::string name);
	Camera* GetActiveCamera();
	void SetActiveCamera(Camera* camera);
	Transform* GetRootTransform();
	void AddLight(Light* light);
	void DestroyLight(Light* light);
	int Prerender(Shader* current_shader);
	void Render();
};
