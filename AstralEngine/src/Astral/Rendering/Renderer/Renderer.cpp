#include "Common.h"
#include "Renderer.h"
#include "Astral/Rendering/RenderAPI/RenderAPI.h"
#include "Astral/Rendering/RenderCommand/RenderCommand.h"

namespace Astral {

	const glm::vec4 Renderer::CLEAR_COLOR = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

	void Renderer::InitRenderer() {
		GfxAPI().LogDriverInfo();
		GfxAPI().ConfigureErrorMessageLogging();
		RenderCommand::SetClearColor(CLEAR_COLOR);
	}

	void Renderer::SetupFrame(std::pair<uint32_t, uint32_t> framebufferSize) {
		RenderCommand::SetActiveFrameBuffer(0);
		RenderCommand::SetViewport(framebufferSize);
		RenderCommand::Clear();
	}

	//void Renderer::BeginScene(Scene& scene) {

	//}

	//void Renderer::EndScene() {s
	//
	//}

	void Renderer::Submit(const IVertexArray& vertexArray) {
		RenderCommand::Draw(vertexArray);
	}

}