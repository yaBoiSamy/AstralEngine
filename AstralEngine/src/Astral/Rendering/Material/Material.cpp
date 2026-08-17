#include "Common.h"
#include "Material.h"

#include "Astral/Rendering/Shader/Shader.h"
#include "Astral/Rendering/Texture/Texture.h"


namespace Astral::Render {
	Material::Material(Shader* shader, glm::vec4 albedo, Texture* albedo_texture) : shader(shader), albedo(albedo), albedo_texture(albedo_texture) {
		AST_CORE_ASSERT(shader, "shader cannot be null at material construction");
	}

	void Material::Bind() const {
		shader->SetUniform<glm::vec4>("AST_ALBEDO", albedo);
		shader->SetUniform<bool>("AST_HAS_ALBEDO_TEXTURE", static_cast<bool>(albedo_texture));
		shader->Bind();
		albedo_texture->Bind(albedo_binding_slot);
	}

	void Material::SetAlbedo(glm::vec4 albedo, Texture* albedo_texture) {
		shader->SetUniform<glm::vec4>("ALBEDO", albedo);
		this->albedo_texture = albedo_texture;
	}
}
