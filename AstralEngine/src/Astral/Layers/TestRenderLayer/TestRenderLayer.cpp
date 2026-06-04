#include "Common.h"
#include "TestRenderLayer.h"
#include <glad/glad.h>


namespace Astral
{
	void TestRenderLayer::OnAttach() {
		AST_CORE_INFO("TestRenderLayer attached");

		float positions[6] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.0f,  0.5f
		};

		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &positions, GL_STATIC_DRAW);

		// Vertex array has many vertices. Vertices have many attributes. Attributes each have a format specified like this:
		glVertexAttribPointer(
			0, // Attrib index
			2, // # of fields in attribute
			GL_FLOAT,  // Type of each field
			GL_FALSE, // Fields not normalized (normalization depends on field types)
			2 * sizeof(float), // Distance between consecutive attributes
			0 // Offset to first field
		);
		glEnableVertexAttribArray(0);
	}

	void TestRenderLayer::OnUpdate(const FrameContext& context) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}