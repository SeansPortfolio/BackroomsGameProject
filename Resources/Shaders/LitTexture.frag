#version 330 core

out vec4 FragColor;

struct PointLight
{
    vec3 position;
    vec3 color;

    float radius;

    float constant;
    float linear;
    float exponent;
};

#define MAX_POINT_LIGHTS 2

in vec3 SurfaceNormal;  
in vec2 TexCoord;
in vec3 FragPos;  

// texture samplers
uniform sampler2D image;

// lighting colors
uniform vec3 viewPos; 
uniform PointLight pointLights[MAX_POINT_LIGHTS];

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
    vec4 objectColor = texture(image, TexCoord);
    vec3 result = vec3(0, 0, 0);

    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        result += CalculatePointLight(pointLights[i]);
    }

    FragColor = vec4(result, 1.0) * objectColor;
}