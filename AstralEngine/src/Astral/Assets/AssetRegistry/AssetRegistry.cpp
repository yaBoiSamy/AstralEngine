#include "Common.h"
#include "AssetRegistry.h"


namespace Astral::Assets {

	AssetRegistry::AssetRegistry(Render::Renderer* renderer) : renderer(renderer) {
		blank_texture = CreateTexture("blank", "resources/blank_texture.png");
	}

	Shader* AssetRegistry::CreateShader(std::string name, Render::VertexLayout& layout, std::filesystem::path vertex_path, std::filesystem::path fragement_path) {
		shader_directory.emplace(name, std::make_unique<Shader>(renderer, name, layout, vertex_path, fragement_path));
		return FetchShader(name);
	}

	Texture* AssetRegistry::CreateTexture(std::string name, std::filesystem::path texture_path) {
		texture_directory.emplace(name, std::make_unique<Texture>(renderer, name, texture_path));
		return FetchTexture(name);
	}

	Material* AssetRegistry::CreateMaterial(std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture) {
		material_directory.emplace(name, std::make_unique<Material>(renderer, blank_texture, name, shader, albedo, albedo_texture));
		return FetchMaterial(name);
	}

	Mesh* AssetRegistry::CreateMesh(std::string name, std::vector<Vertex> verts, std::vector<uint32_t> indices) {
		mesh_directory.emplace(name, std::make_unique<Mesh>(renderer, name, std::move(verts), std::move(indices)));
		return FetchMesh(name);
	}

	Scene* AssetRegistry::CreateScene(std::string name) {
		scene_directory.emplace(name, std::make_unique<Scene>(name));
		return FetchScene(name);
	}

	Shader* AssetRegistry::FetchShader(const std::string& name) const {
		return Fetch(name, shader_directory);
	}

	Texture* AssetRegistry::FetchTexture(const std::string& name) const {
		return Fetch(name, texture_directory);
	}

	Material* AssetRegistry::FetchMaterial(const std::string& name) const {
		return Fetch(name, material_directory);
	}

	Mesh* AssetRegistry::FetchMesh(const std::string& name) const {
		return Fetch(name, mesh_directory);
	}

	Scene* AssetRegistry::FetchScene(const std::string& name) const {
		return Fetch(name, scene_directory);
	}
}