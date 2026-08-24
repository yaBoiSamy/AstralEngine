#include "Common.h"
#include "Binding.h"


namespace Astral::Render::OpenGL {

	VertexBufferBinding::VertexBufferBinding(GLuint binding_slot, IVertexBuffer* resource) : binding_slot(binding_slot), resource(resource) {
		AST_CORE_ASSERT(resource, "Cannot bind a null vertex buffer");
	}

	void VertexBufferBinding::Bind(IShader* shader) const {
		resource->Bind(binding_slot);
	}

	UniformBufferBinding::UniformBufferBinding(GLuint binding_slot, IUniformBuffer* resource) : binding_slot(binding_slot), resource(resource) {
		AST_CORE_ASSERT(resource, "Cannot bind a null uniform buffer");
	}

	void UniformBufferBinding::Bind(IShader* shader) const {
		resource->Bind(binding_slot);
	}

	TextureBinding::TextureBinding(GLuint binding_slot, ITexture* resource) : binding_slot(binding_slot), resource(resource) {
		AST_CORE_ASSERT(resource, "Cannot bind a null texture");
	}

	void TextureBinding::Bind(IShader* shader) const {
		resource->Bind(binding_slot);
	}

}