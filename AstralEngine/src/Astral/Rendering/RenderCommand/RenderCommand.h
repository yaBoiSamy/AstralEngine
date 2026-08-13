#pragma once
#include "Common.h"
#include "Astral/Rendering/Buffers/VertexArray.h"

namespace Astral {

	class RenderCommand {
	public:
		static void SetActiveFrameBuffer(uint32_t id);
		static void SetViewport(uint32_t frame_width, uint32_t frame_height);
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void Draw(const IVertexArray& vertexArray);
	};

}