#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 text_coord;

// layout(std140, binding = 0) uniform Viewport
// {
//     uint width;
//     uint height;
// };

// layout(std140, binding = 1) uniform Lighting
// {
// };

layout(std140, binding = 2) uniform Camera
{
    mat4 view;
    mat4 projection;
    mat4 projection_view;
    mat4 inverse_projection_view;
};

layout(std140, binding = 3) uniform Model
{
    mat4 model;
};


out vec2 ftext_coord;

void main() {
    ftext_coord = text_coord;
    gl_Position = projection_view * model * vec4(pos, 1.0);
}
