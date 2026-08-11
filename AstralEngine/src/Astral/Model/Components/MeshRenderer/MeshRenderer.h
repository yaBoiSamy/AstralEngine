#pragma once
#include "Astral/Model/Component.h"
#include "Astral/Model/Assets/Mesh/Mesh.h"
#include "Astral/Model/Assets/Material/Material.h"

namespace Astral {

	class MeshRenderer : public AComponent {
	public:
		MeshRenderer(const Mesh* mesh = nullptr, const Material* material = nullptr);
		void Draw();
		const Mesh* mesh;
		const Material* material;
	};
}

