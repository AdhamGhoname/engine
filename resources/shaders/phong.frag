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

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 attenuation;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 attenuation;
    vec3 bounds;
};


uniform Material material;
uniform vec3 cameraPosition;

#define MAX_LIGHT_COUNT 32

uniform int dirLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLights[MAX_LIGHT_COUNT];
uniform PointLight pointLights[MAX_LIGHT_COUNT];
uniform SpotLight spotLights[MAX_LIGHT_COUNT];

vec3 dirLighting(DirectionalLight light) {
    vec3 direction = normalize(-light.direction);
    
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    
    // diffuse
    float diffuseIntensity = max(0.0f, dot(direction, normal));
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse, texCoord));
    
    //specular
    vec3 reflectedLightDirection = reflect(-direction, normal);
    float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    vec3 specular = light.specular * specularIntensity * vec3(texture(material.specular, texCoord));
    return ambient + diffuse + specular;
}

vec3 pointLighting(PointLight light) {
    vec3 direction = light.position - vertPosition;
    float d = length(direction);
    direction /= d;
    float attenuation = 1.0f / dot(light.attenuation, vec3(1, d, d*d));
    
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    
    // diffuse
    float diffuseIntensity = max(0.0f, dot(direction, normal));
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse, texCoord));
    
    //specular
    vec3 reflectedLightDirection = reflect(-direction, normal);
    float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    vec3 specular = light.specular * specularIntensity * vec3(texture(material.specular, texCoord));
    return (ambient + diffuse + specular) * attenuation;
}

vec3 spotLighting(SpotLight light) {
    vec3 direction = light.position - vertPosition;
    float d = length(direction);
    direction /= d;
    float attenuation = 1.0f / dot(light.attenuation, vec3(1, d, d*d));
    
    float costheta = dot(normalize(-light.direction), direction);
    float intensity = (light.bounds.y - costheta) / (light.bounds.y - light.bounds.x + 1e-6);
    intensity = clamp(intensity, 0.0f, 1.0f);
    
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    
    // diffuse
    float diffuseIntensity = max(0.0f, dot(direction, normal));
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse, texCoord));
    
    //specular
    vec3 reflectedLightDirection = reflect(-direction, normal);
    float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    vec3 specular = light.specular * specularIntensity * vec3(texture(material.specular, texCoord));
    return (ambient + diffuse + specular) * attenuation * intensity;
}

void main()
{
    vec3 color = vec3(0.0f);
    for (int i = 0; i < dirLightCount; i++) {
        color += dirLighting(directionalLights[i]);
    }
    for (int i = 0; i < pointLightCount; i++) {
        color += pointLighting(pointLights[i]);
    }
    for (int i = 0; i < spotLightCount; i++) {
        color += spotLighting(spotLights[i]);
    }
    
	FragColor = vec4(color, 1.0);
}
