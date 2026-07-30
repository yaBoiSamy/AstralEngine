#pragma once

#include "Common.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Astral {

	// Providing a C++-friendly interface for the uniform writing functions
	template<typename T>
	inline void GLUniformWrite(GLint handle, std::span<const T> data) {
		AST_CORE_ASSERT(false, "Trying to write to a C++ type with no GLSL equivalent");
	}

	#define IMPLEMENT_GL_UNIFORM_WRITING(cpp_type, gl_write_func, ...) \
	template<> \
	inline void GLUniformWrite<cpp_type>(GLint handle, std::span<const cpp_type> data) { \
		AST_CORE_ASSERT(!data.empty(), "Cannot write empty uniform data"); \
		gl_write_func(handle, static_cast<GLsizei>(data.size()), __VA_ARGS__); \
	}

	IMPLEMENT_GL_UNIFORM_WRITING(float, glUniform1fv, data.data())
	IMPLEMENT_GL_UNIFORM_WRITING(glm::vec2, glUniform2fv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::vec3, glUniform3fv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::vec4, glUniform4fv, glm::value_ptr(data[0]))

	IMPLEMENT_GL_UNIFORM_WRITING(double, glUniform1dv, data.data())
	IMPLEMENT_GL_UNIFORM_WRITING(glm::dvec2, glUniform2dv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::dvec3, glUniform3dv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::dvec4, glUniform4dv, glm::value_ptr(data[0]))

	IMPLEMENT_GL_UNIFORM_WRITING(int32_t, glUniform1iv, data.data())
	IMPLEMENT_GL_UNIFORM_WRITING(glm::ivec2, glUniform2iv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::ivec3, glUniform3iv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::ivec4, glUniform4iv, glm::value_ptr(data[0]))

	IMPLEMENT_GL_UNIFORM_WRITING(uint32_t, glUniform1uiv, data.data())
	IMPLEMENT_GL_UNIFORM_WRITING(glm::uvec2, glUniform2uiv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::uvec3, glUniform3uiv, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::uvec4, glUniform4uiv, glm::value_ptr(data[0]))

	IMPLEMENT_GL_UNIFORM_WRITING(glm::mat2, glUniformMatrix2fv, GL_FALSE, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::mat3, glUniformMatrix3fv, GL_FALSE, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::mat4, glUniformMatrix4fv, GL_FALSE, glm::value_ptr(data[0]))

	IMPLEMENT_GL_UNIFORM_WRITING(glm::dmat2, glUniformMatrix2dv, GL_FALSE, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::dmat3, glUniformMatrix3dv, GL_FALSE, glm::value_ptr(data[0]))
	IMPLEMENT_GL_UNIFORM_WRITING(glm::dmat4, glUniformMatrix4dv, GL_FALSE, glm::value_ptr(data[0]))

	#undef IMPLEMENT_GL_UNIFORM_WRITING


	// C++ -> OpenGL type conversion
	template<typename T>
	struct GLNumericType;

    #define IMPLEMENT_GL_TYPE_CONVERSION(cpp_type, gl_type_enum)	\
	template<>														\
	struct GLNumericType<cpp_type> {								\
		static constexpr GLenum value = gl_type_enum;				\
	};

	IMPLEMENT_GL_TYPE_CONVERSION(int8_t, GL_BYTE)
	IMPLEMENT_GL_TYPE_CONVERSION(uint8_t, GL_UNSIGNED_BYTE)
	IMPLEMENT_GL_TYPE_CONVERSION(int16_t, GL_SHORT)
	IMPLEMENT_GL_TYPE_CONVERSION(uint16_t, GL_UNSIGNED_SHORT)
	IMPLEMENT_GL_TYPE_CONVERSION(int32_t, GL_INT)
	IMPLEMENT_GL_TYPE_CONVERSION(uint32_t, GL_UNSIGNED_INT)
	IMPLEMENT_GL_TYPE_CONVERSION(float, GL_FLOAT)
	IMPLEMENT_GL_TYPE_CONVERSION(double, GL_DOUBLE)

    #undef IMPLEMENT_GL_TYPE_CONVERSION

}