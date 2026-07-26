#include "Common.h"
#include "Mesh.h"

namespace Astral {

	Mesh::Mesh(const MeshData* meshdata) : meshdata(meshdata) {}

	void Mesh::Draw() {
		AST_CORE_ASSERT(meshdata, "Tried to render mesh component with no mesh data attached");
		meshdata->Draw();
	}
}
