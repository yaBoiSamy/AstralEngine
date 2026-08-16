#include "Common.h"
#include "Scene.h"
#include "Astral/Components/Camera/Camera.h"
#include "Astral/Components/MeshRenderer/MeshRenderer.h"
#include "Astral/Assets/Asset.h"

namespace Astral::Assets {
	using namespace Components;

	Scene::Scene(std::string name) : Asset(name), main_camera(nullptr), root(name) {}

	void Scene::SetMainCam(Camera* cam) {
		main_camera = cam;
	}

	void Scene::Draw(uint32_t frame_width, uint32_t frame_height) {
		AST_CORE_ASSERT(main_camera, "A main camera must be attached to the scene to render stuff");
		if (frame_width == 0 || frame_height == 0)
			return;
		main_camera->UpdateRenderedPOV(frame_width, frame_height);

		for (auto& desc : root.Descendants())
			for (auto& mesh_component : desc.Components<MeshRenderer>())
				mesh_component.Draw();
	}
}