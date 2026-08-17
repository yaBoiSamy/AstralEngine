#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"
#include "Astral/Rendering/Material/Material.h"

namespace Astral::Assets {

	class Material : public Asset {
	public:
		Material(std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture = nullptr);
		Render::Material* GetRendererMaterial();
		void Bind() const;
		void SetAlbedo(glm::vec4 albedo, Texture* albedo_texture);
	private:
		Render::Material material;
	};
}
