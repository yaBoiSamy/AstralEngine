#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"

namespace Astral::Assets {

	class Material : public Asset {
	public:
		Material(std::string name, Shader* shader, glm::vec4 albedo, const Texture* albedo_texture = nullptr);
		void Bind() const;
		void SetAlbedo(glm::vec4 albedo, const Texture* albedo_texture);
	private:
		Shader* shader;
		const Texture* albedo_texture;
	};
}
