#pragma once
#include <Common.h>
#include "Astral/Events/EventListener.h"

namespace Astral {
	class InputListener : public EventListener	{
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<double, double> GetMousePosition();
		static void SwapBuffers();


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

		static ptr<InputSnapshot> currentInput;

		static std::unordered_set<int> pressedKeysBuffer;
		static std::unordered_set<int> pressedMouseButtonsBuffer;
		static double mouseXBuffer;
		static double mouseYBuffer;

	};
}
