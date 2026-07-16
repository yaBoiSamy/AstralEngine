#include "Common.h"
#include "Renderer.h"
#include "Astral/Rendering/RenderCommand/RenderCommand.h"

namespace Astral {
	void Renderer::BeginScene() {

	}

	void Renderer::EndScene() {
	
	}

	void Renderer::Submit(const IVertexArray& vertexArray) {
		RenderCommand::Draw(vertexArray);
	}

}