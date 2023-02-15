#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 vertPosition;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform vec3 cameraPosition;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));   
    
	vec3 lightDirection = normalize(-light.direction);

	float diffuseIntensity = max(0.0f, dot(lightDirection, normal));
    
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse, texCoord));

	vec3 reflectedLightDirection = reflect(-lightDirection, normal);

	float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    
    vec3 specular = light.specular * specularIntensity * vec3(texture(material.specular, texCoord));
    
	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
