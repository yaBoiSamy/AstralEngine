#include "Common.h"
#include "Mesh.h"

Astral::Mesh::Mesh(MeshData* meshdata) : meshdata(meshdata) {}

void Astral::Mesh::Draw() {
	meshdata->Draw();
}
