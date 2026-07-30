#include "Common.h"
#include "Scene.h"
#include "Astral/Model/Components/MeshRenderer/MeshRenderer.h"

namespace Astral {
	Scene::Scene() : main_camera(nullptr) {}

	void Scene::SetMainCam(Camera* cam) {
		main_camera = cam;
	}

	void Scene::Draw() {
		AST_CORE_ASSERT(main_camera, "A main camera must be attached to the scene to render stuff");
		main_camera->UpdateRenderedPOV();

		for (auto& desc : root.Descendants())
			for (auto& mesh_component : desc.Components<MeshRenderer>())
				mesh_component.Draw();
	}
}