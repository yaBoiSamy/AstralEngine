#include "Common.h"
#include "MeshRenderer.h"
#include "Astral/Assets/Mesh/Mesh.h"
#include "Astral/Assets/Material/Material.h"
#include "Astral/Rendering/Command/Command.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Material/Material.h"
#include "Astral/Misc/Entity.h"

namespace Astral::Components {

	MeshRenderer::MeshRenderer(Assets::Mesh* mesh, Assets::Material* material) : mesh(mesh), material(material) {}

	void MeshRenderer::Draw(std::function<void(Render::ModelData model_data, const Render::IVertexArray* vertexArray, const Render::Material* material)> invoke_draw_call) {
		AST_CORE_ASSERT(mesh, "Tried to render using MeshRenderer but no mesh was attached");
		AST_CORE_ASSERT(material, "Tried to render using MeshRenderer but no was material attached");

		material->Bind();
		invoke_draw_call(
			Owner()->transform().RenderedWorldSpace(),
			mesh->GetRendererVertexArray(),
			material->GetRendererMaterial()
		);
	}
}
