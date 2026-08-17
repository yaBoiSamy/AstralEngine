#include "Common.h"
#include "Material.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"


namespace Astral::Assets {

	Material::Material(std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture) : 
		Asset(name), 
		material(shader->GetRendererShader(), albedo, albedo_texture->GetRendererTexture()) {}

	Render::Material* Material::GetRendererMaterial() {
		return &material;
	}

	void Material::Bind() const {
		material.Bind();
	}

	void Material::SetAlbedo(glm::vec4 albedo, Texture* albedo_texture) {
		material.SetAlbedo(albedo, albedo_texture->GetRendererTexture());
	}
}