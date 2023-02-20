#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 normal;
out vec2 uv;
out vec3 vertPosition;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat3 Normal;

void main()
{
	uv = aTexCoord;
	normal = Normal * aNormal;
	vertPosition = vec3(Model * vec4(aPos.xyz, 1.0));
	gl_Position = Projection * View * Model * vec4(aPos.xyz, 1.0);
}
