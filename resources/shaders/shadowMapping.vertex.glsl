#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} vsOut;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main(){
	vec3 fragPos = vec3(model * vec4(aPos, 1.f));
	vsOut.FragPos = fragPos;
	vsOut.Normal = transpose(inverse(mat3(model))) * aNormal;
	vsOut.TexCoords = aTexCoords;
	vsOut.FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.f);
	gl_Position = projection * view * model * vec4(aPos, 1.f);
}