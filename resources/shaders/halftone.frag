#version 330 core
#define MAX_LIGHT_COUNT 32
#define MAX_TEXTURES_COUNT 4

out vec4 FragColor;

in vec3 normal;
in vec3 vertPosition;
in mat3 normal_mat;
in mat3 TBN;
uniform sampler2D halftoneTexture;

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

uniform vec3 cameraPosition;


uniform int dirLightCount;
uniform int pointLightCount;
uniform int spotLightCount;
uniform vec3 resolution;

uniform DirectionalLight directionalLights[MAX_LIGHT_COUNT];
uniform PointLight pointLights[MAX_LIGHT_COUNT];
uniform SpotLight spotLights[MAX_LIGHT_COUNT];


vec3 getBackgroundColor(vec2 uv) {
    return mix(vec3(0.0f, 0.25f, 0.28f), vec3(0.0f, 0.30f, 0.33f), 1.0f - pow(dot(abs(uv), vec2(1.0f)), 1.0f));
}

vec3 dirLighting(DirectionalLight light, vec2 uv) {
    vec3 direction = normalize(-light.direction);    
    
    float intensity = dot(direction, normal);
    intensity = (intensity + 1.0f) / 2.0f;

    float halfToneValue = texture(halftoneTexture, uv).r;
    float tint = step(halfToneValue, intensity + 0.15f);
    return mix(getBackgroundColor(uv), vec3(1.0f), tint);
}

void main()
{
    vec2 uv = (2.0 * gl_FragCoord.xy - resolution.xy) / resolution.y;;
	vec3 color = vec3(0.0f);
    for (int i = 0; i < dirLightCount; i++) {
        color += dirLighting(directionalLights[i], uv);
    }
    FragColor = vec4(color, 1.0f);
}