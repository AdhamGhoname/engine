#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat3 Normal;

void main()
{
	normal = Normal * normalize(aNormal);
	gl_Position = Projection * View * Model * vec4(aPos.xyz, 1.0);
}
