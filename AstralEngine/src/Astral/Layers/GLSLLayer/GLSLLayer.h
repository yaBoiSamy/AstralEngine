#pragma once

#include <string>
#include "Astral/Layers/ALayer.h"
#include "Astral/Rendering/Shader/Shader.h"
#include "Astral/Rendering/VertexArray/Attributes.h"
#include "Astral/Rendering/VertexArray/VertexArray.h"

namespace Astral
{
	class GLSLLayer : public ALayer
	{
	public:
		GLSLLayer();
		virtual void OnUpdate(const FrameContext& context) override;

	};

}

