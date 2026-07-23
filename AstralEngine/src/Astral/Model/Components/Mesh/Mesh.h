#pragma once
#include "Astral/Model/Component.h"
#include "Astral/Model/Assets/MeshData/MeshData.h"

namespace Astral {

	class Mesh : AComponent {
	public:
		Mesh(MeshData* meshdata);
		void Draw();
		MeshData* meshdata;
	};
}

