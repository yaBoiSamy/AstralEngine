#pragma once
#include <glad/glad.h>
#include "Astral/Rendering/Backend/API.h"


namespace Astral::Render::OpenGL {

	class IndexBuffer : public IIndexBuffer {
	public:
		IndexBuffer(size_t length);
		~IndexBuffer();
		virtual void Upload(const void* data, size_t index_count, size_t index_offset) const override;
		virtual size_t Length() const override;
		void Bind() const;

	private:
		GLuint handle;
		const size_t length;
	};
}

