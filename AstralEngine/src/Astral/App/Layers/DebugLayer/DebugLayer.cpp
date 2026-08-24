#include <Common.h>
#include "DebugLayer.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"


namespace Astral::App {

	DebugLayer::DebugLayer(Render::Renderer* renderer, std::function<void()> renderImGuiWidgets) :
		ALayer("DebugLayer"),
		renderImGuiWidgets(renderImGuiWidgets),
		renderer(renderer) {}


	void DebugLayer::OnUpdate(const FrameContext& context) {
		SetupDebugLayer(context);
		renderImGuiWidgets();
		RenderDebugLayer();
	}

	void DebugLayer::SetupDebugLayer(const FrameContext& context) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(
			static_cast<float>(context.window_snapshot.width),
			static_cast<float>(context.window_snapshot.height)
		);
		ImGui::NewFrame();
	}

	void DebugLayer::RenderDebugLayer() {
		ImGui::Render();
		renderer->Command().DrawImGui();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup);
		}
	}
}
