#pragma once
#include "Common.h"
#include "Shader.h"

namespace Astral {
	class ShaderLibrary {
	public:
		ShaderLibrary() = default;
		void Load(std::string name, std::string_view vertex_shader_path, std::string_view fragment_shader_path);
		Shader* Get(std::string name) const;
	private:
		std::unordered_map<std::string, Arc<Shader>> shaders;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	inline void Astral::ShaderLibrary::Load(std::string name, std::string_view vertex_shader_path, std::string_view fragment_shader_path) {
		AST_CORE_ASSERT(!shaders.contains(name), "Shader library cannot contain two shaders with name {0}", name);
		shaders.emplace(name, std::make_shared<Shader>(name, vertex_shader_path, fragment_shader_path));
	}

	inline Shader* Astral::ShaderLibrary::Get(std::string name) const {
		AST_CORE_ASSERT(shaders.contains(name), "Shader {0} does not exist in the shader library", name);
		return shaders.at(name).get();
	}
}