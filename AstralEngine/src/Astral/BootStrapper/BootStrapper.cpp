#include "Common.h"
#include "BootStrapper.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Astral/Window/Window.h"
#include "Astral/Events/Event.h"
#include "Astral/Events/EventDispatcher.h"

namespace Astral {
    const char* ToGLSLVersion(int major, int minor)
    {
        if (major == 3 && minor == 0) return "#version 130";
        if (major == 3 && minor == 1) return "#version 140";
        if (major == 3 && minor == 2) return "#version 150";
        if (major == 3 && minor == 3) return "#version 330";
        if (major == 4 && minor == 0) return "#version 400";
        if (major == 4 && minor == 1) return "#version 410";
        if (major == 4 && minor == 2) return "#version 420";
        if (major == 4 && minor == 3) return "#version 430";
        if (major == 4 && minor == 4) return "#version 440";
        if (major == 4 && minor == 5) return "#version 450";
        if (major == 4 && minor == 6) return "#version 460";

        AST_CORE_ASSERT(false, "Unsupported OpenGL version");
        return "";
    }


    // Make Callbacks wrapped by Dispatcher, then make window class subscribe to events
    void SetGLFWCallbacks(GLFWwindow* windowHandle) {
        glfwSetErrorCallback([](int error, const char* description) {
            AST_CORE_ERROR("GLFW error ({0}): {1}", error, description);
            });

        glfwSetWindowCloseCallback(windowHandle, [](GLFWwindow* window) {
            EventDispatcher<WindowCloseEvent>::Dispatch(
                WindowCloseEvent());
            });

        glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height) {
            auto& windowState = *(Window::State*)glfwGetWindowUserPointer(window);
            EventDispatcher<WindowResizeEvent>::Dispatch(
                WindowResizeEvent(width, height));
            });

        glfwSetWindowFocusCallback(windowHandle, [](GLFWwindow* window, int focus) {
            if (focus)
                EventDispatcher<WindowFocusEvent>::Dispatch(
                    WindowFocusEvent());
            else
                EventDispatcher<WindowLostFocusEvent>::Dispatch(
                    WindowLostFocusEvent());
            });

        glfwSetWindowPosCallback(windowHandle, [](GLFWwindow* window, int x, int y) {
            EventDispatcher<WindowMovedEvent>::Dispatch(
                WindowMovedEvent(x, y));
            });

        glfwSetKeyCallback(windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
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

        glfwSetMouseButtonCallback(windowHandle, [](GLFWwindow* window, int button, int action, int mods) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);

            if (action == GLFW_PRESS)
                EventDispatcher<MouseButtonPressedEvent>::Dispatch(
                    MouseButtonPressedEvent(button, x, y));
            else if (action == GLFW_RELEASE)
                EventDispatcher<MouseButtonReleasedEvent>::Dispatch(
                    MouseButtonReleasedEvent(button, x, y));
            });

        glfwSetCursorPosCallback(windowHandle, [](GLFWwindow* window, double x, double y) {
            EventDispatcher<MouseMovedEvent>::Dispatch(
                MouseMovedEvent(x, y));
            });

        glfwSetScrollCallback(windowHandle, [](GLFWwindow* window, double xOffset, double yOffset) {
            EventDispatcher<MouseScrolledEvent>::Dispatch(
                MouseScrolledEvent(xOffset, yOffset));
            });
    }

    Window WindowStartup(const StartupConfig& config) {

        // GLFW initialization
        int success = glfwInit();
        AST_CORE_ASSERT(success, "glfw init unsuccessful");

       // OpenGL Versioning
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.glMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.glMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window with graphics context
        float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
        GLFWwindow* window = glfwCreateWindow((int)(config.resolutionWidth * main_scale), (int)(config.resolutionHeight * main_scale), config.windowName.c_str(), nullptr, nullptr);
        AST_CORE_ASSERT(window, "Failed to create GLFW window");
        glfwMakeContextCurrent(window);
        SetGLFWCallbacks(window);

		// Load OpenGL functions using glad
        success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        AST_CORE_ASSERT(success, "Failed to populate graphics programming functions");

		// Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

        // Styling
        ImGui::StyleColorsDark();

		// Scaling  TODO: Dynamic scaling
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(main_scale);
        style.FontScaleDpi = main_scale;

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(ToGLSLVersion(config.glMajor, config.glMinor));

        return Window(window, Window::StateSnapshot(config.windowName, config.resolutionWidth, config.resolutionHeight, config.vSync));
    }
}