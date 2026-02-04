#include "Common.h"
#include "InputListener.h"


namespace Astral {
	bool InputListener::IsKeyPressed(int keycode){
		return currentInput->pressedKeys.contains(keycode);
	}

	bool InputListener::IsMouseButtonPressed(int button) {
		return currentInput->pressedMouseButtons.contains(button);
	}

	std::pair<double, double> InputListener::GetMousePosition() {
		return { currentInput->mouseX, currentInput->mouseY};
	}

	void InputListener::SwapBuffers() {
		currentInput = std::make_unique<InputSnapshot>(
			pressedKeysBuffer, 
			pressedMouseButtonsBuffer, 
			mouseXBuffer, 
			mouseYBuffer
		);
	}


	bool InputListener::OnKeyPressedEvent(const KeyPressedEvent& event) {
		pressedKeysBuffer.insert(event.keycode);
		return false;
	}

	bool InputListener::OnKeyReleasedEvent(const KeyReleasedEvent& event) {
		pressedKeysBuffer.erase(event.keycode);
		return false;
	}

	bool InputListener::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& event) {
		pressedMouseButtonsBuffer.insert(event.button);
		return false;
	}

	bool InputListener::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& event) {
		pressedMouseButtonsBuffer.erase(event.button);
		return false;
	}

	bool InputListener::OnMouseMovedEvent(const MouseMovedEvent& event) {
		mouseXBuffer = event.x;
		mouseYBuffer = event.y;
		return false;
	}


	ptr<InputListener::InputSnapshot> InputListener::currentInput = nullptr;

	std::unordered_set<int> InputListener::pressedKeysBuffer{};
	std::unordered_set<int> InputListener::pressedMouseButtonsBuffer{};
	double InputListener::mouseXBuffer = 0.0;
	double InputListener::mouseYBuffer = 0.0;
}
