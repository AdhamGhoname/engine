#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light 
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient, specular, diffuse;
	float constant, quadratic, linear;
};

struct SpotLight
{
	vec3 position, direction;
	float cutoff, outerCutOff;

	vec3 ambient, specular, diffuse;
	float constant, quadratic, linear;
};

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform PointLight pointLight;
uniform SpotLight spotLight;



vec3 calcPointLight();
vec3 calcDirLight();
vec3 calcSpotLight();

void main()
{

	vec3 res = calcSpotLight();

	gl_FragColor = vec4(res, 1.f);
} 

vec3 calcDirLight()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCoords)));


	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoords)));

	return (ambient + diffuse + specular);
};

vec3 calcPointLight()
{
	vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, texCoords));

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(pointLight.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = pointLight.diffuse * (diff * vec3(texture(material.diffuse, texCoords)));


	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);
	vec3 specular = pointLight.specular * (spec * vec3(texture(material.specular, texCoords)));

	// attenuation
	float distance = length(pointLight.position - fragPos);
	float attenuation = 1.f / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;   


	return (ambient + diffuse + specular);
};

vec3 calcSpotLight()
{

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(spotLight.position - fragPos);
	float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon   = spotLight.cutoff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);	

	if(theta >spotLight.cutoff)
	{
		vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse, texCoords));

		float diff = max(dot(norm, lightDir), 0.f);
		vec3 diffuse = spotLight.diffuse * (diff * vec3(texture(material.diffuse, texCoords)));


		vec3 viewDir = normalize(viewPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);
		vec3 specular = spotLight.specular * (spec * vec3(texture(material.specular, texCoords)));

		diffuse  *= intensity;
		specular *= intensity;	

		// attenuation
		float distance    = length(spotLight.position - fragPos);
		float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));    
		ambient  *= attenuation; 
		diffuse   *= attenuation;
		specular *= attenuation;  

		return (ambient + diffuse + specular);
	}

	return spotLight.ambient * (vec3(texture(material.diffuse, texCoords)));
	
};