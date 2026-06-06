#include "Common.h"
#include "TestRenderLayer.h"
#include <glad/glad.h>


namespace Astral
{
	TestRenderLayer::TestRenderLayer() : ALayer("TestRenderLayer") {}

	void TestRenderLayer::OnAttach() {

		// Vertex buffer setup
		float vertices[4 * 2] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			-0.5f,  0.5f,
			 0.5f,  0.5f
		};
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		glGenVertexArrays(1, &vertexLayout);
		glBindVertexArray(vertexLayout);
		glVertexAttribPointer(
			0, // Attrib index
			2, // # of fields in attribute
			GL_FLOAT,  // Type of each field
			GL_FALSE, // Fields not normalized (normalization depends on field types)
			2 * sizeof(float), // Distance between consecutive attributes
			0 // Offset to first field, 0 for tight packing
		);
		glEnableVertexAttribArray(0);


		// Index buffer setup 
		uint32_t indices[6] = {
			0, 1, 2,
			1, 2, 3
		};
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);


		// Shader program setup
		const std::string vertexDir = "src/Astral/Rendering/Shaders/vertex.vert.glsl";
		const std::string fragmentDir = "src/Astral/Rendering/Shaders/fragment.frag.glsl";

		programID = compiler.CreateShaderProgram(vertexDir, fragmentDir);
		if (programID == 0) {
			return;
		}
		glUseProgram(programID);
	}

	void TestRenderLayer::OnUpdate(const FrameContext& context) {
		glUseProgram(programID);
		glBindVertexArray(vertexLayout);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}