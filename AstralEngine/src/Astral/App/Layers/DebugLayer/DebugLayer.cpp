#include <Common.h>
#include "DebugLayer.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"

#include <imgui_impl_opengl3.h>
#include <imgui.h>


namespace Astral::App {

	DebugLayer::DebugLayer(Render::Renderer* renderer, std::function<void()> renderImGuiWidgets) :
		ALayer("DebugLayer"),
		renderImGuiWidgets(renderImGuiWidgets),
		renderer(renderer) {}


	void DebugLayer::OnUpdate(const FrameContext& context) {
		renderer->Command().DrawImGui([this, context]() {
			SetupDebugLayer(context);
			renderImGuiWidgets();
			RenderDebugLayer();
		});
	}

	void DebugLayer::SetupDebugLayer(const FrameContext& context) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(
			static_cast<float>(context.window_snapshot.frame_width),
			static_cast<float>(context.window_snapshot.frame_height)
		);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}

	void DebugLayer::RenderDebugLayer() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	GLFWwindow* backup = glfwGetCurrentContext();
		//	ImGui::UpdatePlatformWindows();
		//	ImGui::RenderPlatformWindowsDefault();
		//	glfwMakeContextCurrent(backup);
		//}
	}
}
