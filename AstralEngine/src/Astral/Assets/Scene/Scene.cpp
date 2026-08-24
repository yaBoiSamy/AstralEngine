#include "Common.h"
#include "Scene.h"
#include "Astral/Components/Camera/Camera.h"
#include "Astral/Components/MeshRenderer/MeshRenderer.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral::Assets {
	using namespace Components;

	Scene::Scene(std::string name) : 
		Asset(name), 
		root(name),
		main_camera(nullptr) {}

	void Scene::SetMainCam(Camera* cam) {
		main_camera = cam;
	}

	void Scene::Draw(Render::Renderer& renderer, uint32_t frame_width, uint32_t frame_height) {
		AST_CORE_ASSERT(main_camera, "A main camera must be attached to the scene for it to be rendered");
		if (frame_width == 0 || frame_height == 0)
			return;

		const glm::vec4 CLEAR_COLOR = glm::vec4();

		renderer.UpdateLightingData(Render::LightingData{});
		renderer.UpdateCameraData(main_camera->RenderedPOV(frame_width, frame_height));

		for (auto& desc : root.Descendants()) {
			for (auto& mesh_component : desc.Components<MeshRenderer>()) {
				mesh_component.Draw(renderer);
			}
		}
	}
}