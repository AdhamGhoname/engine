#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 texCoords;


void main()
{
	vec4 pos = projection * view * vec4(aPos, 1.f);
	gl_Position = pos.xyww;
	texCoords = aPos;
}