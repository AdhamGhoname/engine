#version 330 core

in vec3 texCoords;

uniform samplerCube cubemap;

void main()
{
	gl_FragColor = texture(cubemap, texCoords);
}