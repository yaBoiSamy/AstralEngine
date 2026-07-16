#include "Common.h"
#include "RenderCommand.h"

namespace Astral {
	void RenderCommand::SetClearColor(const glm::vec4& color) {
		renderAPI->SetClearColor(color);
	}

	void RenderCommand::Clear() {
		renderAPI->Clear();
	}

	void RenderCommand::Draw(const IVertexArray& vertexArray) {
		vertexArray.Bind();
		renderAPI->Draw(vertexArray);
	}

	ptr<RenderAPI> RenderCommand::renderAPI = std::make_unique<OpenGLRenderAPI>();
}