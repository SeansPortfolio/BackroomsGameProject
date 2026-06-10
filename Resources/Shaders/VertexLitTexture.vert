#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

struct PointLight
{
    vec3 position;
    vec3 color;

    float radius;

    float constant;
    float linear;
    float exponent;
};

#define MAX_POINT_LIGHTS 4

// lighting colors
uniform vec3 viewPos; 
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec3 FragPos;

vec3 CalculatePointLight(PointLight light)
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color;

  	// diffuse 
    vec3 norm = normalize(aNormal);
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
   gl_Position = Projection * View * Model * vec4(aPos, 1.0);
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
   FragPos = vec3(Model * vec4(aPos, 1.0));

   vec3 result = vec3(0, 0, 0);

   for(int i = 0; i < MAX_POINT_LIGHTS; i++)
   {
       result += CalculatePointLight(pointLights[i]);
   }

   Color = result;
}