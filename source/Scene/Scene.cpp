#include "Scene.h"
#include "../Object/Object.h"
#include "../Light/DirectionalLight.h"
#include "../Light/PointLight.h"
#include "../Light/SpotLight.h"
#include "../Object/Components/Transform/Transform.h"
#include "../Object/Components/Renderer/Renderer.h"
#include <string>
#include <glm/glm.hpp>
#include <iostream>
#include "../Engine/Engine.h"
#include <iostream>

Scene::Scene() {
    sceneRoot_ = new Object((Scene*)NULL);
    name_ = "Untitled Scene";
}

Scene::Scene(std::string name) {
    sceneRoot_ = new Object((Scene*)NULL);
    name_ = name;
}

Scene::~Scene() {
    Object::DestoryRecursive(sceneRoot_);
    lights_.clear();
}

Transform* Scene::GetRootTransform() {
    return sceneRoot_->GetTransform();
}

void Scene::AddLight(Light* light) {
    lights_[light->GetTypeIndex()].push_back(light);
}

void Scene::DestroyLight(Light* light) {
    std::vector<Light*> lights = lights_[light->GetTypeIndex()];
    auto it = std::find(lights.begin(), lights.end(), light);
    if (it == lights.end())
        return;
    lights.erase(it);
}

int Scene::Prerender(Shader* currentShader) {
    if (!activeCamera_) {
        return -1;
    }

    //Camera uniforms
    currentShader->setUniform("cameraPosition", activeCamera_->GetPosition());
    currentShader->setUniform("View", activeCamera_->GetViewMatrix());
    currentShader->setUniform("Projection", activeCamera_->GetProjectionMatrix());

    // Material properties
    currentShader->setUniform("material.shininess", 32.0f);
    // Directional Lights uniforms
    currentShader->setUniform("dirLightCount", (int)lights_[typeid(DirectionalLight)].size());
    for (int i = 0; i < lights_[typeid(DirectionalLight)].size(); i++) {
        DirectionalLight* light = (DirectionalLight*)lights_[typeid(DirectionalLight)][i];
        currentShader->setUniform("directionalLights[" + std::to_string(i) + "].direction", light->GetDirection());
        currentShader->setUniform("directionalLights[" + std::to_string(i) + "].ambient", light->GetAmbient());
        currentShader->setUniform("directionalLights[" + std::to_string(i) + "].diffuse", light->GetDiffuse());
        currentShader->setUniform("directionalLights[" + std::to_string(i) + "].specular", light->GetSpecular());
    }

    // Point Lights uniforms
    currentShader->setUniform("pointLightCount", (int)lights_[typeid(PointLight)].size());
    for (int i = 0; i < lights_[typeid(PointLight)].size(); i++) {
        PointLight* light = (PointLight*)lights_[typeid(PointLight)][i];
        currentShader->setUniform("pointLights[" + std::to_string(i) + "].position", light->GetTransform()->GetPosition());
        currentShader->setUniform("pointLights[" + std::to_string(i) + "].ambient", light->GetAmbient());
        currentShader->setUniform("pointLights[" + std::to_string(i) + "].diffuse", light->GetDiffuse());
        currentShader->setUniform("pointLights[" + std::to_string(i) + "].specular", light->GetSpecular());
        currentShader->setUniform("pointLights[" + std::to_string(i) + "].attenuation", light->GetAttenuation());
    }

    // Spot Lights uniforms
    currentShader->setUniform("spotLightCount", (int)lights_[typeid(SpotLight)].size());
    for (int i = 0; i < lights_[typeid(SpotLight)].size(); i++) {
        SpotLight* light = (SpotLight*)lights_[typeid(SpotLight)][i];
        currentShader->setUniform("spotLights[" + std::to_string(i) + "].position", light->GetTransform()->GetPosition());
        currentShader->setUniform("spotLights[" + std::to_string(i) + "].ambient", light->GetAmbient());
        currentShader->setUniform("spotLights[" + std::to_string(i) + "].diffuse", light->GetDiffuse());
        currentShader->setUniform("spotLights[" + std::to_string(i) + "].specular", light->GetSpecular());
        currentShader->setUniform("spotLights[" + std::to_string(i) + "].attenuation", light->GetAttenuation());
        Vector2 bounds = light->GetBounds();
        Vector3 boundsData = Vector3(glm::cos(glm::radians(bounds.x())), glm::cos(glm::radians(bounds.y())), 0.0f);
        currentShader->setUniform("spotLights[" + std::to_string(i) + "].bounds", boundsData);
    }

    return 0;
}

void Scene::RenderRecursive(Transform* node) {
    Renderer* renderer = node->GetObject()->GetComponent<Renderer>();
    if (renderer != NULL) {
        renderer->Render();
    }
    for (int i = 0; i < node->GetChildCount(); i++) {
        RenderRecursive(node->GetChild(i));
    }
}

void Scene::Render() {
    RenderRecursive(sceneRoot_->GetTransform());
}

std::string Scene::GetName() {
    return name_;
}

void Scene::SetName(std::string name) {
    name_ = name;
}

Camera* Scene::GetActiveCamera() {
    return activeCamera_;
}

void Scene::SetActiveCamera(Camera* camera) {
    activeCamera_ = camera;
}