#pragma once
#include "Common.h"
#include "Astral/Rendering/Shader/Shader.h"
#include "Astral/Rendering/Texture/Texture.h"

namespace Astral {

	class Material {
	public:
		Material(const Shader* shader, glm::vec4 albedo, const Texture* albedo_texture = nullptr);
		void Bind() const;
		const Shader& GetShader() const;
		const Texture* albedo_texture;
	private:
		const Shader* shader;
	};
}
