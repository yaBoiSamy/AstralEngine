#pragma once
#include <span>
#include "Astral/Rendering/VertexArray/Buffers.h"
#include "Astral/Rendering/VertexArray/Attributes.h"

namespace Astral {

	class IVertexArray {
	public:
		virtual void Bind() const = 0;
		virtual uint32_t Length() const = 0;
	};

	template <typename VertexT, typename IndexT = uint32_t>
	class VertexArray : public IVertexArray {
	public:
		VertexArray(uint32_t vert_count, uint32_t index_count, UsageHint vertex_buffer_usage, std::initializer_list<AttributeLayout> layout, UsageHint index_buffer_usage);

		// moving is supported
		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&& other) = default;

		// copying is not permitted
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		void WriteVertices(uint32_t start, std::span<VertexT> data);
		void WriteIndices(uint32_t start, std::span<IndexT> data);

		virtual void Bind() const override;
		virtual uint32_t Length() const override;
	private:
		VertexBuffer<VertexT> vbo;
		IndexBuffer<IndexT> ebo;
	};



	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	
	template<typename VertexT, typename IndexT>
	inline VertexArray<VertexT, IndexT>::VertexArray(uint32_t vert_count, uint32_t index_count, UsageHint vertex_buffer_usage, std::initializer_list<AttributeLayout> layout, UsageHint index_buffer_usage) : 
		vbo(vert_count, vertex_buffer_usage, layout), ebo(index_count, index_buffer_usage) {}

	template<typename VertexT, typename IndexT>
	inline void VertexArray<VertexT, IndexT>::WriteVertices(uint32_t start, std::span<VertexT> data) {
		vbo.Write(start, data);
	}

	template<typename VertexT, typename IndexT>
	inline void VertexArray<VertexT, IndexT>::WriteIndices(uint32_t start, std::span<IndexT> data) {
		ebo.Write(start, data);
	}

	template<typename VertexT, typename IndexT>
	inline void VertexArray<VertexT, IndexT>::Bind() const {
		vbo.Bind();
		ebo.Bind();
	}

	template<typename VertexT, typename IndexT>
	inline uint32_t VertexArray<VertexT, IndexT>::Length() const {
		return ebo.Length();
	}

}
