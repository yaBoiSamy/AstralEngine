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
		AssetRegistry(Render::Renderer* renderer);

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
		Texture* blank_texture;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	template<AssetType AssetT>
	inline AssetT* AssetRegistry::Fetch(const std::string& name, const std::unordered_map<std::string, Box<AssetT>>& directory) const {
		auto it = directory.find(name);
		AssetT* asset = it != directory.end() ? it->second.get() : nullptr;
		AST_CORE_ASSERT(asset, "Unable to find asset with name {0}", name);
		return asset;
	}
}

