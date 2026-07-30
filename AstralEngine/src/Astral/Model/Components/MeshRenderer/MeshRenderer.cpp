#include "Common.h"
#include "MeshRenderer.h"
#include "Astral/Model/Entity.h"

namespace Astral {

	MeshRenderer::MeshRenderer(const Mesh* mesh, const Shader* shader) : mesh(mesh), shader(shader) {}

	void MeshRenderer::Draw() {
		AST_CORE_ASSERT(mesh, "Tried to render using MeshRenderer but no mesh was attached");
		AST_CORE_ASSERT(shader, "Tried to render using MeshRenderer but no was shader attached");
		Owner()->transform().UpdateRenderedWorldSpace();
		mesh->Draw(*shader);
	}
}
