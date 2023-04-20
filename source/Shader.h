#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragPath);
	Shader(const std::string& vertexPath, const std::string& fragPath, std::string& geomPath);
	void Use();
	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void Set2Float(const std::string& name, float v1, float v2);
	void Set3Float(const std::string& name, float v1, float v2, float v3);
	void SetVec2(const std::string& name, glm::vec2& value);
	void SetVec3(const std::string& name, glm::vec3& value);
	void SetMat4(const std::string& name, glm::mat4 value);

private:
	unsigned int id;
	std::string LoadShader(const std::string& path);
	void GenShader(const std::string& path, unsigned int type);
};

