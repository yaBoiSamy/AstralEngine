#include "Common.h"
#include "Shader.h"
#include <fstream>
#include <sstream>


namespace Astral::Assets {
	Shader::Shader(Render::Renderer* renderer, std::string name, Render::VertexLayout& layout, std::filesystem::path vertex_path, std::filesystem::path fragment_path)
		: Asset(name), renderer(renderer), shader_handle(renderer->Command().CreateShader(layout, ParseShaderStageFile(vertex_path), ParseShaderStageFile(fragment_path))) {}

	Render::ResourceHandle Shader::GetHandle() const {
		return shader_handle;
	}

	std::string ParseShaderStageFile(std::filesystem::path path) {
		std::ifstream file = std::ifstream(path, std::ios::in);
		AST_CORE_ASSERT(file.is_open(), "Shader path invalid: {0}", (std::filesystem::current_path() / path).string());

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string src = buffer.str();
		AST_CORE_ASSERT(src != "", "Shader stage failed to load for shader path {0}", (std::filesystem::current_path() / path).string());
		return src;
	}
}