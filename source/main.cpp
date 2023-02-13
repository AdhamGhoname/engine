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

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

float* sphereVerts;

unsigned int VAO[2];
Shader lightSourceShader = Shader();
Shader phongLightShader = Shader();
unsigned int textureID[2];

float lastTime;
float deltaTime;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f),
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
	//cout << "Resizing to: " << width << " x " << height << "\n";
	glViewport(0, 0, width, height);
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

void generate_sphere_mesh(float radius, int sectorCount, int stackCount, float** dest)
{
	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	constexpr float PI = glm::pi<float>();
	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	vector<glm::vec3> vertices, normals;
	vector<glm::vec2> texCoords;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices.push_back(glm::vec3(x, y, z));

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(glm::vec3(nx, ny, nz));

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			texCoords.push_back(glm::vec2(s, t));
		}
	}

	float* points = new float[vertices.size()*3 + normals.size() * 3 + texCoords.size() * 2];
	for (int i = 0; i < vertices.size(); i += 8)
	{
		points[i] = vertices[i / 8].x;
		points[i+1] = vertices[i / 8].y;
		points[i+2] = vertices[i / 8].z;
	}

	for (int i = 3; i < normals.size(); i += 8)
	{
		points[i] = vertices[(i - 3) / 8].x;
		points[i+1] = vertices[(i - 3) / 8].y;
		points[i+2] = vertices[(i - 3) / 8].z;
	}

	for (int i = 6; i < texCoords.size(); i += 8)
	{
		points[i] = vertices[(i - 6) / 8].x;
		points[i + 1] = vertices[(i - 6) / 8].y;
	}
	*dest = points;
}

void init()
{
	glGenVertexArrays(2, VAO);

	unsigned int VBO[2];
	glGenBuffers(2, VBO);
	phongLightShader = Shader("../shaders/phong.vert", "../shaders/phong.frag");

	// Phong shaded objects

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

	glGenTextures(2, textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	unsigned char* data = stbi_load("../textures/container.jpg", &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Couldn't load texture image." << endl;
	}
	stbi_image_free(data);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("../textures/awesomeface.png", &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Couldn't load texture image." << endl;
	}
	stbi_image_free(data);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// light source
	generate_sphere_mesh(1.5f, 20, 20, &sphereVerts);
	for (int i = 0; i < 10; i++)
	{
		cout << sphereVerts[100+i] << endl;
	}
	lightSourceShader = Shader("../shaders/lightSource.vert", "../shaders/lightSource.frag");

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphereVerts), sphereVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	lastTime = glfwGetTime();
}


void render()
{
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();


	glBindVertexArray(VAO[0]);

	phongLightShader.use();
	phongLightShader.setUniform("sampler1", 0);
	phongLightShader.setUniform("sampler2", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureID[1]);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, -0.5f, 1.0f));
	model = glm::rotate(model, glm::radians(20.0f) * (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 proj = camera.GetProjectionMatrix();

	phongLightShader.setUniform("Model", model);
	phongLightShader.setUniform("View", view);
	phongLightShader.setUniform("Projection", proj);
	phongLightShader.setUniform("Normal", glm::mat3(glm::transpose(glm::inverse(model))));
	phongLightShader.setUniform("lightColor", glm::vec3(1.0f));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(VAO[1]);

	lightSourceShader.use();
	glm::vec3 lightPosition(0.0f, 0.0f, 0.0f);
	phongLightShader.setUniform("lightPosition", lightPosition);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, 0));
	view = camera.GetViewMatrix();
	proj = camera.GetProjectionMatrix();

	lightSourceShader.setUniform("Model", model);
	lightSourceShader.setUniform("View", view);
	lightSourceShader.setUniform("Projection", proj);
	lightSourceShader.setUniform("Normal", glm::mat3(glm::transpose(glm::inverse(model))));
	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, 120);
}



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
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
    cout << "here" << endl;

	int VertAttrCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &VertAttrCount);
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetScrollCallback(window, OnMouseScroll);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
