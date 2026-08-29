#include "Common.h"
#include "Material.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"


namespace Astral::Assets {

	Material::Material(Render::Renderer* renderer, Texture* blank_texture, std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture) :
		Asset(name),
		renderer(renderer),
		shader_handle(shader->GetHandle()),
		blank_texture_handle(blank_texture->GetHandle()),
		material_uniform_buffer_handle(0)
	{
		AST_CORE_ASSERT(renderer, "Cannot create material without a valid renderer");
		material_uniform_buffer_handle = renderer->Command().CreateUniformBuffer(sizeof(MaterialData));
		SetAlbedo(albedo, albedo_texture);
	}

	Render::ResourceHandle Material::GetShaderHandle() const {
		return shader_handle;
	}

	Render::ResourceHandle Material::GetAlbedoTextureHandle() const {
		return albedo_texture_handle;
	}

	Render::ResourceHandle Material::GetMaterialDataHandle() const {
		return material_uniform_buffer_handle;
	}

	void Material::SetAlbedo(glm::vec4 albedo, Texture* albedo_texture) {
		this->albedo = albedo;
		albedo_texture_handle = albedo_texture ? albedo_texture->GetHandle() : blank_texture_handle;
		renderer->Command().WriteUniformBuffer(material_uniform_buffer_handle, ToBytes(std::make_unique<MaterialData>(MaterialData{ albedo })));
	}
}