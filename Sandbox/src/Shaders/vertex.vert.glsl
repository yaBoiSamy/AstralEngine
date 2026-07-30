


#version 460 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

layout(std140, binding = 0) uniform Camera
{
    mat4 view;
    mat4 projection;
};

layout(std140, binding = 1) uniform Model
{
    mat4 model;
};

uniform vec4 nigger;

out vec4 fcolor;

void main() {
    fcolor = nigger;
    gl_Position = projection * view * model * vec4(pos, 1.0);
}
