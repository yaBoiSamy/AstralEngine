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

		glGenVertexArrays(1, &attributeLayout);
		glBindVertexArray(attributeLayout);

		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &positions, GL_STATIC_DRAW);

		// Vertex array has many vertices. Vertices have many attributes. Attributes each have a format specified like this:
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0, // Attrib index
			2, // # of fields in attribute
			GL_FLOAT,  // Type of each field
			GL_FALSE, // Fields not normalized (normalization depends on field types)
			2 * sizeof(float), // Distance between consecutive attributes
			0 // Offset to first field, 0 for tight packing
		);
		 
		std::string vertexShaderSrc = R"(
			#version 330 core
			layout(location = 0) in vec4 position;
			void main() {
				gl_Position = position;
			}
		)";

		std::string fragmentShaderSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			void main() {
				color = vec4(1.0, 0.5, 0.2, 1.0);
			}
		)";

		programID = CreateProgram(vertexShaderSrc, fragmentShaderSrc);
		if (programID == 0) {
			return;
		}
		glUseProgram(programID);
	}

	void TestRenderLayer::OnUpdate(const FrameContext& context) {
		glUseProgram(programID);
		glBindVertexArray(attributeLayout);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	uint32_t TestRenderLayer::CreateProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		uint32_t programID = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		if (vs == 0 || fs == 0)
			return 0;

		glAttachShader(programID, vs);
		glAttachShader(programID, fs);
		glLinkProgram(programID);
		glValidateProgram(programID);

		// Intermediates deletion
		glDeleteShader(vs);
		glDeleteShader(fs);

		return programID;
	}

	uint32_t TestRenderLayer::CompileShader(uint32_t type, const std::string& src) {
		uint32_t shaderID = glCreateShader(type);
		const char* rawsrc = src.c_str();
		glShaderSource(shaderID, 1, &rawsrc, nullptr);
		glCompileShader(shaderID);

		int result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			std::string message = std::string(length, '\0');
			glGetShaderInfoLog(shaderID, length, &length, message.data());
			AST_CORE_ERROR("Failed to compile shader: {0}", message);
			glDeleteShader(shaderID);
			return 0;
		}

		return shaderID;
	}
}