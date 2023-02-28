#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Shader/Shader.h"
#include "Camera/Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <sstream>
#include "Model/Model.h"
#include "Object/Object.h"
#include "Object/Components/Transform/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

string join(string a, string b) {
    return a + b;
}

float cubeVerts[] = {
	// positions // normals // texture coords
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};

float* sphereVerts;

unsigned int VAO[2];
Shader lightSourceShader = Shader();
Shader standardShader = Shader();
unsigned int textureID[2];

Model backpack;

float lastTime;
float deltaTime;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			"persp",
			0.1f,
			1000.0f,
			45.0f,
			(float)WINDOW_WIDTH / WINDOW_HEIGHT,
			0.01f,
			-glm::vec3(glm::half_pi<float>(), glm::half_pi<float>(), 0.0f),
			glm::vec3(glm::half_pi<float>(), glm::half_pi<float>(), 0.0f));

void OnMouseMove(GLFWwindow* window, double x, double y)
{
	camera.OnMouseMove(window, x, y);
}

void OnMouseScroll(GLFWwindow* window, double x, double y)
{
	camera.OnMouseScroll(window, x, y);
}

unsigned int indices[] = 
{
	0, 1, 2,
	1, 2, 3,
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camera.SetAspectRatio((float)width / height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) 
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera.TranslateRelative(glm::vec3(0.0f, 0.0f, -2.5f) * deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera.TranslateRelative(glm::vec3(-2.5f, 0.0f, 0.0) * deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera.TranslateRelative(glm::vec3(0.0f, 0.0f, 2.5f) * deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D))
	{
		camera.TranslateRelative(glm::vec3(2.5f, 0.0f, 0.0) * deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_R))
	{
		camera.TranslateRelative(glm::vec3(0.0f, 2.0f, 0.0f) * deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_F))
	{
		camera.TranslateRelative(glm::vec3(0.0f, -2.0f, 0.0f) * deltaTime);
	}
}

vector<glm::vec3> lightPositions;

void init()
{
	glGenVertexArrays(2, VAO);
//
	unsigned int VBO[2];
	glGenBuffers(2, VBO);
	standardShader = Shader("resources/shaders/standard.vert", "resources/shaders/standard.frag");
    backpack = Model("resources/models/backpack/backpack.obj");
    for (int i = 0; i < 8; i++) {
        int signX = (i & 1) ? 1 : -1;
        int signY = ((i >> 1) & 1) ? 1 : -1;
        int signZ = ((i >> 2) & 1) ? 1 : -1;
        glm::vec3 position = glm::vec3(signX, signY, signZ) * 2.0f;
        lightPositions.push_back(position);
    }

	// light source
	lightSourceShader = Shader(("resources/shaders/lightSource.vert"), ("resources/shaders/lightSource.frag"));
//
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
//
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	lastTime = glfwGetTime();
}


void render()
{
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();

    glm::vec3 lightPosition = camera.GetPosition();
    glm::vec3 lightDirection = -camera.GetForward();

    standardShader.use();
    standardShader.setUniform("cameraPosition", camera.GetPosition());
    standardShader.setUniform("material.shininess", 32.0f);
    standardShader.setUniform("dirLightCount", 0);
    standardShader.setUniform("directionalLights[0].direction", glm::vec3(0.0f, 1.0f, -1.0f));
    standardShader.setUniform("directionalLights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    standardShader.setUniform("directionalLights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
    standardShader.setUniform("directionalLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
    
    standardShader.setUniform("directionalLights[1].direction", glm::vec3(0.0f, 1.0f, 0.0f));
    standardShader.setUniform("directionalLights[1].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    standardShader.setUniform("directionalLights[1].diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
    standardShader.setUniform("directionalLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
    
    standardShader.setUniform("pointLightCount", 8);
    for (int i = 0; i < 8; i++) {
        string prefix = "pointLights[" + to_string(i) + "]";
        standardShader.setUniform(prefix + ".position", lightPositions[i]);
        standardShader.setUniform(prefix + ".ambient", glm::vec3(0.2f));
        standardShader.setUniform(prefix + ".diffuse", glm::vec3(0.5f)); // darkened
        standardShader.setUniform(prefix + ".specular", glm::vec3(1.0f));
        standardShader.setUniform(prefix + ".attenuation", glm::vec3(1.0f, 0.09f, 0.032f));
    }

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 proj = camera.GetProjectionMatrix();
    standardShader.setUniform("View", view);
    standardShader.setUniform("Projection", proj);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,  glm::vec3(0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    standardShader.setUniform("Model", model);
    standardShader.setUniform("Normal", glm::mat3(glm::transpose(glm::inverse(model))));
    backpack.render(standardShader);

    glBindVertexArray(VAO[1]);
    lightSourceShader.use();
    for (int i = 0; i < 8; i++) {
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPositions[i]);
        lightModel = glm::scale(lightModel, glm::vec3(0.1f));
        lightSourceShader.setUniform("Model", lightModel);
        lightSourceShader.setUniform("View", view);
        lightSourceShader.setUniform("Projection", proj);
        lightSourceShader.setUniform("Normal", glm::mat3(glm::transpose(glm::inverse(model))));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Engine", NULL, NULL);
	if (!window)
	{
		cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
    
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD\n";
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	init();

	int VertAttrCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &VertAttrCount);
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetScrollCallback(window, OnMouseScroll);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
