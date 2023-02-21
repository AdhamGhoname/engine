#version 330 core
#define MAX_LIGHT_COUNT 32
#define MAX_TEXTURES_COUNT 4

out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 vertPosition;
in mat3 normal_mat;

struct Material {
    sampler2D diffuse[MAX_TEXTURES_COUNT];
    sampler2D specular[MAX_TEXTURES_COUNT];
    sampler2D normal;
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


uniform int dirLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLights[MAX_LIGHT_COUNT];
uniform PointLight pointLights[MAX_LIGHT_COUNT];
uniform SpotLight spotLights[MAX_LIGHT_COUNT];


vec3 sample_diffuse() {
    vec3 color = vec3(0.0f);
    float total_alpha = 1e-6;
    for (int i = 0; i < MAX_TEXTURES_COUNT; i++) {
        vec4 sample = texture(material.diffuse[i], uv);
        color += sample.rgb * sample.a;
        total_alpha += sample.a;
    }
    return color / total_alpha;
}

vec3 sample_specular() {
    vec3 color = vec3(0.0f);
    float total_alpha = 1e-6;
    for (int i = 0; i < MAX_TEXTURES_COUNT; i++) {
        vec4 sample = texture(material.specular[i], uv);
        color += sample.rgb * sample.a;
        total_alpha += sample.a;
    }
    return color / total_alpha;
}

vec3 sample_normal() {
    vec3 normal = vec3(texture(material.normal, uv));
    //vec3 normal = normalize(vec3(texture(material.normal, uv)));
    return normal;
}
vec3 dirLighting(DirectionalLight light) {
    vec3 direction = normalize(-light.direction);
    
    vec3 diffuse_color = sample_diffuse();
    vec3 specular_color = sample_specular();
    vec3 sampled_normal = sample_normal();
    
    // ambient
    vec3 ambient = light.ambient * diffuse_color;
    
    // diffuse
    float diffuseIntensity = max(0.0f, dot(direction, sampled_normal));
    vec3 diffuse = light.diffuse * diffuseIntensity * diffuse_color;
    
    //specular
    vec3 reflectedLightDirection = reflect(-direction, sampled_normal);
    float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    vec3 specular = light.specular * specularIntensity * specular_color;
    return ambient + diffuse + specular; 
}

vec3 pointLighting(PointLight light) {
    vec3 direction = light.position - vertPosition;
    float d = length(direction);
    direction /= d;
    float attenuation = 1.0f / dot(light.attenuation, vec3(1, d, d*d));
    
    vec3 diffuse_color = sample_diffuse();
    vec3 specular_color = sample_specular();
    vec3 sampled_normal = sample_normal();

    // ambient
    vec3 ambient = light.ambient * diffuse_color;
    
    // diffuse
    float diffuseIntensity = max(0.0f, dot(direction, sampled_normal));
    vec3 diffuse = light.diffuse * diffuseIntensity * diffuse_color;
    
    //specular
    vec3 reflectedLightDirection = reflect(-direction, sampled_normal);
    float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    vec3 specular = light.specular * specularIntensity * specular_color;
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
    
    vec3 diffuse_color = sample_diffuse();
    vec3 specular_color = sample_specular();
    vec3 sampled_normal = sample_normal();
    
    // ambient
    vec3 ambient = light.ambient * diffuse_color;
    
    // diffuse
    float diffuseIntensity = max(0.0f, dot(direction, sampled_normal));
    vec3 diffuse = light.diffuse * diffuseIntensity * diffuse_color;
    
    //specular
    vec3 reflectedLightDirection = reflect(-direction, sampled_normal);
    float specularIntensity = dot(normalize(cameraPosition - vertPosition), reflectedLightDirection);
    specularIntensity = max(0.0f, specularIntensity);
    specularIntensity = pow(specularIntensity, material.shininess);
    vec3 specular = light.specular * specularIntensity * specular_color;
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
//    if (length(color) < 0.35f) {
//        color = vec3(uv, 1.0f);
//    }
//    else {
//        color = vec3(0.1f);
//    }
    
	FragColor = vec4(color, 1.0);
}
