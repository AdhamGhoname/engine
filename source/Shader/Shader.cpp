#include "Shader.h"
#include <iostream>
using namespace std;


bool Shader::readFile(const char* filepath, string& output)
{
	ifstream fs(filepath);
	//fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		stringstream buffer;
		buffer << fs.rdbuf();
		output = buffer.str();
		return true;
	}
	catch (ifstream::failure e)
	{
		cout << "Failed to read shader file " << filepath << endl;
	}
	return false;
}

void Shader::setupShader(const char* filename, GLenum shaderType, const char* shaderName, unsigned int* shaderID)
{

	string shader_string;
	if (!readFile(filename, shader_string))
	{
		return;
	}

	const char* shaderContent = shader_string.c_str();

	*shaderID = glCreateShader(shaderType);
	glShaderSource(*shaderID, 1, &shaderContent, NULL);
	glCompileShader(*shaderID);

	int success;
	char infoLog[512];
	glGetShaderiv(*shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(*shaderID, 512, NULL, infoLog);
		cout << "Failed to compile shader: " << shaderName << "!\n";
		cout << infoLog << "\n";
	}
}

Shader::Shader()
{
	this->ID = -1;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	unsigned int vertex_shader, fragment_shader;

	setupShader(vertexPath, GL_VERTEX_SHADER, "Vertex Shader", &vertex_shader);
	setupShader(fragmentPath, GL_FRAGMENT_SHADER, "Fragment Shader", &fragment_shader);

	this->ID = glCreateProgram();

	glAttachShader(this->ID, vertex_shader);
	glAttachShader(this->ID, fragment_shader);
	glLinkProgram(this->ID);

	int success;
	char infoLog[512];

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
		cout << "Failed to link shader program!\n";
		cout << infoLog << "\n";
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setUniform(const string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setUniform(const string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setUniform(const string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setUniform(const string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const string& name, glm::mat3 value) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}


void Shader::setUniform(const string& name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}
