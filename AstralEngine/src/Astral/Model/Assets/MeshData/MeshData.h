#pragma once
#include "Astral/Rendering/VertexArray/VertexArray.h"
#include "Astral/Rendering/VertexArray/Attributes.h"
#include <glm/glm.hpp>

namespace Astral {

	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	extern const std::array<AttributeLayout, 2> VERTEX_LAYOUT;

	class MeshData {
	public:
		MeshData(std::vector<Vertex> verts, std::vector<uint32_t> indices);

		void Draw();

	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		VertexArray<Vertex> gpu_mesh;
	};
}


