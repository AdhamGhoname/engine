#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Scene/Scene.h"

class Engine {
private:
	static inline Engine* instance_;
	Engine();
	~Engine();
	bool initialized_;
	Scene* activeScene_;
	int windowWidth_;
	int windowHeight_;
	float lastFrameTime_;
	float deltaTime_;
	GLFWwindow* activeWindow_;
	Vector3 clearColor_;
	void ProcessInput();
	void Render();
	void OnMouseMove(GLFWwindow* window, double x, double y);
	void OnMouseScroll(GLFWwindow* window, double x, double y);
	void OnScreenResize(GLFWwindow* window, int width, int height);
public:
	void Initialize(int winWidth, int winHeight);
	void Run();

	Scene* GetActiveScene();
	void SetActiveScene(Scene* scene);
	float GetDeltaTime();
	int GetWindowWidth();
	int GetWindowHeight();
	void SetClearColor(Vector3 color);

	static Engine* GetInstance();
};