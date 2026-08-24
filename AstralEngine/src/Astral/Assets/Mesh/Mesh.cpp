#include "Common.h"
#include "Mesh.h"

namespace Astral::Assets {
	using namespace Render;

	const std::array<VertexAttribute, 2> ATTRIBUTES = {
	   Attr::Vec3::Layout(0, 0, offsetof(Vertex, position)),
	   Attr::Vec2::Layout(1, 0, offsetof(Vertex, text_coord))
	};

	const std::array<VertexBinding, 1> BINDINGS = {
		{ 0, 0 }
	};

	Mesh::Mesh(
		Render::Renderer* renderer,
		std::string name,
		std::vector<Vertex> verts, 
		std::vector<uint32_t> idxs) : 
		Asset(name),
		renderer(renderer),
		vertices(std::move(verts)), 
		indices(std::move(idxs)),
		vertex_buffer_handle(renderer->Command().CreateVertexBuffer(vertices.size(), sizeof(Vertex))),
		index_buffer_handle(renderer->Command().CreateIndexBuffer(indices.size())) 
	{
		renderer->Command().WriteVertexBuffer(vertex_buffer_handle, ToBytesArray(vertices), vertices.size());
		renderer->Command().WriteIndexBuffer(index_buffer_handle, ToBytesArray(indices), indices.size());
	}

	Render::ResourceHandle Mesh::GetVertexBufferHandle() {
		return vertex_buffer_handle;
	}

	Render::ResourceHandle Mesh::GetIndexBufferHandle() {
		return index_buffer_handle;
	}

}

