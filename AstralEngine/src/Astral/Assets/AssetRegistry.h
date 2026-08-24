#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Assets/Material/Material.h"
#include "Astral/Assets/Mesh/Mesh.h"
#include "Astral/Assets/Scene/Scene.h"
#include "Astral/Assets/Shader/Shader.h"
#include "Astral/Assets/Texture/Texture.h"

namespace Astral::Assets {

	template<typename T>
	concept AssetType = std::derived_from<T, Asset>;


	class AssetRegistry {
	public:
		AssetRegistry(Render::Renderer* renderer) : renderer(renderer) {}

		Shader* CreateShader(std::string name, Render::VertexLayout& layout, std::filesystem::path vertex_path, std::filesystem::path fragement_path);
		Texture* CreateTexture(std::string name, std::filesystem::path texture_path);
		Material* CreateMaterial(std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture = nullptr);
		Mesh* CreateMesh(std::string name, std::vector<Vertex> verts, std::vector<uint32_t> indices);
		Scene* CreateScene(std::string name);

		Shader* FetchShader(const std::string& name) const;
		Texture* FetchTexture(const std::string& name) const;
		Material* FetchMaterial(const std::string& name) const;
		Mesh* FetchMesh(const std::string& name) const;
		Scene* FetchScene(const std::string& name) const;

	private:
		template<AssetType AssetT>
		AssetT* Fetch(const std::string& name, const std::unordered_map<std::string, Box<AssetT>>& directory) const;

		std::unordered_map<std::string, Box<Shader>> shader_directory;
		std::unordered_map<std::string, Box<Texture>> texture_directory;
		std::unordered_map<std::string, Box<Material>> material_directory;
		std::unordered_map<std::string, Box<Mesh>> mesh_directory;
		std::unordered_map<std::string, Box<Scene>> scene_directory;

		Render::Renderer* renderer;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	inline Shader* AssetRegistry::CreateShader(std::string name, Render::VertexLayout& layout, std::filesystem::path vertex_path, std::filesystem::path fragement_path) {
		shader_directory.emplace(name, std::make_unique<Shader>(renderer, name, layout, vertex_path, fragement_path));
		return FetchShader(name);
	}

	inline Texture* AssetRegistry::CreateTexture(std::string name, std::filesystem::path texture_path) {
		texture_directory.emplace(name, std::make_unique<Texture>(renderer, name, texture_path));
		return FetchTexture(name);
	}

	inline Material* AssetRegistry::CreateMaterial(std::string name, Shader* shader, glm::vec4 albedo, Texture* albedo_texture) {
		material_directory.emplace(name, std::make_unique<Material>(name, shader, albedo, albedo_texture));
		return FetchMaterial(name);
	}

	inline Mesh* AssetRegistry::CreateMesh(std::string name, std::vector<Vertex> verts, std::vector<uint32_t> indices) {
		mesh_directory.emplace(name, std::make_unique<Mesh>(renderer, name, std::move(verts), std::move(indices)));
		return FetchMesh(name);
	}

	inline Scene* AssetRegistry::CreateScene(std::string name) {
		scene_directory.emplace(name, std::make_unique<Scene>(name));
		return FetchScene(name);
	}


	template<AssetType AssetT>
	inline AssetT* AssetRegistry::Fetch(const std::string& name, const std::unordered_map<std::string, Box<AssetT>>& directory) const {
		auto it = directory.find(name);
		AssetT* asset = it != directory.end() ? it->second.get() : nullptr;
		AST_CORE_ASSERT(asset, "Unable to find asset with name {0}", name);
		return asset;
	}

	inline Shader* AssetRegistry::FetchShader(const std::string& name) const {
		return Fetch(name, shader_directory);
	}

	inline Texture* AssetRegistry::FetchTexture(const std::string& name) const {
		return Fetch(name, texture_directory);
	}

	inline Material* AssetRegistry::FetchMaterial(const std::string& name) const {
		return Fetch(name, material_directory);
	}

	inline Mesh* AssetRegistry::FetchMesh(const std::string& name) const {
		return Fetch(name, mesh_directory);
	}

	inline Scene* AssetRegistry::FetchScene(const std::string& name) const {
		return Fetch(name, scene_directory);
	}
}

