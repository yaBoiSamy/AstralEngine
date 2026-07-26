#pragma once
#include <span>
#include "Astral/Rendering/Buffers/Buffers.h"
#include "Astral/Rendering/Buffers/Attributes.h"

namespace Astral {

	class IVertexArray {
	public:
		virtual void Bind() const = 0;
		virtual size_t Length() const = 0;
	};

	template <typename VertexT, typename IndexT = uint32_t>
	class VertexArray : public IVertexArray {
	public:
		VertexArray(size_t vert_count, size_t index_count, UsageHint usage, std::span<const AttributeLayout> layout);

		// moving is supported
		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&& other) = default;

		// copying is not permitted
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		void WriteVertices(uint32_t start, std::span<VertexT> data);
		void WriteIndices(uint32_t start, std::span<IndexT> data);

		virtual void Bind() const override;
		virtual size_t Length() const override;
	private:
		VertexBuffer<VertexT> vbo;
		IndexBuffer<IndexT> ebo;
	};



	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	
	template<typename VertexT, typename IndexT>
	inline VertexArray<VertexT, IndexT>::VertexArray(size_t vert_count, size_t index_count, UsageHint usage, std::span<const AttributeLayout> layout) :
		vbo(vert_count, usage, layout), ebo(index_count, usage) {}

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
	inline size_t VertexArray<VertexT, IndexT>::Length() const {
		return ebo.Length();
	}

}
