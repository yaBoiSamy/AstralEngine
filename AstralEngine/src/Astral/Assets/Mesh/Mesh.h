#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Buffers/Attributes.h"


namespace Astral::Assets {

	struct Vertex {
		glm::vec3 position;
		glm::vec2 text_coord;
	};

	extern const std::array<Render::AttributeLayout, 2> VERTEX_LAYOUT;

	class Mesh : public Asset {
	public:
		Mesh(std::string name, std::vector<Vertex> verts, std::vector<uint32_t> indices);
		const Render::IVertexArray& GetVertexArray() const;

	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		Render::VertexArray<Vertex> gpu_mesh;
	};
}


