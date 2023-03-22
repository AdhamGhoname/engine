#include "Object/Object.h"
#include "Object/Components/Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "Model/Model.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Engine/Engine.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


void main() {

	// create new scene
	Scene* scene = new Scene("engine test");

	// get engine instance and set active scene
	Engine* engine = Engine::GetInstance();
	engine->SetActiveScene(scene);


	// initialize engine
	engine->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);


	// create a backpack object and add renderer and model.
	Object* backpackObject = new Object(scene,
		Vector3::Zero(),
		Quaternion::Euler(0.0f, 45.0f, 0.0f));
	Model* backpackModel = new Model("resources/models/backpack/backpack.obj");
	Renderer* renderer = backpackObject->AddComponent<Renderer>();
	renderer->SetModel(backpackModel);

	// create lights
	DirectionalLight* directionalLight = new DirectionalLight(scene);
	PointLight* pointLight = new PointLight(scene, Vector3(1.0f, -1.0f, 1.0f));

	// create a perspective camera
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), // position
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