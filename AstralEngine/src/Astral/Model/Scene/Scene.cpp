#include "Common.h"
#include "Scene.h"
#include "Astral/Model/Components/MeshRenderer/MeshRenderer.h"

namespace Astral {
	Scene::Scene(Application* app, std::string name, ALayer* layer) : main_camera(nullptr), root("Scene", layer), app(app) {}

	void Scene::SetMainCam(Camera* cam) {
		main_camera = cam;
	}

	void Scene::Draw() {
		AST_CORE_ASSERT(main_camera, "A main camera must be attached to the scene to render stuff");
		FrameContext ctxt = app->GetFrameContext();
		uint32_t fbx = ctxt.window_snapshot.frame_width;
		uint32_t fby = ctxt.window_snapshot.frame_height;
		if (fbx == 0 || fby == 0)
			return;
		main_camera->UpdateRenderedPOV(fbx, fby);

		for (auto& desc : root.Descendants())
			for (auto& mesh_component : desc.Components<MeshRenderer>())
				mesh_component.Draw();
	}
}