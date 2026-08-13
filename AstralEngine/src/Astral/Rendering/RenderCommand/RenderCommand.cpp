#include "Common.h"
#include "RenderCommand.h"
#include "Astral/Rendering/RenderAPI/RenderAPI.h"

namespace Astral {
	void RenderCommand::SetActiveFrameBuffer(uint32_t id) {
		GfxAPI().SetActiveFrameBuffer(id);
	}

	void RenderCommand::SetViewport(uint32_t frame_width, uint32_t frame_height) {
		GfxAPI().SetViewport(frame_width, frame_height);
	}

	void RenderCommand::SetClearColor(const glm::vec4& color) {
		GfxAPI().SetClearColor(color);
	}

	void RenderCommand::Clear() {
		GfxAPI().Clear();
	}

	void RenderCommand::Draw(const IVertexArray& vertexArray) {
		vertexArray.Bind();
		GfxAPI().Draw(vertexArray);
	}
}