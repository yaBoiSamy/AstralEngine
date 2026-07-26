#include "Common.h"
#include "GLSLLayer.h"
#include "Astral/Rendering/Buffers/Attributes.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Renderer/Renderer.h"


namespace Astral
{
	GLSLLayer::GLSLLayer() :
		ALayer("TestRenderLayer")

	{
	}

	void GLSLLayer::OnUpdate(const FrameContext& context) {
	}
}