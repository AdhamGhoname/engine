#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;

out vec3 normal;
out vec2 uv;
out vec3 vertPosition;
out mat3 normal_mat;
out mat3 TBN;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat3 Normal;

void main()
{
	uv = aTexCoord;
	vec3 N = normalize(Model * vec4(aNormal, 0.0f)).xyz;
	vec3 T = normalize(Model * vec4(aTangent, 0.0f)).xyz;
	T = T - dot(T,N) * N;
	vec3 B = cross(T, N);
	TBN = mat3(T, B, N);

    normal_mat = Normal;
	vertPosition = vec3(Model * vec4(aPos.xyz, 1.0));
	gl_Position = Projection * View * Model * vec4(aPos.xyz, 1.0);
}
