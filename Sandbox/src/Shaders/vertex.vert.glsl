


#version 330 core
layout(location = 0) in float inX;
layout(location = 1) in float inY;
void main() {
    gl_Position = vec4(inX, inY, 0.0, 1.0);
}
