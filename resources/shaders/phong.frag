#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 vertPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
    vec3 ambient = 0.1f * lightColor * material.ambient;
    
	vec3 lightDirection = normalize(lightPosition - vertPosition);

	float diffuseIntensity = 0.5 * max(0.0f, dot(lightDirection, normal));
    
    vec3 diffuse = diffuseIntensity * material.diffuse;

	vec3 reflectedLightDirection = reflect(-lightDirection, normal);

	float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    
    vec3 specular = specularIntensity * material.specular;
    
    
    
	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
