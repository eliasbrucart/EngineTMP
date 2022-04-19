#version 330 core
in vec3 position;
in vec3 color;
in vec2 uv;
in vec3 aNormal;

out vec3 vertexColor;
out vec2 texCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

void main()
{
    vertexColor = color;
    texCoords = uv;
    gl_Position = projection * view * model * vec4(position, 1.0);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(position, 1.0));
}