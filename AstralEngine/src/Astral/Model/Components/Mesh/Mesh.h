#pragma once
#include "Astral/Model/Component.h"
#include "Astral/Model/Assets/MeshData/MeshData.h"

namespace Astral {

	class Mesh : public AComponent {
	public:
		Mesh(const MeshData* meshdata = nullptr);
		void Draw();
		const MeshData* meshdata;
	};
}

