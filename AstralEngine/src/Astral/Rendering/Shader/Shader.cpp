#include "Common.h"
#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <filesystem>


namespace Astral
{
	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) : shaderHandle(glCreateProgram()) {
		std::string vert_shader = StringifyShaderStage(vertexShaderPath);
		std::string frag_shader = StringifyShaderStage(fragmentShaderPath);
		AST_CORE_ASSERT(vert_shader != "", "Vertex shader path invalid: {0}", std::filesystem::current_path().append(vertexShaderPath).string());
		AST_CORE_ASSERT(frag_shader != "", "Fragment shader path invalid: {0}", std::filesystem::current_path().append(fragmentShaderPath).string());

		ShaderStageHandle vs = CompileShaderStage(GL_VERTEX_SHADER, StringifyShaderStage(vertexShaderPath));
		ShaderStageHandle fs = CompileShaderStage(GL_FRAGMENT_SHADER, StringifyShaderStage(fragmentShaderPath));

		if (vs == 0 || fs == 0) {
			glDeleteProgram(shaderHandle);
			shaderHandle = 0;
			return;
		}

		glAttachShader(shaderHandle, vs);
		glAttachShader(shaderHandle, fs);
		glLinkProgram(shaderHandle);


		#ifdef AST_DEBUG
		int result;
		glGetProgramiv(shaderHandle, GL_LINK_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetProgramiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
			std::string message = std::string(length, '\0');
			glGetProgramInfoLog(shaderHandle, length, &length, message.data());
			AST_CORE_ASSERT(false, "Failed to link shader stages: {0}", message);
			glDeleteProgram(shaderHandle);
			glDeleteShader(vs);
			glDeleteShader(fs);
			shaderHandle = 0;
			return;
		}

		glValidateProgram(shaderHandle);

		glGetProgramiv(shaderHandle, GL_VALIDATE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetProgramiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
			std::string message = std::string(length, '\0');
			glGetProgramInfoLog(shaderHandle, length, &length, message.data());
			AST_CORE_ASSERT(false, "Failed to validate shader: {0}", message);
			glDeleteProgram(shaderHandle);
			glDeleteShader(vs);
			glDeleteShader(fs);
			shaderHandle = 0;
			return;
		}
		#endif

		glDetachShader(shaderHandle, vs);
		glDetachShader(shaderHandle, fs);
	}

	Shader::~Shader() {
		glDeleteProgram(shaderHandle);
	}

	Shader::ShaderStageHandle Shader::CompileShaderStage(uint32_t type, const std::string& src) {
		ShaderStageHandle shaderStageHandle = glCreateShader(type);
		const char* rawsrc = src.c_str();
		glShaderSource(shaderStageHandle, 1, &rawsrc, nullptr);
		glCompileShader(shaderStageHandle);

		#ifdef AST_DEBUG
			int result;
			glGetShaderiv(shaderStageHandle, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				int length;
				glGetShaderiv(shaderStageHandle, GL_INFO_LOG_LENGTH, &length);
				std::string message = std::string(length, '\0');
				glGetShaderInfoLog(shaderStageHandle, length, &length, message.data());
				AST_CORE_ASSERT(false, "Failed to compile shader: {0}", message);
				glDeleteShader(shaderStageHandle);
				return 0;
			}
		#endif

		return shaderStageHandle;
	}

	std::string Shader::StringifyShaderStage(const std::string& path)
	{
		std::ifstream file = std::ifstream(path, std::ios::in);
		std::stringstream buffer;

		buffer << file.rdbuf();
		return buffer.str();
	}

	void Shader::Bind() const {
		glUseProgram(shaderHandle);
	}
}