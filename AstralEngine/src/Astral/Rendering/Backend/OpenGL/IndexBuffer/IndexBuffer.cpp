#include "Common.h"
#include "IndexBuffer.h"


namespace Astral::Render::OpenGL {
	IndexBuffer::IndexBuffer(size_t length) : length(length) {
		glGenBuffers(1, &handle);		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			static_cast<GLsizeiptr>(length * sizeof(uint32_t)),
			nullptr,
			GL_DYNAMIC_DRAW
		);
	}

	IndexBuffer::~IndexBuffer() {
		if (handle != 0)
			glDeleteBuffers(1, &handle);
	}

	void IndexBuffer::Upload(const void* data, size_t index_count, size_t index_offset) const {
		AST_CORE_ASSERT(index_count + index_offset <= length, "Writing indices past index buffer's capacity");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
		glBufferSubData(
			GL_ELEMENT_ARRAY_BUFFER,
			static_cast<GLintptr>(index_offset * sizeof(uint32_t)),
			static_cast<GLsizeiptr>(index_count * sizeof(uint32_t)),
			data
		);
	}

	size_t IndexBuffer::Length() const {
		return length;
	}

	void IndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	}
}