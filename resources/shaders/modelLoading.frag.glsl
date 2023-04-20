#version 330 core

struct PointLight
{
	vec3 position;

	vec3 ambient, specular, diffuse;
	float constant, quadratic, linear;
};

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;



uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform PointLight light;

uniform vec3 viewPos;
uniform float shininess;


vec3 calcPointLighting();

void main()
{
	gl_FragColor = vec4(calcPointLighting(), 1.0f);
}

vec3 calcPointLighting()
{
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, texCoords));

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(texture_diffuse1, texCoords)));


	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), shininess);
	vec3 specular = light.specular * (spec * vec3(texture(texture_specular1, texCoords)));

	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;   


	return (ambient + diffuse + specular);
};