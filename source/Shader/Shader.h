#pragma once
#include "predefined.h"
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Math/MathCommons.h"
#include <unordered_map>

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
    void setUniform(const std::string& name, glm::mat3 value) const;
    void setUniform(const std::string& name, glm::mat4 value) const;
    
    void setUniform(const std::string& name, glm::vec2 value) const;
    void setUniform(const std::string& name, glm::vec3 value) const;
    void setUniform(const std::string& name, glm::vec4 value) const;

	void setUniform(const std::string& name, Vector2 value) const;
	void setUniform(const std::string& name, Vector3 value) const;
	void setUniform(const std::string& name, Vector4 value) const;

	static Shader* StandardShader();

private:
	static inline std::unordered_map<std::string, Shader*> predefined_shaders;
	void setupShader(const char* filename, GLenum shaderType, const char* shaderName, unsigned int* shaderID);
	bool readFile(const char* filepath, std::string& output);
};
