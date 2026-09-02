#include <Common.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Astral/App/Events/Event/Event.h"
#include "Astral/App/Events/EventHandlers/EventHandlers.h"
#include  "Astral/App/Application/StartupConfig.h"


namespace Astral::App {

	static bool s_glfwInitialized = false;

	Window::Window(const App::StartupConfig& config) : state(State{
		config.window_name,
		0, 0, // Derived from glfwGetWindowPos and window pos callback
		config.window_width,
		config.window_height,
		0, 0, // Derived from glfwGetFramebufferSize and frameBuffer size callback
		false, // Derived from glfwGetWindowAttrib and window focused callback
		config.vsync,
		0.0 // Derived from glfwGetTime in SwapBuffers
	}) {

        int success = glfwInit();
        AST_CORE_ASSERT(success, "glfw init unsuccessful");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.version_minor);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);

        handle = Box<GLFWwindow, GLFWDeleter>(glfwCreateWindow((int)config.window_width, (int)config.window_height, config.window_name.c_str(), nullptr, nullptr));
        AST_CORE_ASSERT(handle.get(), "Failed to create GLFW window");
        glfwSetErrorCallback([](int error, const char* description) {
            AST_CORE_ERROR("GLFW error ({0}): {1}", error, description);
            });


        int x, y;
        glfwGetWindowPos(handle.get(), &x, &y);
        state.x = x;
        state.y = y;

        int fbx, fby;
        glfwGetFramebufferSize(handle.get(), &fbx, &fby);
        state.frame_width = fbx;
        state.frame_height = fby;

        state.focused = (bool)glfwGetWindowAttrib(handle.get(), GLFW_FOCUSED);

		AST_CORE_INFO("Window \"{0}\" being created with dimensions {1}x{2}", state.title, state.width, state.height);
        glfwSetWindowUserPointer(handle.get(), this);

        glfwSetWindowCloseCallback(handle.get(), [](GLFWwindow* handle) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
			window.Broadcast(WindowCloseEvent());
            });

        glfwSetWindowSizeCallback(handle.get(), [](GLFWwindow* handle, int width, int height) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(WindowResizeEvent(width, height));
            window.state.width = width;
            window.state.height = height;
            });

        glfwSetFramebufferSizeCallback(handle.get(), [](GLFWwindow* handle, int frame_width, int frame_height) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(WindowFrameResizeEvent(frame_width, frame_height));
            window.state.frame_width = frame_width;
            window.state.frame_height = frame_height;
            });

        glfwSetWindowFocusCallback(handle.get(), [](GLFWwindow* handle, int focus) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
			window.state.focused = (focus != 0);
            if (focus)
                window.Broadcast(WindowFocusEvent());
            else
                window.Broadcast(WindowLostFocusEvent());
            });

        glfwSetWindowPosCallback(handle.get(), [](GLFWwindow* handle, int x, int y) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(WindowMovedEvent(x, y));
            });

        glfwSetKeyCallback(handle.get(), [](GLFWwindow* handle, int key, int scancode, int action, int mods) {
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

        glfwSetMouseButtonCallback(handle.get(), [](GLFWwindow* handle, int button, int action, int mods) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            double x, y;
            glfwGetCursorPos(handle, &x, &y);
            if (action == GLFW_PRESS)
                window.Broadcast(MouseButtonPressedEvent(button, x, y));
            else if (action == GLFW_RELEASE)
                window.Broadcast(MouseButtonReleasedEvent(button, x, y));
            });

        glfwSetCursorPosCallback(handle.get(), [](GLFWwindow* handle, double x, double y) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(MouseMovedEvent(x, y));
            });

        glfwSetScrollCallback(handle.get(), [](GLFWwindow* handle, double x_offset, double y_offset) {
            Window& window = *(Window*)glfwGetWindowUserPointer(handle);
            window.Broadcast(MouseScrolledEvent(x_offset, y_offset));
            });
	}

    FrameContext Window::GetFrameContext() const {
        return FrameContext{
            GetInputState(),
            GetWindowState(),
        };
    }

    FrameContext::WindowSnapshot Window::GetWindowState() const {
        return FrameContext::WindowSnapshot{
            state.title,
            state.x,
            state.y,
            state.width,
            state.height,
            state.frame_width,
            state.frame_height,
            state.focused,
            state.vsync,
            state.deltatime
        };
    }

    FrameContext::InputSnapshot Window::GetInputState() const {
        std::unordered_set<int> keys;
        std::unordered_set<int> mouse_buttons;

        // Poll keyboard
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
            if (glfwGetKey(handle.get(), key) == GLFW_PRESS)
                keys.insert(key);

        // Poll mouse buttons
        for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
            if (glfwGetMouseButton(handle.get(), button) == GLFW_PRESS)
                mouse_buttons.insert(button);

        // Poll mouse position
        double mouse_x, mouse_y;
        glfwGetCursorPos(handle.get(), &mouse_x, &mouse_y);

        return FrameContext::InputSnapshot{
            std::move(keys),
            std::move(mouse_buttons),
            mouse_x,
            mouse_y
        };
    }

	void Window::GLFWDeleter::operator()(GLFWwindow* w) const noexcept {
		glfwSetWindowUserPointer(w, nullptr);
		if (w) glfwDestroyWindow(w);
	}

    void Window::PumpEvents() {
		glfwPollEvents();
    }

    void Window::MakeContextCurrent() const {
        glfwMakeContextCurrent(handle.get());
    }

	void Window::SetVSync(bool vsync) {
		glfwSwapInterval(vsync ? 1 : 0);
		state.vsync = vsync;
	}

    void Window::SwapBuffers() {
        static double last_frametime = 0;
        double curr_frametime = glfwGetTime();
        state.deltatime = curr_frametime - last_frametime;
        last_frametime = curr_frametime;
        glfwSwapBuffers(handle.get());
    }
}