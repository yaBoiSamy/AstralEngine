#pragma once

#include <string>
#include "Astral/Layers/ALayer.h"
#include "Astral/Rendering/GLSLCompiler.h"

namespace Astral
{
	class GLSLLayer : public ALayer
	{
	public:
		GLSLLayer();
		virtual void OnAttach() override;
		virtual void OnUpdate(const FrameContext& context) override;

	private:
		GLSLCompiler compiler;
		VertexBufferHandle vertexBufferID;
		VertexLayoutHandle vertexLayout;
		IndexBufferHandle indexBufferID;
		ShaderProgramHandle programID;
	};

}

