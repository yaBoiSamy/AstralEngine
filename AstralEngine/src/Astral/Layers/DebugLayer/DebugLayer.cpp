#include "Common.h"
#include "DebugLayer.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace Astral
{
	DebugLayer::DebugLayer(std::function<double()> getDeltaTime, std::function<Window::StateSnapshot()> getWindowState) :
		ALayer("DebugLayer"), GetDeltaTime(getDeltaTime), GetWindowState(getWindowState) {}

	DebugLayer::~DebugLayer() {}

	void DebugLayer::OnAttach() {}
	void DebugLayer::OnDetach() {}

	void DebugLayer::OnUpdate() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = (float)GetDeltaTime();
		Window::StateSnapshot snapshot = GetWindowState();
		io.DisplaySize = ImVec2((float)snapshot.width, (float)snapshot.height);

		bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
