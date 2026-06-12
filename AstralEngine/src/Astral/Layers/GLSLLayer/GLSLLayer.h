#pragma once

#include <string>
#include "Astral/Layers/ALayer.h"
#include "Astral/Rendering/Shader/Shader.h"
#include "Astral/Rendering/Buffers/Buffers.h"

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
		static const uint32_t POS_VERTEX_COUNT = 4;
		static const uint32_t POS_DIMENSIONALITY = 2;

		struct fort { 
			bool ab;
			int c;
			char sus[2];
			float x; 
			float y; 
		};
		VertexBuffer<fort> vertexBuffer;
		IndexBuffer<uint32_t> indexBuffer;
	};

}

