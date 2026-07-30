#pragma once
#include "Astral/Model/Component.h"
#include "Astral/Model/Assets/Mesh/Mesh.h"

namespace Astral {

	class MeshRenderer : public AComponent {
	public:
		MeshRenderer(const Mesh* mesh = nullptr, const Shader* shader = nullptr);
		void Draw();
		const Mesh* mesh;
		const Shader* shader;
	};
}

