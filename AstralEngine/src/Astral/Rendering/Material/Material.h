#pragma once
#include "Astral/Rendering/Shader/Shader.h"
#include "Astral/Rendering/Texture/Texture.h"


namespace Astral::Render {

	class Material {
	public:
		Material(Shader* shader, glm::vec4 albedo, Texture* albedo_texture = nullptr);
		void Bind() const;
		void SetAlbedo(glm::vec4 albedo, Texture* albedo_texture);
	private:
		Shader* shader;

		glm::vec4 albedo;
		const uint32_t albedo_binding_slot = 0;
		Texture* albedo_texture;
	};
}
