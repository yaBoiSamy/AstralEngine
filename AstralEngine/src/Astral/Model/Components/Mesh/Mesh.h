#pragma once
#include "Astral/Model/Component.h"
#include "Astral/Model/Assets/MeshData/MeshData.h"

namespace Astral {

	class Mesh : AComponent {
	public:
		Mesh(const MeshData* meshdata);
		void Draw();
		const MeshData* meshdata;
	};
}

