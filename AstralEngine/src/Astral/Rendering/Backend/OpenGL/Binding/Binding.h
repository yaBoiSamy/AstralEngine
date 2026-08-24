#pragma once
#include "Astral/Rendering/Backend/API.h"
#include <glad/glad.h>


namespace Astral::Render::OpenGL {

	class VertexBufferBinding : public IVertexBufferBinding {
	public:
		VertexBufferBinding(GLuint binding_slot, IVertexBuffer* resource);
		virtual void Bind(IShader* shader) const override;

	private:
		const GLuint binding_slot;
		IVertexBuffer* resource;
	};

	class UniformBufferBinding : public IUniformBufferBinding {
	public:
		UniformBufferBinding(GLuint binding_slot, IUniformBuffer* resource);
		virtual void Bind(IShader* shader) const override;

	private:
		const GLuint binding_slot;
		IUniformBuffer* resource;
	};

	class TextureBinding : public ITextureBinding {
	public:
		TextureBinding(GLuint binding_slot, ITexture* resource);
		virtual void Bind(IShader* shader) const override;

	private:
		const GLuint binding_slot;
		ITexture* resource;
	};
};

