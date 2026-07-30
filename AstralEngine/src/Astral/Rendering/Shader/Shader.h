#pragma once

#include "Common.h"
#include "Uniform.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace Astral
{
	class Shader {
	public:
		Shader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		~Shader();
		void Bind() const;

		template <typename T>
		void CreateUniform(const std::string& name);

		template <typename T>
		void CreateUniformArray(const std::string& name);

		template <typename T>
		void SetUniform(const std::string& name, const T& data);

		template <typename T>
		void SetUniformArray(const std::string& name, std::span<const T> data);

	private:
		typedef GLuint ShaderStageHandle;
		typedef GLuint ShaderHandle;

		std::string StringifyShaderStage(std::string_view filepath);
		ShaderStageHandle CompileShaderStage(uint32_t type, std::string_view src);

		ShaderHandle shaderHandle;
		std::unordered_map<std::string, UniformVariant> uniforms;
	};



	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	inline Shader::Shader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath) : shaderHandle(glCreateProgram()) {
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

	inline Shader::~Shader() {
		glDeleteProgram(shaderHandle);
	}

	inline Shader::ShaderStageHandle Shader::CompileShaderStage(uint32_t type, std::string_view src) {
		ShaderStageHandle shaderStageHandle = glCreateShader(type);
		const char* rawsrc = src.data();
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

	inline std::string Shader::StringifyShaderStage(std::string_view path) {
		std::ifstream file = std::ifstream(std::string(path), std::ios::in);
		std::stringstream buffer;

		buffer << file.rdbuf();
		return buffer.str();
	}

	inline void Shader::Bind() const {
		glUseProgram(shaderHandle);
	}

	template <typename T>
	inline void Shader::CreateUniform(const std::string& name) {
		AST_CORE_ASSERT(!uniforms.contains(name), "Uniform with identical name already exists");
		uniforms.emplace(name, Uniform<T>(name, shaderHandle));
	}

	template <typename T>
	inline void Shader::CreateUniformArray(const std::string& name) {
		AST_CORE_ASSERT(!uniforms.contains(name), "Uniform with identical name already exists");
		uniforms.emplace(name, UniformArray<T>(name, shaderHandle));
	}

	template <typename T>
	inline void Shader::SetUniform(const std::string& name, const T& data) {
		AST_CORE_ASSERT(uniforms.contains(name), "Uniform {} does not exist", name);
		Bind();
		std::visit(
			[&](auto&& uniform) {
				using UniformT = std::decay_t<decltype(uniform)>;
				if constexpr (std::is_same_v <Uniform<T>, UniformT>) {
					uniform.Write(data);
				}
				else {
					if constexpr (std::is_same_v <UniformArray<T>, UniformT>) {
						AST_CORE_ERROR("Writing single-value data to array uniform {}", name);
					}
					else {
						AST_CORE_ERROR("Type mismatch between uniform {} and provided data", name);
					}
				}
			},
			uniforms.at(name)
		);
	}

	template <typename T>
	inline void Shader::SetUniformArray(const std::string& name, std::span<const T> data) {
		AST_CORE_ASSERT(uniforms.contains(name), "Uniform {} does not exist", name);
		Bind();
		std::visit(
			[&](auto&& uniform) {
				using UniformT = std::decay_t<decltype(uniform)>;
				if constexpr (std::is_same_v < UniformArray<T>, UniformT>) {
					uniform.Write(data);
				}
				else {
					if constexpr (std::is_same_v < Uniform<T>, UniformT>) {
						AST_CORE_ERROR("Writing array data to single-value uniform {}", name);
					}
					else {
						AST_CORE_ERROR("Type mismatch between uniform {} and provided data", name);
					}
				}
			},
			uniforms.at(name)
		);
	}
}