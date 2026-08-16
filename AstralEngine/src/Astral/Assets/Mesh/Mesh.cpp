#include "Common.h"
#include "Mesh.h"
#include "Astral/Assets/Asset.h"
#include "astral/Rendering/Buffers/Buffers.h"
#include "astral/Rendering/Buffers/VertexArray.h"
#include "astral/Rendering/Buffers/Attributes.h"

namespace Astral::Assets {
	using namespace Render;

	const std::array<AttributeLayout, 2> VERTEX_LAYOUT = {
	   Attr::Vec3::Layout(0, offsetof(Vertex, position)),
	   Attr::Vec2::Layout(1, offsetof(Vertex, text_coord)),
	};

	Mesh::Mesh(
		std::string name,
		std::vector<Vertex> verts, 
		std::vector<uint32_t> idxs) : 
		Asset(name),
		vertices(std::move(verts)), 
		indices(std::move(idxs)),
		gpu_mesh(vertices.size(), indices.size(), UsageHint::Static, VERTEX_LAYOUT) {
		gpu_mesh.WriteVertices(0, vertices);
		gpu_mesh.WriteIndices(0, indices);
	}

	const IVertexArray& Mesh::GetVertexArray() const {
		return static_cast<const IVertexArray&>(gpu_mesh);
	}

}

