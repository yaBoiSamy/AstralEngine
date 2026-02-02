#include "Common.h"
#include "Input.h"


namespace Astral {
	bool Input::IsKeyPressed(int keycode){
		return currentInput->pressedKeys.contains(keycode);
	}

	bool Input::IsMouseButtonPressed(int button) {
		return currentInput->pressedMouseButtons.contains(button);
	}

	std::pair<double, double> Input::GetMousePosition() {
		return { currentInput->mouseX, currentInput->mouseY};
	}

	void Input::SwapBuffers() {
		currentInput = std::make_unique<InputSnapshot>(
			pressedKeysBuffer, 
			pressedMouseButtonsBuffer, 
			mouseXBuffer, 
			mouseYBuffer
		);
	}


	bool Input::OnKeyPressedEvent(const KeyPressedEvent& event) {
		pressedKeysBuffer.insert(event.keycode);
		return false;
	}

	bool Input::OnKeyReleasedEvent(const KeyReleasedEvent& event) {
		pressedKeysBuffer.erase(event.keycode);
		return false;
	}

	bool Input::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& event) {
		pressedMouseButtonsBuffer.insert(event.button);
		return false;
	}

	bool Input::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& event) {
		pressedMouseButtonsBuffer.erase(event.button);
		return false;
	}

	bool Input::OnMouseMovedEvent(const MouseMovedEvent& event) {
		mouseXBuffer = event.x;
		mouseYBuffer = event.y;
		return false;
	}


	ptr<Input::InputSnapshot> Input::currentInput = nullptr;

	std::unordered_set<int> Input::pressedKeysBuffer{};
	std::unordered_set<int> Input::pressedMouseButtonsBuffer{};
	double Input::mouseXBuffer = 0.0;
	double Input::mouseYBuffer = 0.0;
}
