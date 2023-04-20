#pragma once
#include "Scene.h"
class ShadowMapping :
    public Scene
{
public:
	void Load();
	void Render(Camera& camera, glm::mat4& projection, float delta);
	void CleanUp();

private:
	unsigned int depthMapFBO, depthMap;


	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
};

