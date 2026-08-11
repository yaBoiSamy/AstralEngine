#pragma once
#include "Common.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Buffers/Attributes.h"


namespace Astral {

	struct Vertex {
		glm::vec3 position;
		glm::vec2 text_coord;
	};

	extern const std::array<AttributeLayout, 2> VERTEX_LAYOUT;

	class Mesh {
	public:
		Mesh(std::vector<Vertex> verts, std::vector<uint32_t> indices);
		const IVertexArray& GetVertexArray() const;

	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		VertexArray<Vertex> gpu_mesh;
	};
}


