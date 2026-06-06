#pragma once

#include "Common.h"
#include <glad/glad.h>

namespace Astral
{
	typedef uint32_t VertexBufferHandle;
	typedef uint32_t VertexLayoutHandle;
	typedef uint32_t IndexBufferHandle;
	typedef uint32_t ShaderHandle;
	typedef uint32_t ShaderProgramHandle;


	class GLSLCompiler {
	public:
		GLSLCompiler();
		ShaderProgramHandle CreateShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	private:
		std::string StringifyShader(const std::string& filepath);
		ShaderHandle CompileShader(uint32_t type, const std::string& src);
	};
}