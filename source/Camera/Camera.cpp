#include "Camera.h"

Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    forward = glm::vec3(0.0f, 0.0f, 1.0f);
    projection = "persp";
    near = 0.1f;
    far = 1000.0f;
    fov = 60.0f;
    aspect_ratio = 16.0f / 9.0f;
    mouseSensitivity = 0.1f;
    eulerAngleLowerbound = -glm::vec3(glm::half_pi<float>(), glm::half_pi<float>(), 0.0f);
    eulerAngleUpperbound = glm::vec3(glm::half_pi<float>(), glm::half_pi<float>(), 0.0f);
}

Camera::Camera(glm::vec3 position,
            glm::vec3 forward,
            std::string projection,
            float near,
            float far,
            float fov,
            float aspect_ratio,
            float mouseSensitivity,
            glm::vec3 eulerAngleLowerbound,
            glm::vec3 eulerAngleUpperbound)
{
	this->position = position;
	this->forward = glm::normalize(forward);
	this->projection = projection;
	this->near = near;
	this->far = far;
	this->fov = fov;
	this->aspect_ratio = aspect_ratio;
	this->mouseSensitivity = mouseSensitivity;
	this->eulerAngleLowerbound = eulerAngleLowerbound;
	this->eulerAngleUpperbound = eulerAngleUpperbound;
	float pitch = glm::asin(this->forward.y);
	float yaw = glm::atan(this->forward.z / this->forward.x);
	this->eulerAngles = glm::vec3(pitch, yaw, 0.0f);
	this->moved = false;
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 right = glm::normalize(glm::cross(this->forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::vec3 up = glm::cross(right, this->forward);
	glm::mat4 lookAt = glm::lookAt(this->position, this->position - this->forward, up);
	return lookAt;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (this->projection == "persp") {
		return glm::perspective(this->fov, this->aspect_ratio, this->near, this->far);
	}
	else
	{
		return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, this->near, this->far);
	}
}

void Camera::LookAt(glm::vec3 target)
{
	this->forward = glm::normalize(target - this->position);
}

void Camera::SetEulerAngles(glm::vec3 eulerAngles)
{
	//eulerAngles = glm::min(this->eulerAngleUpperbound, eulerAngles);
	//eulerAngles = glm::max(this->eulerAngleLowerbound, eulerAngles);
	this->eulerAngles = eulerAngles;
	this->forward.x = glm::cos(eulerAngles.y) * glm::cos(eulerAngles.x);
	this->forward.y = glm::sin(eulerAngles.x);
	this->forward.z = glm::sin(eulerAngles.y) * glm::cos(eulerAngles.x);
}

void Camera::SetPitch(float pitch)
{
	this->SetEulerAngles(glm::vec3(pitch, this->eulerAngles.y, this->eulerAngles.z));
}

void Camera::SetYaw(float yaw)
{
	this->SetEulerAngles(glm::vec3(this->eulerAngles.x, yaw, this->eulerAngles.z));
}

void Camera::OffsetEulerAngles(glm::vec3 offset)
{
	this->SetEulerAngles(this->eulerAngles + offset);
}

void Camera::OffsetPitch(float offset)
{
	this->SetPitch(this->eulerAngles.x + offset);
}

void Camera::OffsetYaw(float offset)
{
	this->SetYaw(this->eulerAngles.y + offset);
}

void Camera::Translate(glm::vec3 offset)
{
	this->position += offset;
}

void Camera::TranslateRelative(glm::vec3 offset)
{
	this->position += glm::vec3(glm::inverse(this->GetViewMatrix()) * glm::vec4(offset, 0.0f));
}

void Camera::OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	if (!this->moved)
	{
		this->lastMousePos = glm::vec2(xpos, ypos);
		moved = true;
		return;
	}
	glm::vec2 current = glm::vec2(xpos, ypos);
	glm::vec2 offset = current - this->lastMousePos;
	//offset.y *= -1;

	offset *= this->mouseSensitivity / glm::pi<float>();
	this->OffsetEulerAngles(glm::vec3(offset.y, offset.x, 0));
	this->lastMousePos = current;
}

void Camera::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	float new_fov = this-> fov - yoffset * this->mouseSensitivity;
	this->fov = glm::max(glm::min(120.0f, new_fov), 1.0f);
} 
