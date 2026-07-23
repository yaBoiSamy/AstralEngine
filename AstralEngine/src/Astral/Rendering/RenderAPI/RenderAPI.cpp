#include "Common.h"
#include "RenderAPI.h"
#include <glad/glad.h>

namespace Astral {
	OpenGLRenderAPI::OpenGLRenderAPI() {}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::Draw(const IVertexArray& vertexArray) {
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexArray.Length()), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderAPI::Present() {

	}
}