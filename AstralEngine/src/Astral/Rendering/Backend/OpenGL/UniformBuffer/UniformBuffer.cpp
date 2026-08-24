#include "Common.h"
#include "UniformBuffer.h"
#include <glad/glad.h>

namespace Astral::Render::OpenGL {
	UniformBuffer::UniformBuffer(size_t buffer_stride) : buffer_stride(buffer_stride) {
		glGenBuffers(1, &handle);
		glBindBuffer(GL_UNIFORM_BUFFER, handle);
		glBufferData(
			GL_UNIFORM_BUFFER,
			buffer_stride,
			nullptr,
			GL_DYNAMIC_DRAW
		);
	}

	UniformBuffer::~UniformBuffer() {
		if (handle != 0)
			glDeleteBuffers(1, &handle);
	}

	void UniformBuffer::Bind(uint32_t binding_slot) const {
		glBindBufferBase(GL_UNIFORM_BUFFER, binding_slot, handle);
	}

	void UniformBuffer::Upload(const void* data) const {
		glBindBuffer(GL_UNIFORM_BUFFER, handle);
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			0,
			buffer_stride,
			data
		);
	}
}