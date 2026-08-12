#include "Common.h"
#include "Material.h"

namespace Astral {
	Material::Material(Arc<Shader> shader, glm::vec4 albedo, const Texture* albedo_texture) : shader(shader), albedo_texture(albedo_texture) {
		AST_CORE_ASSERT(shader, "shader cannot be null at material construction");
		shader->SetUniform<glm::vec4>("ALBEDO", albedo);
	}

	void Material::Bind() const {
		shader->SetUniform<bool>("HAS_ALBEDO_TEXTURE", static_cast<bool>(albedo_texture));
		albedo_texture->Bind(0);
	}

	const Shader& Material::GetShader() const {
		return *shader;
	}
}