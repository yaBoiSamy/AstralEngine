#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral::Assets {

	class Material : public Asset {
	public:
		Material(std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture = nullptr);
		Render::ResourceHandle GetShaderHandle();
		Render::ResourceHandle GetAlbedoTextureHandle();
		void SetAlbedo(glm::vec4 albedo, Texture* albedo_texture = nullptr);

	private:
		Render::ResourceHandle shader_handle;
		glm::vec4 albedo;
		Render::ResourceHandle albedo_texture_handle;
	};
}