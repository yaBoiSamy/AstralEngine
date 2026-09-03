#include "Common.h"
#include "MeshRenderer.h"
#include "Astral/Assets/Mesh/Mesh.h"
#include "Astral/Assets/Material/Material.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Misc/Entity.h"

namespace Astral::Components {

	MeshRenderer::MeshRenderer(Assets::Mesh* mesh, Assets::Material* material) : mesh(mesh), material(material) {}

	void MeshRenderer::Draw(Render::Renderer& renderer) {
		AST_CORE_ASSERT(mesh, "Tried to render using MeshRenderer but no mesh was attached");
		AST_CORE_ASSERT(material, "Tried to render using MeshRenderer but no was material attached");

		renderer.UpdateModelData(Owner()->transform().ModelMatrix());

		std::vector<Render::ResourceBinding> bindings = renderer.GetBindings();
		bindings.push_back(Render::VertexBufferBinding{ VERTEX_BUFFER_BINDING_SLOT, mesh->GetVertexBufferHandle() });
		bindings.push_back(Render::TextureBinding{ ALBEDO_TEXTURE_BINDING_SLOT, material->GetAlbedoTextureHandle() });
		bindings.push_back(Render::UniformBufferBinding{ MATERIAL_DATA_BINDING_SLOT, material->GetMaterialDataHandle() });

		renderer.Command().DrawIndexed(material->GetShaderHandle(), mesh->GetIndexBufferHandle(), std::move(bindings), 0, mesh->GetIndexCount());
	}
}
