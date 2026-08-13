#pragma once

#include "Astral/Model/Layers/ALayer.h"

namespace Astral
{
	class MainLayer : public ALayer
	{
	public:
		MainLayer();
		
		virtual bool OnKeyPressedEvent(const Astral::KeyPressedEvent& event) override {
			AST_USER_INFO("Key Pressed: {0} (repeats: {1})", event.keycode, event.repeatCount);
			return false;
		}

		virtual void OnUpdate(const FrameContext& context) override;

	};

}

