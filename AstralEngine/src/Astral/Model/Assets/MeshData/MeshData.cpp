#include "Common.h"
#include "MeshData.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral {

	const std::array<AttributeLayout, 2> VERTEX_LAYOUT = {
	   Attr::Vec3::Layout(0, offsetof(Vertex, position)),
	   Attr::Vec4::Layout(1, offsetof(Vertex, color)),
	};

	MeshData::MeshData(
		std::vector<Vertex> verts, 
		std::vector<uint32_t> idxs) : 
		vertices(std::move(verts)), 
		indices(std::move(idxs)),
		gpu_mesh(vertices.size(), indices.size(), UsageHint::Static, VERTEX_LAYOUT) {
		gpu_mesh.WriteVertices(0, vertices);
		gpu_mesh.WriteIndices(0, indices);
	}

	void MeshData::Draw() const {
		Renderer::Submit(gpu_mesh);
	}
}

