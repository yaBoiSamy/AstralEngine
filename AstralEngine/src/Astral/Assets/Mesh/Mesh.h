#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Rendering/Renderer/Renderer.h"


namespace Astral::Assets {

	struct Vertex {
		glm::vec3 position;
		glm::vec2 text_coord;
	};

	class Mesh : public Asset {
	public:
		Mesh(Render::Renderer* renderer, std::string name, std::vector<Vertex> verts, std::vector<uint32_t> indices);
		size_t  GetVertexCount() const;
		size_t  GetIndexCount() const;
		Render::ResourceHandle GetVertexBufferHandle();
		Render::ResourceHandle GetIndexBufferHandle();

	private:
		Render::Renderer* renderer;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		Render::ResourceHandle vertex_buffer_handle;
		Render::ResourceHandle index_buffer_handle;
	};
}


