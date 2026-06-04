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
		uint32_t CreateProgram(const std::string& vertexShader, const std::string& fragmentShader);
		uint32_t CompileShader(uint32_t type, const std::string& src);

		uint32_t bufferID;
		uint32_t attributeLayout;
		uint32_t programID;
	};

}

