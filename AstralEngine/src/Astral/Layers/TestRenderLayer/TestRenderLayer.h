#pragma once

#include "Astral/Layers/ALayer.h"

namespace Astral
{
	class TestRenderLayer : public ALayer
	{
	public:
		TestRenderLayer() : ALayer("TestRenderLayer") {}
		virtual void OnAttach() override;
		virtual void OnUpdate(const FrameContext& context) override;

	private:
		uint32_t bufferID;
	};

}

