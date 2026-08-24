#pragma once
#include "Astral/Rendering/Backend/API.h"
#include <glad/glad.h>


namespace Astral::Render::OpenGL {
	class VertexBuffer : public IVertexBuffer {
	public:
		VertexBuffer(size_t length, size_t vertex_stride);
		~VertexBuffer();
		virtual void Upload(const void* data, size_t vertex_count, size_t vertex_offset) const override;
		virtual size_t Length() const override;
		virtual void Bind(uint32_t binding_slot) const override;

	private:
		GLuint handle;
		const size_t length;
		const size_t vertex_stride;
	};
}