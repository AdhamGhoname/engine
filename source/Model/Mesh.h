#pragma once
#include <stdio.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../Shader/Shader.h"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec2 uv;
};

struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
private:
    unsigned int VAO, VBO, EBO;
    void init();
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    void render(Shader& shader);
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
};
