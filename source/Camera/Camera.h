#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	float fov;
	float aspect_ratio;
	std::string projection;
	float near;
	float far;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 eulerAngles;
	glm::vec2 lastMousePos;
	glm::vec3 eulerAngleLowerbound;
	glm::vec3 eulerAngleUpperbound;
	float mouseSensitivity;
	bool moved;

public:
    Camera();
	Camera(glm::vec3 position,
		glm::vec3 forward,
		std::string projection,
		float near,
		float far,
		float fov,
		float aspect_ratio,
		float mouseSensitivity,
		glm::vec3 eulerAngleLowerbound,
		glm::vec3 eulerAngleUpperbound);

	void LookAt(glm::vec3 target);
	void SetEulerAngles(glm::vec3 eulerAngles);
	void SetPitch(float pitch);
	void SetYaw(float pitch);
	void OffsetEulerAngles(glm::vec3 offset);
	void OffsetPitch(float offset);
	void OffsetYaw(float offset);
	void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
	void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	void Translate(glm::vec3 offset);
	void TranslateRelative(glm::vec3 offset);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
};
