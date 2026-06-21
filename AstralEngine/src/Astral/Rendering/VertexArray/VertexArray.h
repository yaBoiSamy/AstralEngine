#pragma once
#include <span>
#include "Astral/Rendering/VertexArray/Buffers.h"
#include "Astral/Rendering/VertexArray/Attributes.h"

namespace Astral {

	template <typename VertexT, typename IndexT = uint32_t>
	class VertexArray {
	public:
		VertexArray(UsageHint vertex_buffer_usage, std::initializer_list<AttributeLayout> layout, UsageHint index_buffer_usage);

		// moving is supported
		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&& other) = default;

		// copying is not permitted
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		void WriteVertices(std::span<VertexT> data);
		void WriteIndices(std::span<IndexT> data);

		void Bind() const;

	private:
		VertexBuffer<VertexT> vbo;
		IndexBuffer<IndexT> ebo;
	};



	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	
	template<typename VertexT, typename IndexT>
	inline VertexArray<VertexT, IndexT>::VertexArray(UsageHint vertex_buffer_usage, std::initializer_list<AttributeLayout> layout, UsageHint index_buffer_usage) : 
		vbo(vertex_buffer_usage, layout), ebo(index_buffer_usage) {}

	template<typename VertexT, typename IndexT>
	inline void VertexArray<VertexT, IndexT>::WriteVertices(std::span<VertexT> data) {
		vbo.Write(data);
	}

	template<typename VertexT, typename IndexT>
	inline void VertexArray<VertexT, IndexT>::WriteIndices(std::span<IndexT> data) {
		ebo.Write(data);
	}

	template<typename VertexT, typename IndexT>
	inline void VertexArray<VertexT, IndexT>::Bind() const {
		vbo.Bind();
		ebo.Bind();
	}

}
