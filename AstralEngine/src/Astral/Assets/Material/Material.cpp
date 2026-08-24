#include "Common.h"
#include "Material.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"


namespace Astral::Assets {

	Material::Material(std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture) :
		Asset(name),
		shader_handle(shader->GetHandle()),
		albedo(albedo),
		albedo_texture_handle(albedo_texture ? albedo_texture->GetHandle() : 0) {}

	Render::ResourceHandle Material::GetShaderHandle() {
		return shader_handle;
	}

	Render::ResourceHandle Material::GetAlbedoTextureHandle() {
		return albedo_texture_handle;
	}

	void Material::SetAlbedo(glm::vec4 albedo, Texture* albedo_texture) {
		this->albedo = albedo;
		albedo_texture_handle = albedo_texture ? albedo_texture->GetHandle() : 0;
	}
}