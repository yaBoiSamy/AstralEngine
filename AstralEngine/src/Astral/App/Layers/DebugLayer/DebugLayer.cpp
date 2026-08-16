#include <Common.h>
#include "DebugLayer.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Astral/App/FrameContext.h"


namespace Astral::App {

	DebugLayer::DebugLayer(std::function<void()> renderImGuiWidgets) :
		ALayer("DebugLayer"),
		renderImGuiWidgets(renderImGuiWidgets) {}


	void DebugLayer::OnUpdate(const FrameContext& context) {
		SetupDebugLayer();
		renderImGuiWidgets();
		RenderDebugLayer();
	}

	void DebugLayer::SetupDebugLayer() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void DebugLayer::RenderDebugLayer() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup);
		}
	}
}
