


#version 460 core

in vec2 ftext_coord;

uniform sampler2D albedoTexture;

layout(location = 0) out vec4 color;

void main() {
	color = texture(albedoTexture, ftext_coord);
}
