#pragma once
#include "Astral/Rendering/RenderAPI/RenderAPI.h"

namespace Astral {

	class RenderCommand {
	public:
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void Draw(const IVertexArray& vertexArray);

	private:
		static ptr<RenderAPI> renderAPI;
	};

}