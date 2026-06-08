#pragma once
#include <glad/glad.h>

namespace Astral {

	class Buffer {
	public:
		enum class NumericType {
			Int8 = GL_BYTE,
			UInt8 = GL_UNSIGNED_BYTE,
			Int16 = GL_SHORT,
			UInt16 = GL_UNSIGNED_SHORT,
			Int32 = GL_INT,
			UInt32 = GL_UNSIGNED_INT,
			Float16 = GL_HALF_FLOAT,
			Float32 = GL_FLOAT,
			Double64 = GL_DOUBLE
		};

		enum class Type
		{
			Vertex = GL_ARRAY_BUFFER,
			Index = GL_ELEMENT_ARRAY_BUFFER
		};

		enum class Usage {
			Static = GL_STATIC_DRAW,
			Dynamic = GL_DYNAMIC_DRAW,
			Stream = GL_STREAM_DRAW
		};

		Buffer(Buffer::Type type, Usage usage);
		Buffer(Buffer&&) = default;
		Buffer& operator=(Buffer&& other) = default;
		virtual ~Buffer();

		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;

		virtual void Bind() const;
		void Write(const void* data, uint32_t elementCount);
	protected:
		static uint32_t SizeOfNumType(NumericType numtype);
		virtual uint32_t SizeOfNElements(uint32_t nElements) const = 0;
	private:
		typedef GLuint BufferHandle;
		BufferHandle handle;
		const Buffer::Type type;
		const Usage usage;
	};


	class IndexBuffer : public Buffer {
	public:
		IndexBuffer(Usage usage, NumericType indexType);
		IndexBuffer(IndexBuffer&&) = default;
		IndexBuffer& operator=(IndexBuffer&& other) = default;
	private:
		virtual uint32_t SizeOfNElements(uint32_t nElements) const override;
		NumericType indexType;
	};


	class VertexBuffer : public Buffer {
	public:
		struct AttributeLayout {
			AttributeLayout(uint32_t index, uint32_t fieldCount, NumericType fieldType, bool normalized = false);
			uint32_t Stride() const;
			const uint32_t index;
			const NumericType fieldType;
			const uint32_t fieldCount;
			const bool normalized;
		};

		using VertexLayout = std::vector<AttributeLayout>;

		VertexBuffer(Usage usage, const VertexLayout& layout);
		VertexBuffer(VertexBuffer&&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;
		virtual ~VertexBuffer() override;

		virtual void Bind() const override;
	private:
		uint32_t VertexStride() const;
		virtual uint32_t SizeOfNElements(uint32_t nElements) const override;

		typedef GLuint LayoutHandle;

		LayoutHandle layoutHandle;
		const VertexLayout layouts;
	};
}
