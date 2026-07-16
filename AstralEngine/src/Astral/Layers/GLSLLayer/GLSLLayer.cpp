#include "Common.h"
#include "GLSLLayer.h"
#include "Astral/Rendering/VertexArray/Attributes.h"
#include "Astral/Rendering/VertexArray/VertexArray.h"
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