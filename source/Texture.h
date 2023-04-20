#pragma once
#include <glad/glad.h>
#include "stb_image.h"

#include <string>
#include <iostream>

class Texture
{
public:
	Texture(const std::string& path);
	void Use();


private:
	unsigned int id;

	void LoadTexture(const std::string path);
};

