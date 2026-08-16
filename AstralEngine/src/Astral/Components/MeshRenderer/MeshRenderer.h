#pragma once
#include "Astral/Components/Component.h"
#include "Astral/Assets/Mesh/Mesh.h"
#include "Astral/Assets/Material/Material.h"

namespace Astral::Components {

	class MeshRenderer : public AComponent {
	public:
		MeshRenderer(const Assets::Mesh* mesh = nullptr, const Assets::Material* material = nullptr);
		void Draw();
		const Assets::Mesh* mesh;
		const Assets::Material* material;
	};
}

