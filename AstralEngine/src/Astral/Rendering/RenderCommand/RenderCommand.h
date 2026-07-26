#pragma once
#include <glm/glm.hpp>
#include "Astral/Rendering/Buffers/VertexArray.h"

namespace Astral {

	class RenderCommand {
	public:
		static void SetActiveFrameBuffer(uint32_t id);
		static void SetViewport(std::pair<uint32_t, uint32_t> framebufferSize);
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void Draw(const IVertexArray& vertexArray);
	};

}