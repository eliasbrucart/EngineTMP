#version 330 core

uniform vec3 lightColor;

void main()
{
    gl_FragColor = vec4(lightColor, 1.0); // set all 4 vector values to 1.0
}