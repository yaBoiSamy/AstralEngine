#include "Common.h"
#include "Buffers.h"
#include <glad/glad.h>


namespace Astral
{
	Buffer::Buffer(Buffer::Type type, Usage usage) : type(type), usage(usage) {
		glGenBuffers(1, &handle);
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &handle);
	}

	void Buffer::Write(const void* data, uint32_t elementCount) {
		Bind();
		glBufferData(static_cast<GLenum>(type), SizeOfNElements(elementCount), data, static_cast<GLenum>(usage));
	}

	void Buffer::Bind() const {
		glBindBuffer(static_cast<GLenum>(type), handle);
	}

	uint32_t Buffer::SizeOfNumType(Buffer::NumericType type) {
		switch (type) {
		case Buffer::NumericType::Int8:
		case Buffer::NumericType::UInt8:
			return 1;
		case Buffer::NumericType::Int16:
		case Buffer::NumericType::UInt16:
		case Buffer::NumericType::Float16:
			return 2;
		case Buffer::NumericType::Int32:
		case Buffer::NumericType::UInt32:
		case Buffer::NumericType::Float32:
			return 4;
		case Buffer::NumericType::Double64:
			return 8;
		default:
			AST_CORE_ASSERT(false, "Invalid field type");
			return 0;
		}
	}

	IndexBuffer::IndexBuffer(Usage usage, NumericType indexType) : Buffer(Buffer::Type::Index, usage), indexType(indexType) {}

	uint32_t IndexBuffer::SizeOfNElements(uint32_t nElements) const {
		return nElements * SizeOfNumType(indexType);
	}

	VertexBuffer::VertexBuffer(Usage usage, const VertexLayout& layouts) : Buffer(Buffer::Type::Vertex, usage), layouts(layouts) {
		glGenVertexArrays(1, &layoutHandle);
		Bind();

		uint32_t vertexStride = VertexStride();
		uint32_t offset = 0;
		for (const AttributeLayout& attributeLayout : layouts) {
			glVertexAttribPointer(
				attributeLayout.index,
				attributeLayout.fieldCount,
				static_cast<GLenum>(attributeLayout.fieldType),
				attributeLayout.normalized ? GL_TRUE : GL_FALSE,
				vertexStride,
				reinterpret_cast<void*>(static_cast<uintptr_t>(offset))
			);
			offset += attributeLayout.Stride();
			glEnableVertexAttribArray(attributeLayout.index);
		}
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteVertexArrays(1, &layoutHandle);
	}

	void VertexBuffer::Bind() const {
		Buffer::Bind();
		glBindVertexArray(layoutHandle);
	}

	VertexBuffer::AttributeLayout::AttributeLayout(uint32_t index, uint32_t fieldCount, NumericType fieldtype, bool normalized) : 
		index(index), fieldCount(fieldCount), fieldType(fieldtype), normalized(normalized) {}

	uint32_t VertexBuffer::AttributeLayout::Stride() const {
		return fieldCount * SizeOfNumType(fieldType);
	}

	uint32_t VertexBuffer::VertexStride() const {
		uint32_t totalsize = 0;
		for (const AttributeLayout& attributeLayout : layouts) {
			totalsize += attributeLayout.Stride();
		}
		return totalsize;
	}

	uint32_t VertexBuffer::SizeOfNElements(uint32_t nElements) const {
		return VertexStride() * nElements;
	}
}
