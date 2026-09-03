#version 460 core

in vec2 ftext_coord;

layout(binding = 0) uniform sampler2D albedoTexture;

layout(std140, binding = 4) uniform Material
{
    vec4 albedo;
};

layout(location = 0) out vec4 color;

void main() {
	color = texture(albedoTexture, ftext_coord) * albedo;
}
