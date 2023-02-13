#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();

	void setUniform(const std::string& name, bool value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, glm::mat4 value) const;
	void setUniform(const std::string& name, glm::mat3 value) const;
	void setUniform(const std::string& name, glm::vec4 value) const;
	void setUniform(const std::string& name, glm::vec3 value) const;

private:
	void setupShader(const char* filename, GLenum shaderType, const char* shaderName, unsigned int* shaderID);
	bool readFile(const char* filepath, std::string& output);
};