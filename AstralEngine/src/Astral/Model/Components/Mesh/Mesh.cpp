#include "Common.h"
#include "Mesh.h"

namespace Astral {

	Mesh::Mesh(const MeshData* meshdata) : meshdata(meshdata) {}

	void Mesh::Draw() {
		meshdata->Draw();
	}
}
