#include <Common.h>
#include "glfw/glfw3.h"

#include "Window.h"

namespace Astral {
	static bool s_glfwInitialized = false;

	Window::Window(std::string title, uint32_t width, uint32_t height, bool vSync) :
		Window::Window(State{ title, width, height, vSync }) {}

	Window::Window(State state) : state(std::move(state)) {
		AST_CORE_TRACE("Window \"{0}\" being created with dimensions {1}x{2}", this->state.title, this->state.width, this->state.height);

		if (!s_glfwInitialized) {
			int success = glfwInit();
			AST_CORE_ASSERT(success, "glfw init unsuccessful");
			s_glfwInitialized = success;
		}

		handle.reset(glfwCreateWindow(this->state.width, this->state.height, this->state.title.c_str(), nullptr, nullptr));
		AST_CORE_ASSERT(handle, "Failed to create GLFW window");

		glfwMakeContextCurrent(handle.get());
		glfwSetWindowUserPointer(handle.get(), this);
		SetVSync(this->state.vSync);
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

	Window::State Window::GetState() const {
		return state;
	}

	void Window::SetVSync(bool vSync) {
		glfwMakeContextCurrent(handle.get());
		glfwSwapInterval(vSync ? 1 : 0);
		state.vSync = vSync;
	}
}