#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 vertPosition;

uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform vec3 lightColor;
uniform vec3 lightPosition;

void main()
{
	vec4 baseColor = mix(texture(sampler1, texCoord),
					texture(sampler2, texCoord),
					0.5f) * vec4(lightColor, 1.0f);
	float ambientIntensity = 0.1f;
	vec3 lightDirection = normalize(lightPosition - vertPosition);
	float diffuseIntensity = max(0.0f, dot(lightDirection, normal));
	vec3 reflectedLightDirection = reflect(lightDirection, normal);
	float specular = pow(dot(normalize(-vertPosition), normal), 32.0f);
	FragColor = (ambientIntensity + diffuseIntensity + specular) * baseColor;
}