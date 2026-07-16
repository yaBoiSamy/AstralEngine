#pragma once
#include "Astral/Rendering/VertexArray/VertexArray.h"

namespace Astral {

	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const IVertexArray& vertexArray);
	};

}