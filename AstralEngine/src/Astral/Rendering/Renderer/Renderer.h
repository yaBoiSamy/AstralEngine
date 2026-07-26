#pragma once
#include "Astral/Rendering/Buffers/VertexArray.h"
#include <glm/glm.hpp>

namespace Astral {

	class Renderer {
	public:
		static void InitRenderer();

		static void SetupFrame(std::pair<uint32_t, uint32_t> framebufferSize);

		//static void BeginScene(Scene& scene);
		//static void EndScene();

		static void Submit(const IVertexArray& vertexArray);

	private:
		static const glm::vec4 CLEAR_COLOR;
	};

}