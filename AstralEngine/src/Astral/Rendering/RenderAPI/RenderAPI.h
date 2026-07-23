#pragma once
#include <glm/glm.hpp>
#include "Astral/Rendering/VertexArray/VertexArray.h"

namespace Astral {

	class RenderAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void Draw(const IVertexArray& vertexArray) = 0;
		virtual void Present() = 0;

	};

	class OpenGLRenderAPI : public RenderAPI {
	public:
		OpenGLRenderAPI();
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void Draw(const IVertexArray& vertexArray) override;
		virtual void Present() override;
	};
}

