#include "Common.h"
#include "Scene.h"
#include "Astral/Components/Camera/Camera.h"
#include "Astral/Components/MeshRenderer/MeshRenderer.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral::Assets {
	using namespace Components;

	Scene::Scene(Render::Renderer* renderer, std::string name) : 
		Asset(name), 
		renderer(renderer),
		root(name),
		main_camera(nullptr) {}

	void Scene::SetMainCam(Camera* cam) {
		main_camera = cam;
	}

	void Scene::Draw(uint32_t frame_width, uint32_t frame_height) {
		AST_CORE_ASSERT(main_camera, "A main camera must be attached to the scene for it to be rendered");
		if (frame_width == 0 || frame_height == 0)
			return;

		renderer->UpdateLightingData();
		renderer->UpdateCameraData(
			main_camera->ViewMatrix(),
			main_camera->ProjectionMatrix(frame_width, frame_height)
		);

		for (auto& desc : root.Descendants()) {
			for (auto& mesh_component : desc.Components<MeshRenderer>()) {
				mesh_component.Draw(*renderer);
			}
		}
	}
}