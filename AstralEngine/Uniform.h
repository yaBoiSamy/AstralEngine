#pragma once
#include "Common.h"
#include "Astral/Rendering/OpenGLTranslations.h"
#include <glad/glad.h>

namespace Astral {
	using namespace glm;

	template <typename FieldT>
	class Uniform {
	public:
		Uniform(std::string name, GLuint shaderid) : handle(glGetUniformLocation(shaderid, name) {}

		void Write(FieldT& data) {
			writer.Write(handle, std::span<const FieldT>(&data, 1));
		}	
	private:
		const GLuint handle;
	};


	template <typename FieldT, uint32_t SIZE>
	class UniformArray {
	public:
		UniformArray(std::string name, GLuint shaderid) : handle(glGetUniformLocation(shaderid, name) {}

		void Write(std::span<FieldT> data) {
			AST_CORE_ASSERT(data.size() == SIZE, "data span is of incompatible size")
			writer.Write(handle, data);
		}
	private:
		const GLuint handle;
	};
}