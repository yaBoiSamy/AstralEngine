#include "Common.h"
#include "VertexBuffer.h"
#include <glad/glad.h>


namespace Astral::Render::OpenGL {
	VertexBuffer::VertexBuffer(size_t length, size_t vertex_stride) : length(length), vertex_stride(vertex_stride) {
		glGenBuffers(1, &handle);
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(
			GL_ARRAY_BUFFER,
			length * vertex_stride,
			nullptr,
			GL_DYNAMIC_DRAW
		);
	}

	VertexBuffer::~VertexBuffer() {
		if (handle != 0)
			glDeleteBuffers(1, &handle);
	}

	void VertexBuffer::Upload(const void* data, size_t vertex_count, size_t vertex_offset) const {
		AST_CORE_ASSERT(vertex_count + vertex_offset <= length, "Writing vertices past vertex buffer's capacity");
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			vertex_offset * vertex_stride,
			vertex_count * vertex_stride,
			data
		);
	}

	size_t VertexBuffer::Length() const {
		return length;
	}

	void VertexBuffer::Bind(uint32_t binding_slot) const {
		glBindVertexBuffer(
			binding_slot,
			handle,
			0,
			static_cast<GLsizei>(vertex_stride)
		);
	}
}