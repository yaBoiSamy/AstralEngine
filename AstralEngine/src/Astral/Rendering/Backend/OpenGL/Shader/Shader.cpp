#include "Common.h"
#include "Shader.h"
#include <glad/glad.h>


namespace Astral::Render::OpenGL {

	GLenum ConvertFormat(AttributeFormat format) {
		switch (format) {
		case AttributeFormat::Float: return GL_FLOAT;
		case AttributeFormat::Double: return GL_DOUBLE;
		case AttributeFormat::Int: return GL_INT;
		case AttributeFormat::UInt: return GL_UNSIGNED_INT;
		case AttributeFormat::Bool: return GL_BOOL;
		default: AST_CORE_ASSERT(false, "Unrecognized attribute datatype"); return 0;
		}
	}

	Shader::Shader(VertexLayout interface, const std::string& vertex_src, const std::string& fragment_src) : shader_handle(glCreateProgram()) {

		// VAO INITIALIZATION

		glGenVertexArrays(1, &vao_handle);
		glBindVertexArray(vao_handle);

		for (const VertexAttribute& attribute : interface.attributes) {
			const uint32_t ATT_COUNT = 1;
			glVertexAttribFormat(
				attribute.location, 
				attribute.components,
				ConvertFormat(attribute.format),
				attribute.normalized,
				static_cast<GLint>(attribute.offset)
			);
			glEnableVertexAttribArray(attribute.location);
			glVertexAttribBinding(attribute.location, attribute.binding);
		}
		for (const VertexBinding& binding: interface.bindings)
			glVertexBindingDivisor(binding.location, binding.divisor);


		// SHADER INITIALIZATION

		GLuint vs = CompileShaderStage(GL_VERTEX_SHADER, vertex_src);
		GLuint fs = CompileShaderStage(GL_FRAGMENT_SHADER, fragment_src);

		if (vs == 0 || fs == 0) {
			glDeleteProgram(shader_handle);
			shader_handle = 0;
			AST_CORE_ASSERT(false, "Shader failure");
			return;
		}

		glAttachShader(shader_handle, vs);
		glAttachShader(shader_handle, fs);
		glLinkProgram(shader_handle);


#ifdef AST_DEBUG
		int result;
		glGetProgramiv(shader_handle, GL_LINK_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetProgramiv(shader_handle, GL_INFO_LOG_LENGTH, &length);
			std::string message = std::string(length, '\0');
			glGetProgramInfoLog(shader_handle, length, &length, message.data());
			AST_CORE_ASSERT(false, "Failed to link shader stages: {0}", message);
			glDeleteProgram(shader_handle);
			glDeleteShader(vs);
			glDeleteShader(fs);
			shader_handle = 0;
			return;
		}

		glValidateProgram(shader_handle);

		glGetProgramiv(shader_handle, GL_VALIDATE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetProgramiv(shader_handle, GL_INFO_LOG_LENGTH, &length);
			std::string message = std::string(length, '\0');
			glGetProgramInfoLog(shader_handle, length, &length, message.data());
			AST_CORE_ASSERT(false, "Failed to validate shader: {0}", message);
			glDeleteProgram(shader_handle);
			glDeleteShader(vs);
			glDeleteShader(fs);
			shader_handle = 0;
			return;
		}
#endif

		glDetachShader(shader_handle, vs);
		glDetachShader(shader_handle, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	Shader::~Shader() {
		if (shader_handle != 0) {
			glDeleteProgram(shader_handle);
			glDeleteVertexArrays(1, &vao_handle);
		}
	}


	GLuint Shader::CompileShaderStage(uint32_t type, const std::string& src) {
		GLuint shaderStageHandle = glCreateShader(type);
		const char* rawsrc = src.data();
		glShaderSource(shaderStageHandle, 1, &rawsrc, nullptr);
		glCompileShader(shaderStageHandle);

#ifdef AST_DEBUG
		int result;
		glGetShaderiv(shaderStageHandle, GL_COMPILE_STATUS, &result);
		if (result == 0) {
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


	void Shader::Bind() const {
		glUseProgram(shader_handle);
		glBindVertexArray(vao_handle);
	}
}