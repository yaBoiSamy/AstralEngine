#pragma once
#include "Common.h"

#include "Astral/Rendering/Buffers/VertexArray.h"

namespace Astral::Render {

	class GraphicsAPI {
	public:
		virtual void Setup() = 0;
		virtual void SetActiveFrameBuffer(uint32_t id) = 0;
		virtual void SetViewport(uint32_t frame_width, uint32_t frame_height) = 0;
		virtual void Clear(const glm::vec4& color) = 0;
		virtual void Draw(const IVertexArray& vertexArray) = 0;
	};

	GraphicsAPI& GfxAPI();

	class OpenGLGraphicsAPI : public GraphicsAPI {
	public:
		OpenGLGraphicsAPI();
		virtual void Setup() override;
		virtual void SetActiveFrameBuffer(uint32_t id) override;
		virtual void SetViewport(uint32_t frame_width, uint32_t frame_height) override;
		virtual void Clear(const glm::vec4& color) override;
		virtual void Draw(const IVertexArray& vertexArray) override;
	};
}

