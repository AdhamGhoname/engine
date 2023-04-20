#version 330 core

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} fsIn;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace) {
	
	// perform perspective-divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	projCoords = projCoords * 0.5f + 0.5f;
	
	float closestDepth = texture(shadowMap, projCoords.xy).r;

	float currentDepth = projCoords.z;

	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

	return shadow;
}

void main(){
	vec3 color = texture(diffuseTexture, fsIn.TexCoords).rgb;
	vec3 normal = normalize(fsIn.Normal);
	vec3 lightColor = vec3(1.f);

	// ambient
	vec3 ambient = 0.15f * lightColor;

	// diffusec
	vec3 lightDir = normalize(lightPos - fsIn.FragPos);
	float diff = max(dot(lightDir, normal), 0.f);
	vec3 diffuse = diff * lightColor;

	// specular 
	vec3 viewDir = normalize(viewPos - fsIn.FragPos);
	float spec = 0.f;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.f),65.f);
	vec3 specular = spec * lightColor;

	// calculate shadow\
	//float shadow = ShadowCalculation(fsIn.FragPosLightSpace);

	vec3 projCoords = fsIn.FragPosLightSpace.xyz / fsIn.FragPosLightSpace.w;

	projCoords = projCoords * 0.5f + 0.5f;
	
	float closestDepth = texture(shadowMap, projCoords.xy).r;

	float currentDepth = projCoords.z;

	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

	gl_FragColor = vec4(lighting, 1.f);
	gl_FragColor =  vec4(shadow, 0.f, 0.f, 1.f);
}