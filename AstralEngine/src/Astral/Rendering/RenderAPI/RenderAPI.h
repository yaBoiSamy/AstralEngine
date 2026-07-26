#pragma once
#include <glm/glm.hpp>
#include "Astral/Rendering/Buffers/VertexArray.h"

namespace Astral {

	class RenderAPI {
	public:
		virtual void ConfigureErrorMessageLogging() = 0;
		virtual void LogDriverInfo() = 0;
		virtual void SetActiveFrameBuffer(uint32_t id) = 0;
		virtual void SetViewport(std::pair<uint32_t, uint32_t> framebufferSize) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void Draw(const IVertexArray& vertexArray) = 0;
	};

	RenderAPI& GfxAPI();

	class OpenGLRenderAPI : public RenderAPI {
	public:
		OpenGLRenderAPI();
		virtual void ConfigureErrorMessageLogging() override;
		virtual void LogDriverInfo() override;
		virtual void SetActiveFrameBuffer(uint32_t id) override;
		virtual void SetViewport(std::pair<uint32_t, uint32_t> framebufferSize) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void Draw(const IVertexArray& vertexArray) override;
	};
}

