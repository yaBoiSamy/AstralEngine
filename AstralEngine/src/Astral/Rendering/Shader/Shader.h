#pragma once

#include "Common.h"
#include <glad/glad.h>

namespace Astral
{
	class Shader {
	public:
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		~Shader();
		void Bind() const;
	private:
		typedef uint32_t ShaderStageHandle;
		typedef uint32_t ShaderHandle;

		std::string StringifyShaderStage(const std::string& filepath);
		ShaderStageHandle CompileShaderStage(uint32_t type, const std::string& src);

		ShaderHandle shaderHandle;
	};
}