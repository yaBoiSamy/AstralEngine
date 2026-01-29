#include <Common.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Astral {

	static bool s_glfwInitialized = false;

	Window::Window(GLFWwindow* handle, StateSnapshot stateSnapshot, std::function<void()> imguiSetup) : handle(handle), state(nullptr) {
		state = std::make_unique<State>(stateSnapshot);
		AST_CORE_TRACE("Window \"{0}\" being created with dimensions {1}x{2}", state->title, state->width, state->height);
		glfwSetWindowUserPointer(handle, this);
		SetVSync(state->vSync);

        glfwSetWindowCloseCallback(handle, [](GLFWwindow* handle) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
			window.callback(WindowCloseEvent());
            });

        glfwSetWindowSizeCallback(handle, [](GLFWwindow* handle, int width, int height) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.callback(WindowResizeEvent(width, height));
            window.state->width = width;
            window.state->height = height;
            });

        glfwSetWindowFocusCallback(handle, [](GLFWwindow* handle, int focus) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            if (focus)
                window.callback(WindowFocusEvent());
            else
                window.callback(WindowLostFocusEvent());
            });

        glfwSetWindowPosCallback(handle, [](GLFWwindow* handle, int x, int y) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.callback(WindowMovedEvent(x, y));
            });

        glfwSetKeyCallback(handle, [](GLFWwindow* handle, int key, int scancode, int action, int mods) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            switch (action) {
            case GLFW_PRESS:
                window.callback(KeyPressedEvent(key, 0));
                break;
            case GLFW_REPEAT:
                window.callback(KeyPressedEvent(key, 1));
                break;
            case GLFW_RELEASE:
                window.callback(KeyReleasedEvent(key));
                break;
            }
            });

        glfwSetMouseButtonCallback(handle, [](GLFWwindow* handle, int button, int action, int mods) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            double x, y;
            glfwGetCursorPos(handle, &x, &y);
            if (action == GLFW_PRESS)
                window.callback(MouseButtonPressedEvent(button, x, y));
            else if (action == GLFW_RELEASE)
                window.callback(MouseButtonReleasedEvent(button, x, y));
            });

        glfwSetCursorPosCallback(handle, [](GLFWwindow* handle, double x, double y) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.callback(MouseMovedEvent(x, y));
            });

        glfwSetScrollCallback(handle, [](GLFWwindow* handle, double xOffset, double yOffset) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.callback(MouseScrolledEvent(xOffset, yOffset));
            });

        imguiSetup();
	}

	void Window::GLFWDeleter::operator()(GLFWwindow* w) const noexcept {
		glfwSetWindowUserPointer(w, nullptr);
		if (w) glfwDestroyWindow(w);
	}

	Window::~Window() {}

	void Window::SetCallback(std::function<void(const Event&)> callback) {
		this->callback = callback;
	}


	double Window::GetDeltaTime() const {
		return glfwGetTime();
	}

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