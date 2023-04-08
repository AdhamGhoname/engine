#include "Engine.h"
#include "../Camera/Camera.h"
#include <iostream>

Engine::Engine() {
	activeScene_ = NULL;
	windowWidth_ = 0;
	windowHeight_ = 0;
	lastFrameTime_ = -1;
	deltaTime_ = 0;
	activeWindow_ = NULL;
	initialized_ = false;
}

Engine* Engine::GetInstance() {
	if (Engine::instance_ == NULL) {
		Engine::instance_ = new Engine();
	}
	return Engine::instance_;
}

void Engine::Initialize(int winWidth, int winHeight) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	windowWidth_ = winWidth;
	windowHeight_ = winHeight;
	
	std::string windowName = activeScene_ ? activeScene_->GetName() : "Untitled";
	activeWindow_ = glfwCreateWindow(windowWidth_, windowHeight_, windowName.c_str(), NULL, NULL);

	if (!activeWindow_)
	{
		std::cerr << "Failed to create GLFW window\n";
		return;
	}

	glfwMakeContextCurrent(activeWindow_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		return;
	}

	if (!activeScene_) {
		std::cerr << "No active scene. Failed to initialize.\n";
		return;
	}

	if (!activeScene_->GetActiveCamera()) {
		std::cerr << "Active scene has no camera. Failed to initialize.\n";
		return;
	}

	glViewport(0, 0, windowWidth_, windowHeight_);
	glfwSetFramebufferSizeCallback(activeWindow_, [](GLFWwindow* window, int width, int height) {
		instance_->OnScreenResize(window, width, height);
	});

	glfwSetCursorPosCallback(activeWindow_, [](GLFWwindow* window, double x, double y) {
		instance_->OnMouseMove(window, x, y);
	});

	glfwSetScrollCallback(activeWindow_, [](GLFWwindow* window, double x, double y) {
		instance_->OnMouseScroll(window, x, y);
	});

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_FRAMEBUFFER_SRGB);

	initialized_ = true;
}

void Engine::Run() {
	if (!initialized_) {
		return;
	}
	while (!glfwWindowShouldClose(activeWindow_))
	{
		ProcessInput();
		glClearColor(clearColor_.x(), clearColor_.y(), clearColor_.z(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();

		glfwPollEvents();
		glfwSwapBuffers(activeWindow_);
	}
}

void Engine::ProcessInput() {
	if (!initialized_) {
		return;
	}

	if (glfwGetKey(activeWindow_, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(activeWindow_, true);
	}

	Camera* camera = activeScene_->GetActiveCamera();
	if (!camera) {
		return;
	}

	if (glfwGetKey(activeWindow_, GLFW_KEY_W))
	{
		camera->TranslateRelative(glm::vec3(0.0f, 0.0f, -2.5f) * deltaTime_);
	}
	else if (glfwGetKey(activeWindow_, GLFW_KEY_A))
	{
		camera->TranslateRelative(glm::vec3(-2.5f, 0.0f, 0.0) * deltaTime_);
	}
	else if (glfwGetKey(activeWindow_, GLFW_KEY_S))
	{
		camera->TranslateRelative(glm::vec3(0.0f, 0.0f, 2.5f) * deltaTime_);
	}
	else if (glfwGetKey(activeWindow_, GLFW_KEY_D))
	{
		camera->TranslateRelative(glm::vec3(2.5f, 0.0f, 0.0) * deltaTime_);
	}
	else if (glfwGetKey(activeWindow_, GLFW_KEY_R))
	{
		camera->TranslateRelative(glm::vec3(0.0f, 2.0f, 0.0f) * deltaTime_);
	}
	else if (glfwGetKey(activeWindow_, GLFW_KEY_F))
	{
		camera->TranslateRelative(glm::vec3(0.0f, -2.0f, 0.0f) * deltaTime_);
	}
}

void Engine::Render() {
	if (!initialized_) {
		return;
	}
	lastFrameTime_ = glfwGetTime();
	activeScene_->Render();
	deltaTime_ = glfwGetTime() - lastFrameTime_;
}

void Engine::OnMouseMove(GLFWwindow* window, double x, double y) {
	Camera* camera = activeScene_->GetActiveCamera();
	camera->OnMouseMove(window, x, y);
}

void Engine::OnMouseScroll(GLFWwindow* window, double x, double y) {
	Camera* camera = activeScene_->GetActiveCamera();
	camera->OnMouseScroll(window, x, y);
}

void Engine::OnScreenResize(GLFWwindow* window, int winWidth, int winHeight) {
	Camera* camera = activeScene_->GetActiveCamera();
	windowWidth_ = winWidth;
	windowHeight_ = winHeight;
	glViewport(0, 0, windowWidth_, windowHeight_);
	camera->SetAspectRatio((float)windowWidth_ / windowHeight_);
}

Scene* Engine::GetActiveScene() {
	return activeScene_;
}

void Engine::SetActiveScene(Scene* scene) {
	activeScene_ = scene;
}

float Engine::GetDeltaTime() {
	return deltaTime_;
}

int Engine::GetWindowWidth() {
	return windowWidth_;
}

int Engine::GetWindowHeight() {
	return windowHeight_;
}

void Engine::SetClearColor(Vector3 color) {
	clearColor_ = color;
}

Engine::~Engine() {
	glfwTerminate();
	delete activeScene_;
	delete instance_;
}