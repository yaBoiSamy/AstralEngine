#include "Common.h"
#include "Scene.h"
#include "Astral/Model/Components/Mesh/Mesh.h"

namespace Astral {
	void Scene::Draw() {
		for (auto& desc : root.Descendants())
			for (auto& mesh_component : desc.Components<Mesh>())
				mesh_component.Draw();
	}
}