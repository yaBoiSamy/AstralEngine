#pragma once
#include "Astral/Rendering/Backend/API.h"
#include <glad/glad.h>


namespace Astral::Render::OpenGL {
	class UniformBuffer : public IUniformBuffer {
	public:
		UniformBuffer(size_t buffer_stride);
		~UniformBuffer();
		virtual void Bind(uint32_t binding_slot) const override;
		virtual void Upload(const void* data) const override;

	private:
		GLuint handle;
		const size_t buffer_stride;
	};
}
