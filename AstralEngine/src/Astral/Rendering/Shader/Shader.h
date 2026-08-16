#pragma once

#include "Common.h"
#include "Uniform.h"
#include <glad/glad.h>

namespace Astral::Render {

	class Shader {
	public:
		Shader(const std::string& vertex_src, const std::string& fragment_src);
		~Shader();
		void Bind() const;

		template <typename T>
		void CreateUniform(const std::string& name, const T& data);

		template <typename T>
		void CreateUniformArray(const std::string& name);

		template <typename T>
		void SetUniform(const std::string& name, const T& data) const;

		template <typename T>
		void SetUniformArray(const std::string& name, std::span<const T> data) const;

	private:
		typedef GLuint ShaderStageHandle;
		typedef GLuint ShaderHandle;

		ShaderStageHandle CompileShaderStage(uint32_t type, const std::string& src);

		ShaderHandle shaderHandle;
		std::unordered_map<std::string, UniformVariant> uniforms;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	inline Shader::Shader(const std::string& vertex_src, const std::string& fragment_src) : shaderHandle(glCreateProgram()) {

		ShaderStageHandle vs = CompileShaderStage(GL_VERTEX_SHADER, vertex_src);
		ShaderStageHandle fs = CompileShaderStage(GL_FRAGMENT_SHADER, fragment_src);

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

		// STANDARD UNIFORM CREATION
		this->CreateUniform<bool>("HAS_ALBEDO_TEXTURE", false);
		this->CreateUniform<glm::vec4>("ALBEDO", glm::vec4(1, 1, 1, 0));
	}

	inline Shader::~Shader() {
		glDeleteProgram(shaderHandle);
	}

	inline Shader::ShaderStageHandle Shader::CompileShaderStage(uint32_t type, const std::string& src) {
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
					AST_CORE_ASSERT(false, "Failed to compile shader stage: {0}", message);
					glDeleteShader(shaderStageHandle);
					return 0;
				}
		#endif

		return shaderStageHandle;
	}

	inline void Shader::Bind() const {
		glUseProgram(shaderHandle);
	}

	template <typename T>
	inline void Shader::CreateUniform(const std::string& name, const T& data) {
		AST_CORE_ASSERT(!uniforms.contains(name), "Uniform with identical name already exists");
		uniforms.emplace(name, Uniform<T>(name, shaderHandle));
		SetUniform<T>(name, data);
	}

	template <typename T>
	inline void Shader::CreateUniformArray(const std::string& name) {
		AST_CORE_ASSERT(!uniforms.contains(name), "Uniform with identical name already exists");
		uniforms.emplace(name, UniformArray<T>(name, shaderHandle));
	}

	template <typename T>
	inline void Shader::SetUniform(const std::string& name, const T& data) const {
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
	inline void Shader::SetUniformArray(const std::string& name, std::span<const T> data) const {
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