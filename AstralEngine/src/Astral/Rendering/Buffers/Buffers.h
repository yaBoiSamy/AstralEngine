#pragma once
#include <glad/glad.h>

namespace Astral {

	// For C++ type -> OpenGL type conversion
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


	enum class UsageHint {
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
		Stream = GL_STREAM_DRAW
	};

	template <typename BufferElementT>
	class Buffer {
	public:

		Buffer(UsageHint usage);
		virtual ~Buffer();

		// moving is supported
		Buffer(Buffer&&) = default;
		Buffer& operator=(Buffer&& other) = default;

		// copying is not permitted
		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;


		virtual void Bind() const;
		void Write(std::span<BufferElementT> data);

	private:

		virtual GLenum GLTarget() const = 0;
		GLuint handle;
		const UsageHint usage;
	};

		
	template <typename IndexT>
	class IndexBuffer : public Buffer<IndexT> {
	public:
		IndexBuffer(UsageHint usage) : Buffer<IndexT>(usage) {}

		// moving is supported
		IndexBuffer(IndexBuffer&&) = default;
		IndexBuffer& operator=(IndexBuffer&& other) = default;

	private:
		virtual GLenum GLTarget() const override;
	};


	struct AttributeLayout {
		template <typename FieldT>
		static AttributeLayout Create(uint32_t index, uint32_t fieldCount, uint32_t offset, bool normalized = false);
		const uint32_t index;
		const GLenum fieldType;
		const uint32_t fieldCount;
		const uint32_t stride;
		const uint32_t offset;
		const bool normalized;
	};


	template <typename VertexT>
	class VertexBuffer : public Buffer<VertexT> {
	public:

		using VertexLayout = std::vector<AttributeLayout>;

		VertexBuffer(UsageHint usage, const VertexLayout& layout);
		virtual ~VertexBuffer() override;

		// moving is supported
		VertexBuffer(VertexBuffer&&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;

		virtual void Bind() const override;

	private:
		virtual GLenum GLTarget() const override;
		uint32_t VertexStride() const;
		GLuint layoutHandle;
		const VertexLayout layout;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================


	// ================================================ Abstract buffer ================================================

	template <typename BufferElementT>
	Buffer<BufferElementT>::Buffer(UsageHint usage) : usage(usage) {
		glGenBuffers(1, &handle);
	}

	template <typename BufferElementT>
	Buffer<BufferElementT>::~Buffer() {
		glDeleteBuffers(1, &handle);
	}

	template <typename BufferElementT>
	void Buffer<BufferElementT>::Bind() const {
		glBindBuffer(this->GLTarget(), handle);
	}
	
	template <typename BufferElementT>
	void Buffer<BufferElementT>::Write(std::span<BufferElementT> data) {
		Bind();
		glBufferData(
			this->GLTarget(),
			data.size() * sizeof(BufferElementT),
			data.data(),
			static_cast<GLenum>(usage)
		);
	}

	// ================================================= Index buffer ==================================================

	template<typename IndexT>
	GLenum IndexBuffer<IndexT>::GLTarget() const {
		return GL_ELEMENT_ARRAY_BUFFER;
	}


	// ================================================= Vertex buffer =================================================

	template<typename FieldT>
	AttributeLayout AttributeLayout::Create(uint32_t index, uint32_t fieldCount, uint32_t offset, bool normalized) {
		return { index, GLNumericType<FieldT>::value, fieldCount, sizeof(FieldT) * fieldCount, offset, normalized };
	}	


	template <typename VertexT>
	VertexBuffer<VertexT>::VertexBuffer(UsageHint usage, const VertexLayout& layout) : Buffer<VertexT>(usage), layout(layout) {
		glGenVertexArrays(1, &layoutHandle);
		Bind();

		const uint32_t vertexStride = VertexStride();
		for (const AttributeLayout& attributeLayout : layout) {
			glVertexAttribPointer(
				attributeLayout.index,
				attributeLayout.fieldCount,
				attributeLayout.fieldType,
				attributeLayout.normalized ? GL_TRUE : GL_FALSE,
				vertexStride,
				reinterpret_cast<void*>(static_cast<uintptr_t>(attributeLayout.offset))
			);
			glEnableVertexAttribArray(attributeLayout.index);
		}
	}

	template <typename VertexT>
	VertexBuffer<VertexT>::~VertexBuffer() {
		glDeleteVertexArrays(1, &layoutHandle);
	}

	template <typename VertexT>
	void VertexBuffer<VertexT>::Bind() const {
		Buffer<VertexT>::Bind();
		glBindVertexArray(layoutHandle);
	}


	template <typename VertexT>
	uint32_t VertexBuffer<VertexT>::VertexStride() const {
		uint32_t totalsize = 0;
		for (const AttributeLayout& attributeLayout : layout) {
			totalsize = std::max(totalsize, attributeLayout.offset + attributeLayout.stride);
		}
		return totalsize;
	}

	template <typename VertexT>
	GLenum VertexBuffer<VertexT>::GLTarget() const {
		return GL_ARRAY_BUFFER;
	}
}
