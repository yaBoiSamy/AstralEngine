#pragma once

#include <string>
#include "Astral/Layers/ALayer.h"
#include "Astral/Rendering/Shader/Shader.h"

namespace Astral
{
	class GLSLLayer : public ALayer
	{
	public:
		GLSLLayer();
		virtual void OnUpdate(const FrameContext& context) override;

		const std::string VERTEX_DIR = "src/Astral/Rendering/Shaders/vertex.vert.glsl";
		const std::string FRAGMENT_DIR = "src/Astral/Rendering/Shaders/fragment.frag.glsl";

	private:
		typedef uint32_t VertexBufferHandle;
		typedef uint32_t VertexLayoutHandle;
		typedef uint32_t IndexBufferHandle;

		Shader shader;
		VertexBufferHandle vertexBufferID;
		VertexLayoutHandle vertexLayout;
		IndexBufferHandle indexBufferID;
	};

}

