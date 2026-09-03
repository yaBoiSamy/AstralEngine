#include <Common.h>
#include "UILayer.h"
#include "Astral/App/Application/Application.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"

#include <imgui_impl_opengl3.h>
#include <imgui.h>


namespace Astral::App {

	UILayer::UILayer(Application* app, Render::Renderer* renderer, std::function<void()> renderImGuiWidgets) :
		ALayer(app, "UILayer"),
		renderImGuiWidgets(renderImGuiWidgets),
		renderer(renderer) {}


	void UILayer::OnUpdate(const FrameContext& context) {
		renderer->Command().DrawImGui([this, context]() {
			SetupDebugLayer(context);
			renderImGuiWidgets();
			RenderDebugLayer();
		});
	}

	bool UILayer::OnMouseButtonPressedEvent(const Astral::App::MouseButtonPressedEvent& event) {
		return ImGui::GetIO().WantCaptureMouse;
	}

	void UILayer::SetupDebugLayer(const FrameContext& context) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(
			static_cast<float>(context.window_snapshot.frame_width),
			static_cast<float>(context.window_snapshot.frame_height)
		);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}

	void UILayer::RenderDebugLayer() {
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
