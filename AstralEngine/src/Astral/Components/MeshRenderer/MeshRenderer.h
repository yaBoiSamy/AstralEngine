#pragma once
#include "Astral/Components/Component.h"
#include "Astral/Assets/Mesh/Mesh.h"
#include "Astral/Assets/Material/Material.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral::Components {

	class MeshRenderer : public AComponent {
	public:
		MeshRenderer(Assets::Mesh* mesh = nullptr, Assets::Material* material = nullptr);
		void Draw(Render::Renderer& invoker);

		Assets::Mesh* mesh;
		Assets::Material* material;
	};
}

