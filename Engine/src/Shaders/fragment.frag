#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoords;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct MaterialPro{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;
uniform MaterialPro materialPro;

struct Light{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define CANT_POINT_LIGHT 4

uniform DirLight dirLight;
uniform PointLight pointLight[CANT_POINT_LIGHT];
//uniform PointLight pointLight;

uniform int type;

uniform Light light;

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalculateDirLightPro(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalculatePointLightPro(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{

    if(type == 0){

        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);
        
        vec3 result = vec3(0.0);
        result = CalculateDirLight(dirLight, norm, viewDir);

        for(int i=0;i<CANT_POINT_LIGHT;i++){
            result += CalculatePointLight(pointLight[i], norm, FragPos, viewDir);
        }

        //result += CalculatePointLight(pointLight, norm, FragPos, viewDir);

        FragColor = vec4(result, 1.0);

        //ambient
        //float ambienStrength = 0.1;
        //vec3 ambient = light.ambient * material.ambient;
        //
        ////diffuse
        //vec3 normal = normalize(Normal);
        //
        //vec3 lightDir = normalize(light.position - FragPos);
        ////vec3 lightDir = normalize(light.position - FragPos);
        ////vec3 lightDir = normalize(-light.direction);
        //
        //float diff = max(dot(normal, lightDir), 0.0);
        //vec3 diffuse = light.diffuse * (diff * material.diffuse);
        //
        ////specular
        //float specularStrength = 0.5;
        //vec3 viewDir = normalize(viewPos - FragPos);
        //vec3 reflectDir = reflect(-lightDir, normal);
        //
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        //vec3 specular = light.specular * (spec * material.specular);
        //
        //float theta = dot(lightDir, normalize(-light.direction));
        //float epsilon = light.cutOff - light.outerCutOff;
        //float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        //
        //diffuse *= intensity;
        //specular *= intensity;
        //
        ////attenuation
        //float distance = length(light.position - FragPos);
        //float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        //ambient *= attenuation;
        //diffuse *= attenuation;
        //specular *= attenuation;
        //
        //vec3 result = ambient + diffuse + specular;
        //FragColor = vec4(result, 1.0);

    } else if(type == 1){

        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);
        
        vec3 result = vec3(0.0);
        result = CalculateDirLightPro(dirLight, norm, viewDir);

        for(int i=0;i<CANT_POINT_LIGHT;i++){
            result += CalculatePointLightPro(pointLight[i], norm, FragPos, viewDir);
        }

        //result += CalculatePointLightPro(pointLight, norm, FragPos, viewDir);

        FragColor = vec4(result, 1.0);

        //ambient
        //float ambienStrength = 0.1;
        //vec3 ambient = light.ambient * vec3(texture(materialPro.diffuse, texCoords));;
        //
        ////diffuse
        //vec3 normal = normalize(Normal);
        //
        //vec3 lightDir = normalize(light.position - FragPos);
        ////vec3 lightDir = normalize(-light.direction);
        //
        //float diff = max(dot(normal, lightDir), 0.0);
        //vec3 diffuse = light.diffuse * diff * vec3(texture(materialPro.diffuse, texCoords));
        //
        ////specular
        //float specularStrength = 0.5;
        //vec3 viewDir = normalize(viewPos - FragPos);
        //vec3 reflectDir = reflect(-lightDir, normal);
        //
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        //vec3 specular = light.specular * spec * vec3(texture(materialPro.specular, texCoords));
        //
        ////attenuation
        //float distance = length(light.position - FragPos);
        //float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        //
        //ambient *= attenuation;
        //diffuse *= attenuation;
        //specular *= attenuation;
        //
        //vec3 result = ambient + diffuse + specular;
        ////FragColor = texture(mainTexture, texCoords) * vec4(result, 1.0);
        //FragColor = vec4(result, 1.0);
    }
    
}

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir){

    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){

    vec3 lightDir = normalize(light.position - fragPos);

    //diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalculateDirLightPro(DirLight light, vec3 normal, vec3 viewDir){

    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(materialPro.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(materialPro.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(materialPro.specular, texCoords));
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLightPro(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){

    vec3 lightDir = normalize(light.position - fragPos);

    //diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture(materialPro.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(materialPro.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(materialPro.specular, texCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}