#include "Common.h"
#include "Material.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"


namespace Astral::Assets {

	Material::Material(std::string name, Shader* shader, glm::vec4 albedo, const Texture* albedo_texture) : Asset(name), shader(shader), albedo_texture(albedo_texture) {
		AST_CORE_ASSERT(shader, "shader cannot be null at material construction");
		shader->SetUniform<glm::vec4>("ALBEDO", albedo);
	}

	void Material::Bind() const {
		shader->SetUniform<bool>("HAS_ALBEDO_TEXTURE", static_cast<bool>(albedo_texture));
		shader->Bind();
		albedo_texture->Bind(0);
	}

	void Material::SetAlbedo(glm::vec4 albedo, const Texture* albedo_texture) {
		shader->SetUniform<glm::vec4>("ALBEDO", albedo);
		this->albedo_texture = albedo_texture;
	}
}