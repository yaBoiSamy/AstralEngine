#pragma once

#include <string>
#include "Astral/Layers/ALayer.h"
#include "Astral/Rendering/Shader/Shader.h"
#include "Astral/Rendering/VertexArray/Buffers.h"
#include "Astral/Rendering/VertexArray/Attributes.h"
#include "Astral/Rendering/VertexArray/VertexArray.h"

namespace Astral
{
	class GLSLLayer : public ALayer
	{
	public:
		GLSLLayer();
		virtual void OnUpdate(const FrameContext& context) override;

		const std::string VERTEX_DIR = "src/Shaders/vertex.vert.glsl";
		const std::string FRAGMENT_DIR = "src/Shaders/fragment.frag.glsl";

	private:
		typedef uint32_t VertexBufferHandle;
		typedef uint32_t VertexLayoutHandle;
		typedef uint32_t IndexBufferHandle;

		Shader shader;
		static const uint32_t VERT_COUNT = 3;

		struct Vertex { 
			Attr::Vec4 color;
			Attr::Vec2 pos;
		};
		VertexArray<Vertex> vertex_array;
	};

}

