


#version 330 core
layout(location = 0) in vec4 color;
layout(location = 1) in vec2 pos;

out vec4 fcolor;

void main() {
    fcolor = color;
    gl_Position = vec4(pos, 0.0, 1.0);
}
