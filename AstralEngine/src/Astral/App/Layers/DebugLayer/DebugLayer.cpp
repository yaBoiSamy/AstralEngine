#include "Common.h"
#include "DebugLayer.h"
#include "Astral/App/Application/Application.h"
#include <imgui.h>


namespace Astral::App {
	struct EnableGrid {
		std::int32_t enable_yz;
		std::int32_t enable_xz;
		std::int32_t enable_xy;
	};

	DebugLayer::DebugLayer(Application* app, Render::Renderer* renderer) : ALayer(app, "Debug Layer"), renderer(renderer) {
		AST_CORE_ASSERT(renderer, "Cannot initialize DebugLayer with null renderer");
	}

	void DebugLayer::OnAttach() {
		Render::VertexLayout grid_layout{
			.attributes = {},
			.bindings = {}
		};
		grid_enabler_handle = renderer->Command().CreateUniformBuffer(sizeof(EnableGrid));
		Assets().CreateShader("Grid", grid_layout, "src/Shaders/Grid/vertex.vert.glsl", "src/Shaders/Grid/fragment.frag.glsl");
	}

	void DebugLayer::OnUpdate(const FrameContext& context) {
		renderer->Command().WriteUniformBuffer(grid_enabler_handle, ToBytes(std::make_unique<EnableGrid>(EnableGrid{ 
			static_cast<int32_t>(enable_yz), 
			static_cast<int32_t>(enable_xz),
			static_cast<int32_t>(enable_xy)
		})));
		std::vector<Render::ResourceBinding> bindings = renderer->GetBindings();
		bindings.push_back(Render::UniformBufferBinding{
			.binding_slot = GRID_ENABLE_SLOT,
			.resource = grid_enabler_handle
		});
		renderer->Command().Draw(Assets().FetchShader("Grid")->GetHandle(), std::move(bindings), 0, 3);
	}

	void DebugLayer::OnRenderUI() {
		ImGui::Begin("Debug grid");
		ImGui::Checkbox("Enable YZ plane", &enable_yz);
		ImGui::Checkbox("Enable XZ plane", &enable_xz);
		ImGui::Checkbox("Enable XY plane", &enable_xy);
		ImGui::End();
	}
}