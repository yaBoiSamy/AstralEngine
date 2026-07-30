#pragma once

#include "Common.h"
#include "Astral/Rendering/OpenGLTranslations.h"
#include <glad/glad.h>

namespace Astral {
	using namespace glm;

	template <typename FieldT>
	class Uniform {
	public:
		Uniform(std::string_view name, GLuint shaderid) : handle(glGetUniformLocation(shaderid, name.data())) {}

		// moving is supported
		Uniform(Uniform&& other) : handle(other.handle) {
			other.handle = 0;
		}
		Uniform& operator=(Uniform&& other) = default;

		// copying is not permitted
		Uniform(const Uniform&) = delete;
		Uniform& operator=(const Uniform&) = delete;

		void Write(const FieldT& data) {
			GLUniformWrite<FieldT>(handle, std::span<const FieldT>(&data, 1));
		}

	private:
		GLint handle;
	};


	template <typename FieldT>
	class UniformArray {
	public:
		UniformArray(std::string name, uint32_t shaderid) : handle(glGetUniformLocation(shaderid, name)) {}

		// moving is supported
		UniformArray(UniformArray&& other) : handle(other.handle) {
			other.handle = 0;
		}
		UniformArray& operator=(UniformArray&& other) = default;

		// copying is not permitted
		UniformArray(const UniformArray&) = delete;
		UniformArray& operator=(const UniformArray&) = delete;

		void Write(std::span<const FieldT> data) {
			GLUniformWrite<FieldT>(handle, data);
		}

	private:
		GLint handle;
	};


	using UniformVariant = std::variant <
		Uniform<float>,
		Uniform<glm::vec2>,
		Uniform<glm::vec3>,
		Uniform<glm::vec4>,

		Uniform<double>,
		Uniform<glm::dvec2>,
		Uniform<glm::dvec3>,
		Uniform<glm::dvec4>,

		Uniform<int32_t>,
		Uniform<glm::ivec2>,
		Uniform<glm::ivec3>,
		Uniform<glm::ivec4>,

		Uniform<uint32_t>,
		Uniform<glm::uvec2>,
		Uniform<glm::uvec3>,
		Uniform<glm::uvec4>,

		Uniform<glm::mat2>,
		Uniform<glm::mat3>,
		Uniform<glm::mat4>,

		Uniform<glm::dmat2>,
		Uniform<glm::dmat3>,
		Uniform<glm::dmat4>,

		UniformArray<float>,
		UniformArray<glm::vec2>,
		UniformArray<glm::vec3>,
		UniformArray<glm::vec4>,

		UniformArray<double>,
		UniformArray<glm::dvec2>,
		UniformArray<glm::dvec3>,
		UniformArray<glm::dvec4>,

		UniformArray<int32_t>,
		UniformArray<glm::ivec2>,
		UniformArray<glm::ivec3>,
		UniformArray<glm::ivec4>,

		UniformArray<uint32_t>,
		UniformArray<glm::uvec2>,
		UniformArray<glm::uvec3>,
		UniformArray<glm::uvec4>,

		UniformArray<glm::mat2>,
		UniformArray<glm::mat3>,
		UniformArray<glm::mat4>,

		UniformArray<glm::dmat2>,
		UniformArray<glm::dmat3>,
		UniformArray<glm::dmat4>
	> ;
}