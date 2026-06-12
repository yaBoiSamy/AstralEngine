#include "Common.h"
#include "GLSLLayer.h"
#include <glad/glad.h>


namespace Astral
{
	GLSLLayer::GLSLLayer() :
		ALayer("TestRenderLayer"),
		shader(VERTEX_DIR, FRAGMENT_DIR),
		vertexBuffer(UsageHint::Static, { 
			AttributeLayout::Create<float>(0, 1, offsetof(fort, x)),
			AttributeLayout::Create<float>(1, 1, offsetof(fort, y))
			}),
		indexBuffer(UsageHint::Static) {

		shader.Bind();

		//float vertices[POS_VERTEX_COUNT * 2] = {
		//	-0.5f, -0.5f,
		//	 0.5f, -0.5f,
		//	-0.5f,  0.5f,
		//	 0.5f,  0.5f
		//};
		fort vertices[4] = {
			{ false, 0, {'a', 'b'}, -0.5f, -0.5f },
			{ true,  1, {'c', 'd'},  0.5f, -0.5f },
			{ false, 2, {'e', 'f'}, -0.5f,  0.5f },
			{ true,  3, {'g', 'h'},  0.5f,  0.5f }
		};
		vertexBuffer.Write(std::span<fort, POS_VERTEX_COUNT>(vertices));

		uint32_t indices[6] = {
			0, 1, 2,
			1, 2, 3
		};
		indexBuffer.Write(std::span<uint32_t, 6>(indices));
	}

	void GLSLLayer::OnUpdate(const FrameContext& context) {
		vertexBuffer.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}