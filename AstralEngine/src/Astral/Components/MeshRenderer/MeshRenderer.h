#pragma once
#include "Astral/Components/Component.h"
#include "Astral/Assets/Mesh/Mesh.h"
#include "Astral/Assets/Material/Material.h"
#include "Astral/Rendering/Command/Command.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Material/Material.h"

namespace Astral::Components {

	class MeshRenderer : public AComponent {
	public:
		MeshRenderer(Assets::Mesh* mesh = nullptr, Assets::Material* material = nullptr);
		void Draw(std::function<void(Render::ModelData model_data, const Render::IVertexArray* vertexArray, const Render::Material* material)> invoke_draw_call);

		Assets::Mesh* mesh;
		Assets::Material* material;
	};
}

