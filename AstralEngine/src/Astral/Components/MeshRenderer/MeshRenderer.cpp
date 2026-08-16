#include "Common.h"
#include "MeshRenderer.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Assets/Mesh/Mesh.h"
#include "Astral/Assets/Material/Material.h"
#include "Astral/Misc/Entity.h"

namespace Astral::Components {
	using namespace Astral::Assets;
	using namespace Astral::Render;
	MeshRenderer::MeshRenderer(const Mesh* mesh, const Material* material) : mesh(mesh), material(material) {}

	void MeshRenderer::Draw() {
		AST_CORE_ASSERT(mesh, "Tried to render using MeshRenderer but no mesh was attached");
		AST_CORE_ASSERT(material, "Tried to render using MeshRenderer but no was material attached");
		Owner()->transform().UpdateRenderedWorldSpace();

		material->Bind();
		Renderer::Submit(mesh->GetVertexArray());
	}
}
