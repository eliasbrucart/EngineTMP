#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    float ambienStrength = 0.1;
    vec3 ambient = ambienStrength * lightColor;
    vec3 result = ambient * objectColor;
    gl_FragColor = vec4(result, 1.0);
}