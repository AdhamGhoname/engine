#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragPath)
{
	id = glCreateProgram();

	GenShader(vertexPath, GL_VERTEX_SHADER);
	GenShader(fragPath, GL_FRAGMENT_SHADER);

	glLinkProgram(id); 
}

Shader::Shader(const std::string& vertexPath, const std::string& fragPath, std::string& geomPath)
{
	id = glCreateProgram();

	GenShader(vertexPath, GL_VERTEX_SHADER);
	GenShader(fragPath, GL_FRAGMENT_SHADER);
	GenShader(geomPath, GL_GEOMETRY_SHADER);

	glLinkProgram(id);
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::SetBool(const std::string& name, bool value)
{
	SetInt(name, (int)value);
}

void Shader::SetInt(const std::string& name, int value)
{
	int location = glGetUniformLocation(id, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetFloat(const std::string& name, float value)
{
	int location = glGetUniformLocation(id, name.c_str());
	glUniform1f(location, value);
}

void Shader::Set2Float(const std::string& name, float v1, float v2)
{
	int location = glGetUniformLocation(id, name.c_str());
	glUniform2f(location, v1, v2);
}

void Shader::Set3Float(const std::string& name, float v1, float v2, float v3)
{
	int location = glGetUniformLocation(id, name.c_str());
	glUniform3f(location, v1, v2, v3);
}

void Shader::SetVec2(const std::string& name, glm::vec2& value)
{
	Set2Float(name, value.x, value.y);
}

void Shader::SetVec3(const std::string& name, glm::vec3& value)
{
	Set3Float(name, value.x, value.y, value.z);
}

void Shader::SetMat4(const std::string& name, glm::mat4 value)
{
	int location = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::LoadShader(const std::string& path)
{
	std::ifstream file;
	std::stringstream buffer;
	std::string result;

	file.open(path);

	if (file.is_open())
	{
		buffer << file.rdbuf();
		result = buffer.str();
	}
	else
	{
		std::cout << "Error Loading Shader at path " << path << std::endl;
	}

	file.close();

	return result;

}

void Shader::GenShader(const std::string& path, unsigned int type)
{
	unsigned int shader = glCreateShader(type);
	int success;
	char infoLog[512];

	std::string shaderSrc = LoadShader(path);
	const char* src = shaderSrc.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Errror compiling Shader at " << path << "\n" << infoLog << std::endl;
	}

	glAttachShader(id, shader);


}
