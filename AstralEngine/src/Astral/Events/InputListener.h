#pragma once
#include <Common.h>
#include "Astral/Events/EventListener.h"

namespace Astral {
	class InputListener : public EventListener	{
	public:
		bool IsKeyPressed(int keycode);
		bool IsMouseButtonPressed(int button);
		std::pair<double, double> GetMousePosition();
		void SwapBuffers();


	private:		
		struct InputSnapshot {
			const std::unordered_set<int> pressedKeys;
			const std::unordered_set<int> pressedMouseButtons;
			const double mouseX;
			const double mouseY;
		};


		bool OnKeyPressedEvent(const KeyPressedEvent& event) override;
		bool OnKeyReleasedEvent(const KeyReleasedEvent& event) override;
		bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent& event) override;
		bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& event) override;
		bool OnMouseMovedEvent(const MouseMovedEvent& event) override;

		ptr<InputSnapshot> currentInput;

		std::unordered_set<int> pressedKeysBuffer;
		std::unordered_set<int> pressedMouseButtonsBuffer;
		double mouseXBuffer;
		double mouseYBuffer;

	};
}
