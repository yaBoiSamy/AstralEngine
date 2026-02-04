#include "Common.h"
#include "DebugLayer.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Astral/Window/FrameContext.h"


namespace Astral
{
	DebugLayer::DebugLayer(std::function<void()> renderImGuiWidgets) :
		ALayer("DebugLayer"),
		renderImGuiWidgets(renderImGuiWidgets) {}


	void DebugLayer::OnUpdate(const FrameContext& context) {
		Begin(context);
		renderImGuiWidgets();
		End(context);
	}

	void DebugLayer::Begin(const FrameContext& context) {
		FrameContext::WindowSnapshot ws = context.windowSnapshot;

		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = (float)context.deltaTime;
		io.DisplaySize = ImVec2(
			(float)ws.width,
			(float)ws.height
		);
		io.DisplayFramebufferScale = ImVec2(
			(float)ws.framebufferSizeX / (float)ws.width,
			(float)ws.framebufferSizeY / (float)ws.height
		);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void DebugLayer::OnImGuiRender() {
		bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void DebugLayer::End(const FrameContext& context) {


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
