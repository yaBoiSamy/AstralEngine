#include <Common.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Astral {

	static bool s_glfwInitialized = false;

	Window::Window(GLFWwindow* handle, State _state, std::function<void()> imguiSetup) : handle(handle), state(std::make_unique<State>(_state)) {
		AST_CORE_INFO("Window \"{0}\" being created with dimensions {1}x{2}", state->title, state->width, state->height);
		glfwSetWindowUserPointer(handle, this);
		SetVSync(state->vsync);

        glfwSetWindowCloseCallback(handle, [](GLFWwindow* handle) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
			window.Broadcast(WindowCloseEvent());
            });

        glfwSetWindowSizeCallback(handle, [](GLFWwindow* handle, int width, int height) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(WindowResizeEvent(width, height));
            window.state->width = width;
            window.state->height = height;
            });

        glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* handle, int frame_width, int frame_height) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(WindowFrameResizeEvent(frame_width, frame_height));
            window.state->frame_width = frame_width;
            window.state->frame_height = frame_height;
            });

        glfwSetWindowFocusCallback(handle, [](GLFWwindow* handle, int focus) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
			window.state->focused = (focus != 0);
            if (focus)
                window.Broadcast(WindowFocusEvent());
            else
                window.Broadcast(WindowLostFocusEvent());
            });

        glfwSetWindowPosCallback(handle, [](GLFWwindow* handle, int x, int y) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(WindowMovedEvent(x, y));
            });

        glfwSetKeyCallback(handle, [](GLFWwindow* handle, int key, int scancode, int action, int mods) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            switch (action) {
            case GLFW_PRESS:
                window.Broadcast(KeyPressedEvent(key, 0));
                break;
            case GLFW_REPEAT:
                window.Broadcast(KeyPressedEvent(key, 1));
                break;
            case GLFW_RELEASE:
                window.Broadcast(KeyReleasedEvent(key));
                break;
            }
            });

        glfwSetMouseButtonCallback(handle, [](GLFWwindow* handle, int button, int action, int mods) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            double x, y;
            glfwGetCursorPos(handle, &x, &y);
            if (action == GLFW_PRESS)
                window.Broadcast(MouseButtonPressedEvent(button, x, y));
            else if (action == GLFW_RELEASE)
                window.Broadcast(MouseButtonReleasedEvent(button, x, y));
            });

        glfwSetCursorPosCallback(handle, [](GLFWwindow* handle, double x, double y) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(MouseMovedEvent(x, y));
            });

        glfwSetScrollCallback(handle, [](GLFWwindow* handle, double xOffset, double yOffset) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(MouseScrolledEvent(xOffset, yOffset));
            });

        imguiSetup();

        if (state->vsync)
            glfwSwapInterval(1);
	}

    FrameContext Window::GetFrameContext() const {
        return FrameContext{
            GetInputState(),
            GetWindowState(),
        };
    }

    FrameContext::WindowSnapshot Window::GetWindowState() const {
        return FrameContext::WindowSnapshot{
            state->title,
            state->x,
            state->y,
            state->width,
            state->height,
            state->frame_width,
            state->frame_height,
            state->focused,
            state->vsync,
            state->deltatime
        };
    }

    FrameContext::InputSnapshot Window::GetInputState() const {
        std::unordered_set<int> keys;
        std::unordered_set<int> mouseButtons;

        // Poll keyboard
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
            if (glfwGetKey(handle.get(), key) == GLFW_PRESS)
                keys.insert(key);

        // Poll mouse buttons
        for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
            if (glfwGetMouseButton(handle.get(), button) == GLFW_PRESS)
                mouseButtons.insert(button);

        // Poll mouse position
        double mouseX, mouseY;
        glfwGetCursorPos(handle.get(), &mouseX, &mouseY);

        return FrameContext::InputSnapshot{
            std::move(keys),
            std::move(mouseButtons),
            mouseX,
            mouseY
        };
    }

	void Window::GLFWDeleter::operator()(GLFWwindow* w) const noexcept {
		glfwSetWindowUserPointer(w, nullptr);
		if (w) glfwDestroyWindow(w);
	}

    void Window::PumpEvents() {
		glfwPollEvents();
    }

    void Window::SwapBuffers() {
        static double last_frametime = 0;
        double curr_frametime = glfwGetTime();
        state->deltatime = curr_frametime - last_frametime;
        last_frametime = curr_frametime;
        glfwSwapBuffers(handle.get());
    }

	void Window::SetVSync(bool vsync) {
		glfwSwapInterval(vsync ? 1 : 0);
		state->vsync = vsync;
	}
}