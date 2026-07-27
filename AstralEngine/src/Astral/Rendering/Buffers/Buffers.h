#pragma once
#include <glad/glad.h>
#include <span>
#include "Astral/Rendering/Buffers/Attributes.h"


namespace Astral {

	enum class UsageHint {
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
		Stream = GL_STREAM_DRAW
	};

	template <typename BufferElementT>
	class ABuffer {
	public:

		ABuffer(size_t length, UsageHint usage, GLenum target);
		virtual ~ABuffer();

		// moving is supported
		ABuffer(ABuffer&&);
		ABuffer& operator=(ABuffer&& other) = default;

		// copying is not permitted
		ABuffer(const ABuffer&) = delete;
		ABuffer& operator=(const ABuffer&) = delete;


		virtual void Bind() const;
		void Write(uint32_t start, std::span<BufferElementT> data);

		size_t Length() const;

	protected:
		GLuint handle;
		const GLenum target;

	private:
		const UsageHint usage;
		const size_t length;
	};

		
	template <typename IndexT>
	class IndexBuffer : public ABuffer<IndexT> {
	public:
		IndexBuffer(size_t length, UsageHint usage);

		// moving is supported
		IndexBuffer(IndexBuffer&&) = default;
		IndexBuffer& operator=(IndexBuffer&& other) = default;
	};


	template <typename VertexT>
	class VertexBuffer : public ABuffer<VertexT> {
	public:

		VertexBuffer(size_t length, UsageHint usage, std::span<const AttributeLayout>& layout, uint32_t advancement_rate = 0);
		virtual ~VertexBuffer() override;

		// moving is supported
		VertexBuffer(VertexBuffer&&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;

		virtual void Bind() const override;

	private:
		uint32_t VertexStride() const;
		GLuint layoutHandle;
		const std::vector<AttributeLayout> layout;
	};


	template <typename UniformT>
	class UniformBuffer : public ABuffer<UniformT> {
	public:
		UniformBuffer(UsageHint usage, uint32_t binding_point);

		// moving is supported
		UniformBuffer(UniformBuffer&&) = default;
		UniformBuffer& operator=(UniformBuffer&& other) = default;

		void Write(UniformT& data);
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================


	// ================================================ Abstract buffer ================================================

	template <typename BufferElementT>
	ABuffer<BufferElementT>::ABuffer(size_t length, UsageHint usage, GLenum target) : length(length), usage(usage), target(target) {
		glGenBuffers(1, &handle);
		Bind();
		glBufferData(
			target,
			length * sizeof(BufferElementT),
			nullptr,
			static_cast<GLenum>(usage)
		);
	}

	template <typename BufferElementT>
	ABuffer<BufferElementT>::ABuffer(ABuffer&& other) : handle(other.handle), usage(other.usage), length(other.length), target(other.target) {
		other.handle = 0;
	}

	template <typename BufferElementT>
	ABuffer<BufferElementT>::~ABuffer() {
		if (handle != 0)
			glDeleteBuffers(1, &handle);
	}

	template <typename BufferElementT>
	void ABuffer<BufferElementT>::Bind() const {
		glBindBuffer(target, handle);
	}
	
	template <typename BufferElementT>
	void ABuffer<BufferElementT>::Write(uint32_t start, std::span<BufferElementT> data) {
		Bind();
		glBufferSubData(
			target,
			start * sizeof(BufferElementT),
			data.size() * sizeof(BufferElementT),
			data.data()
		);
	}

	template<typename BufferElementT>
	size_t ABuffer<BufferElementT>::Length() const {
		return length;
	}

	// ================================================= Index buffer ==================================================

	template <typename IndexT>
	IndexBuffer<IndexT>::IndexBuffer(size_t length, UsageHint usage) : ABuffer<IndexT>(length, usage, GL_ELEMENT_ARRAY_BUFFER) {}


	// ================================================= Vertex buffer =================================================


	template <typename VertexT>
	VertexBuffer<VertexT>::VertexBuffer(
		size_t length,
		UsageHint usage,
		std::span<const AttributeLayout>& layout,
		uint32_t advancement_rate
	) : ABuffer<VertexT>(length, usage, GL_ARRAY_BUFFER),
		layout(layout.begin(), layout.end()) {

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
			glVertexAttribDivisor(attributeLayout.index, advancement_rate);
		}
	}

	template <typename VertexT>
	VertexBuffer<VertexT>::~VertexBuffer() {
		glDeleteVertexArrays(1, &layoutHandle);
	}

	template <typename VertexT>
	void VertexBuffer<VertexT>::Bind() const {
		ABuffer<VertexT>::Bind();
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


// ================================================= Uniform buffer =================================================

	template <typename UniformT>
	UniformBuffer<UniformT>::UniformBuffer(UsageHint usage, uint32_t binding_point) : ABuffer<UniformT>(1, usage, GL_UNIFORM_BUFFER) {
		glBindBufferBase(this->target, binding_point, this->handle);
	}

	template <typename UniformT>
	void UniformBuffer<UniformT>::Write(UniformT& data) {
		ABuffer<UniformT>::Write(0, std::span<UniformT>(&data, 1));
	}
}