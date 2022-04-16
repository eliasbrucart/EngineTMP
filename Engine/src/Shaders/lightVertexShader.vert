#version 330 core
layout(location = 0) in vec3 position;

in vec3 color;

out vec3 lightColor;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

void main()
{
    lightColor = color;
    gl_Position = projection * view * model * vec4(position, 1.0);
}