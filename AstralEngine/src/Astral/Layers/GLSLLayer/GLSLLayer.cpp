#include "Common.h"
#include "GLSLLayer.h"
#include <glad/glad.h>
#include "Astral/Rendering/VertexArray/Attributes.h"


namespace Astral
{
	GLSLLayer::GLSLLayer() :
		ALayer("TestRenderLayer"),
		shader(VERTEX_DIR, FRAGMENT_DIR),
		vertex_array(
			UsageHint::Static, 
			{
				Attr::Vec4::Layout(0, offsetof(Vertex, color)),
				Attr::Vec2::Layout(1, offsetof(Vertex, pos)),
			},
			UsageHint::Static
		) 
	{

		shader.Bind();
		Vertex vertices[VERT_COUNT] = {
			{ // Bottom left red
				{ 1.0f, 0.0f, 0.0f, 1.0f },   // color
				{ -0.5f, -0.5f }              // pos
			},
			{ // Bottom right green
				{ 0.0f, 1.0f, 0.0f, 1.0f },
				{  0.5f, -0.5f }
			},
			{ // Top center blue
				{ 0.0f, 0.0f, 1.0f, 1.0f },
				{  0.0f,  0.5f }
			}
		};
		vertex_array.WriteVertices(std::span<Vertex, VERT_COUNT>(vertices));

		uint32_t indices[3] = {
			0, 1, 2
		};
		vertex_array.WriteIndices(std::span<uint32_t, 3>(indices));
	}

	void GLSLLayer::OnUpdate(const FrameContext& context) {
		shader.Bind();
		vertex_array.Bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
}