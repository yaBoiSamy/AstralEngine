#include <Common.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Astral/Events/EventDispatcher.h"

namespace Astral {

	static bool s_glfwInitialized = false;

	Window::Window(std::string title, uint32_t width, uint32_t height) :
		Window::Window(State{ title, width, height, false }) {}

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

        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        AST_CORE_ASSERT(success, "Failed to populate graphics programming functions");

		glfwSetWindowUserPointer(handle.get(), this);
		SetVSync(this->state.vSync);

        SetGLFWCallbacks();
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

    void Window::SetGLFWCallbacks() {
        glfwSetErrorCallback([](int error, const char* description) {
            AST_CORE_ERROR("GLFW error ({0}): {1}", error, description);
            });

        glfwSetWindowCloseCallback(handle.get(), [](GLFWwindow* window) {
            EventDispatcher<WindowCloseEvent>::Dispatch(
                WindowCloseEvent());
            });

        glfwSetWindowSizeCallback(handle.get(), [](GLFWwindow* window, int width, int height) {
            auto& windowState = *(Window::State*)glfwGetWindowUserPointer(window);
            windowState.width = width;
            windowState.height = height;

            EventDispatcher<WindowResizeEvent>::Dispatch(
                WindowResizeEvent(width, height));
            });

        glfwSetWindowFocusCallback(handle.get(), [](GLFWwindow* window, int focus) {
            if (focus)
                EventDispatcher<WindowFocusEvent>::Dispatch(
                    WindowFocusEvent());
            else
                EventDispatcher<WindowLostFocusEvent>::Dispatch(
                    WindowLostFocusEvent());
            });

        glfwSetWindowPosCallback(handle.get(), [](GLFWwindow* window, int x, int y) {
            EventDispatcher<WindowMovedEvent>::Dispatch(
                WindowMovedEvent(x, y));
            });

        glfwSetKeyCallback(handle.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            switch (action) {
            case GLFW_PRESS:
                EventDispatcher<KeyPressedEvent>::Dispatch(
                    KeyPressedEvent(key, 0));
                break;

            case GLFW_REPEAT:
                EventDispatcher<KeyPressedEvent>::Dispatch(
                    KeyPressedEvent(key, 1));
                break;

            case GLFW_RELEASE:
                EventDispatcher<KeyReleasedEvent>::Dispatch(
                    KeyReleasedEvent(key));
                break;
            }
            });

        glfwSetMouseButtonCallback(handle.get(), [](GLFWwindow* window, int button, int action, int mods) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);

            if (action == GLFW_PRESS)
                EventDispatcher<MouseButtonPressedEvent>::Dispatch(
                    MouseButtonPressedEvent(button, x, y));
            else if (action == GLFW_RELEASE)
                EventDispatcher<MouseButtonReleasedEvent>::Dispatch(
                    MouseButtonReleasedEvent(button, x, y));
            });

        glfwSetCursorPosCallback(handle.get(), [](GLFWwindow* window, double x, double y) {
            EventDispatcher<MouseMovedEvent>::Dispatch(
                MouseMovedEvent(x, y));
            });

        glfwSetScrollCallback(handle.get(), [](GLFWwindow* window, double xOffset, double yOffset) {
            EventDispatcher<MouseScrolledEvent>::Dispatch(
                MouseScrolledEvent(xOffset, yOffset));
            });
    }
}