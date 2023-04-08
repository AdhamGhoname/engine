#include "Object/Object.h"
#include "Object/Components/Renderer/Renderer.h"
#include "Object/Components/Transform/Transform.h"
#include "Scene/Scene.h"
#include "Model/Model.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Engine/Engine.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include <iostream>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

void main() {

	// create new scene
	Scene* scene = new Scene("engine test");

	// get engine instance and set active scene
	Engine* engine = Engine::GetInstance();
	engine->SetActiveScene(scene);
	engine->SetClearColor(Vector3(0.36f, 0.74f, 0.76f));


	// initialize engine
	engine->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);


	// create a backpack object and add renderer and model.
	//Model* backpackModel = new Model("resources/models/backpack/backpack.obj");
	Model* octaneModel = new Model("resources/models/octane/source/Octane.fbx");
	Model* ballModel = new Model("resources/models/ball/source/rocket ball.fbx");
	Model* pitchModel = new Model("resources/models/pitch/source/ChampionsField-Prabhu-v01.fbx");

	Shader* halfToneShader = new Shader("resources/shaders/halftone.vert", "resources/shaders/halftone.frag");
	Vector3 resolution = Vector3(Engine::GetInstance()->GetWindowWidth(), Engine::GetInstance()->GetWindowHeight(), 0.0f);
	halfToneShader->use();
	halfToneShader->setUniform("resolution", resolution);
	unsigned int textureID = Model::TextureFromFile("resources/textures/halftone6.jpg", "");
	glActiveTexture(GL_TEXTURE26);
	glBindTexture(GL_TEXTURE_2D, textureID);
	halfToneShader->setUniform("halftoneTexture", 26);


	Object* octane = new Object(scene,
		Vector3::Zero(),
		Quaternion::Euler(-90.0f, 0.0f, 0.0f));

	octane->AddComponent<Renderer>()->SetModel(octaneModel);
	octane->GetComponent<Renderer>()->SetShader(halfToneShader);

	Object* ball = new Object(scene,
		Vector3(1.0f, 1.0f, 0.0f),
		Quaternion::Euler(90.0f, 45.0f, 90.0f),
		Vector3::One() * 0.5f);

	ball->AddComponent<Renderer>()->SetModel(ballModel);
	ball->GetComponent<Renderer>()->SetShader(halfToneShader);


	Object* pitch = new Object(scene,
		Vector3(0.0f, -1.0f, 0.0f),
		Quaternion::Euler(-90.0f, 0.0f, 0.0f));

	pitch->AddComponent<Renderer>()->SetModel(pitchModel);
	pitch->GetComponent<Renderer>()->SetShader(halfToneShader);


	// create lights
	DirectionalLight* directionalLight1 = new DirectionalLight(scene, Vector3(-2.0f, -1.0f, 1.0f));
	DirectionalLight* directionalLight2 = new DirectionalLight(scene, Vector3(2.0f, 1.0f, 1.0f));
	PointLight* pointLight = new PointLight(scene, Vector3(1.0f, -1.0f, 1.0f));

	// create a perspective camera
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 1.0f), // position
								glm::vec3(0.0f, 0.0f, 1.0f), // forward
								"persp", // projection
								0.1f, // near
								1000.0f, // far
								45.0f, // fov
								(float)WINDOW_WIDTH / WINDOW_HEIGHT, // aspect ratio
								0.01f, // mouse sensitivity
								-glm::vec3(glm::half_pi<float>(), glm::half_pi<float>(), 0.0f), // rotation bounds min
								glm::vec3(glm::half_pi<float>(), glm::half_pi<float>(), 0.0f)); // rotation bounds max

	scene->SetActiveCamera(camera);

	// run render loop
	engine->Run();
}