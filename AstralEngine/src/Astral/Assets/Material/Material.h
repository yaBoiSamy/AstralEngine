#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral::Assets {

	struct MaterialData {
		glm::vec4 albedo;
	};

	class Material : public Asset {
	public:
		Material(Render::Renderer* renderer, Texture* blank_texture, std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture);
		Render::ResourceHandle GetShaderHandle() const;
		Render::ResourceHandle GetAlbedoTextureHandle() const;	
		Render::ResourceHandle GetMaterialDataHandle() const;
		void SetAlbedo(glm::vec4 albedo, Texture* albedo_texture);

	private:
		Render::Renderer* renderer;
		Render::ResourceHandle shader_handle;
		Render::ResourceHandle blank_texture_handle;
		glm::vec4 albedo;
		Render::ResourceHandle albedo_texture_handle;
		Render::ResourceHandle material_uniform_buffer_handle;
	};
}