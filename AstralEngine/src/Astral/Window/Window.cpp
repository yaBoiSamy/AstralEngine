#include <Common.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Astral/Events/EventDispatcher.h"

namespace Astral {

	static bool s_glfwInitialized = false;

	Window::Window(GLFWwindow* handle, StateSnapshot stateSnapshot) : handle(handle), state(nullptr) {
		state = std::make_unique<State>(stateSnapshot);
		AST_CORE_TRACE("Window \"{0}\" being created with dimensions {1}x{2}", state->title, state->width, state->height);
		glfwSetWindowUserPointer(handle, state.get());
		SetVSync(state->vSync);

		EventDispatcher<WindowResizeEvent>::Subscribe([this](WindowResizeEvent const& e) {
			state->width = e.width;
			state->height = e.height;
			});
	}

	void Window::GLFWDeleter::operator()(GLFWwindow* w) const noexcept {
		glfwSetWindowUserPointer(w, nullptr);
		if (w) glfwDestroyWindow(w);
	}

	Window::~Window() {}


	void Window::Update() {
		glfwPollEvents();
		glfwSwapBuffers(handle.get());
	}

	Window::StateSnapshot Window::GetState() const {
		return StateSnapshot(*state);
	}

	void Window::SetVSync(bool vSync) {
		glfwSwapInterval(vSync ? 1 : 0);
		state->vSync = vSync;
	}
}