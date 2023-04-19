#pragma once
#include <glm/glm.hpp>
#include "../../../Model/Model.h"
#include "../../../Object/ObjectCommons.h"
#include "../../Component.h"
#include "../../../Math/MathCommons.h"
#include "../../../Math/Vector3.h"
#include "../../../Math/Vector4.h"
#include "../../../Math/Quaternion.h"

class Renderer : public Component {
private:
	Model* model_;
	Shader* shader_;
public:
	Renderer(Object* object);
	Renderer(Object* object, Model* model);
	Renderer(Object* object, Model* model, Shader* shader);
	Renderer(Object* object, std::string model_path);
	Renderer(Object* object, std::string model_path, Shader* shader);
	~Renderer();
	void Render();
	Model* GetModel();
	void SetModel(Model* model);
	Shader* GetShader();
	void SetShader(Shader* shader);

	std::type_index GetType();
	static std::type_index Type();
};