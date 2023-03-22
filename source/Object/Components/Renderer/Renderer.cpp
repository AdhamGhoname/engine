#include "Renderer.h"
#include "../../Object.h"
#include "../../../Scene/Scene.h"
#include "../Transform/Transform.h"
#include <iostream>

Renderer::Renderer(Object* object) : Component(object) {
	model_ = NULL;
	shader_ = Shader::StandardShader();
}

Renderer::Renderer(Object* object, Model* model) : Component(object) {
	model_ = model;
	shader_ = Shader::StandardShader();
}

Renderer::Renderer(Object* object, Model* model, Shader* shader) : Component(object) {
	model_ = model;
	shader_ = shader;
}


Renderer::Renderer(Object* object, std::string model_path) : Component(object) {
	model_ = new Model(model_path.c_str());
	shader_ = Shader::StandardShader();
}

Renderer::Renderer(Object* object, std::string model_path, Shader* shader) : Component(object) {
	model_ = new Model(model_path.c_str());
	shader_ = shader;
}

Renderer::~Renderer() {
	delete shader_;
}

void Renderer::Render() {
	if (model_ == NULL || shader_ == NULL) {
		return;
	}
	shader_->use();
	int success = object_->GetScene()->Prerender(shader_);
	if (success != 0) {
		return;
	}
	glm::mat4 modelMatrix = object_->GetTransform()->GetLocalToWorldMatrix();
	shader_->setUniform("Model", modelMatrix);
	shader_->setUniform("Normal", glm::mat3(glm::transpose(glm::inverse(modelMatrix))));
	model_->render(*shader_);
}

Model* Renderer::GetModel() {
	return model_;
}

void Renderer::SetModel(Model* model) {
	model_ = model;
}

Shader* Renderer::GetShader() {
	return shader_;
}

void Renderer::SetShader(Shader* shader) {
	shader_ = shader;
}