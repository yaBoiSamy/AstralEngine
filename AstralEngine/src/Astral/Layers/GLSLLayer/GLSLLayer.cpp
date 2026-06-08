#include "Common.h"
#include "GLSLLayer.h"
#include <glad/glad.h>


namespace Astral
{
	GLSLLayer::GLSLLayer() : 
		ALayer("TestRenderLayer"), 
		shader(VERTEX_DIR, FRAGMENT_DIR),
		vertexBuffer(Buffer::Usage::Static, { VertexBuffer::AttributeLayout(0, POS_DIMENSIONALITY, Buffer::NumericType::Float32) }),
		indexBuffer(Buffer::Usage::Static, Buffer::NumericType::UInt32) {

		shader.Bind();

		float vertices[POS_VERTEX_COUNT * POS_DIMENSIONALITY] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			-0.5f,  0.5f,
			 0.5f,  0.5f
		};
		vertexBuffer.Write(vertices, 8);

		uint32_t indices[6] = {
			0, 1, 2,
			1, 2, 3
		};
		indexBuffer.Write(indices, 6);
	}

	void GLSLLayer::OnUpdate(const FrameContext& context) {
		vertexBuffer.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}