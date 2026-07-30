#pragma once
#include "Common.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Buffers/Attributes.h"
#include "Astral/Rendering/Shader/Shader.h"


namespace Astral {

	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	extern const std::array<AttributeLayout, 2> VERTEX_LAYOUT;

	class Mesh {
	public:
		Mesh(std::vector<Vertex> verts, std::vector<uint32_t> indices);

		void Draw(const Shader& shader) const;

	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		VertexArray<Vertex> gpu_mesh;
	};
}


