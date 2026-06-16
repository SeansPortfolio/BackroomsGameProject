#version 330 core

out vec4 FragColor;



// point lights
struct PointLight
{
    vec3 position;
    vec3 color;

    float radius;

    float constant;
    float linear;
    float exponent;
};


struct SpotLight 
{
    vec3 position;
    vec3 direction;
    vec3 color;      

    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
};


#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 4

in vec3 SurfaceNormal;  
in vec2 TexCoord;
in vec3 FragPos;  

// texture samplers
uniform sampler2D BaseTexture;

// lighting colors
uniform int TotalSpotLights;
uniform int TotalPointLights;

uniform vec3 viewPos;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

vec3 CalculateSpotLight(SpotLight light)
{
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
     
    // diffuse shading
    float diff = max(dot(SurfaceNormal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, SurfaceNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);

    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));   
    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // combine results
    
    vec3 ambient = light.color;

    ambient *= attenuation * intensity;
    return (ambient);
}

vec3 CalculatePointLight(PointLight light)
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color;

  	// diffuse 
    vec3 norm = normalize(SurfaceNormal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;
    
    float length = distance(FragPos, light.position);

    if(length <= light.radius)
    {
        return (ambient + diffuse + specular);
    }
    else
    {
        length = length - light.radius;

        float attenuation = 1.0f /
            (light.constant +
            light.linear * length +
            light.exponent * length * length);

        return (ambient + diffuse + specular) * attenuation;
    }
}

void main()
{
    // texture
    vec4 objectColor = texture(BaseTexture, TexCoord);
    vec3 result = vec3(0, 0, 0);

    for(int i = 0; i < TotalPointLights && i < MAX_POINT_LIGHTS; i++)
    {
        result += CalculatePointLight(pointLights[i]);
    }
    
    for(int i = 0; i < TotalSpotLights && i < MAX_SPOT_LIGHTS; i++)
    {
        result += CalculateSpotLight(spotLights[i]);
    }

    FragColor = vec4(result, 1.0) * objectColor;
}