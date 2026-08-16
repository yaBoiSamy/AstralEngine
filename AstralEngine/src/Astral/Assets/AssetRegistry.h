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

	template<AssetType AssetT>
	class AssetManager {
	public:
		AssetManager() = default;

		void Load(Box<AssetT> asset);
		AssetT* Fetch(const std::string& name) const;

	private:
		std::unordered_map<std::string, Box<AssetT>> directory;
	};


	class AssetRegistry {
	public:
		AssetRegistry() = default;

		template<AssetType AssetT>
		void Load(Box<AssetT> asset);

		template<AssetType AssetT>
		AssetT* Fetch(const std::string& name) const;

	private:
		AssetManager<Shader> shaders;
		AssetManager<Texture> textures;
		AssetManager<Material> materials;
		AssetManager<Mesh> meshes;
		AssetManager<Scene> scenes;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	// ================================================= ASSET MANAGER =================================================

	template<AssetType AssetT>
	inline void AssetManager<AssetT>::Load(Box<AssetT> asset) {
		AST_CORE_ASSERT(asset, "Cannot load null asset");
		directory.emplace(asset->Name(), std::move(asset));
	}

	template<AssetType AssetT>
	inline AssetT* AssetManager<AssetT>::Fetch(const std::string& name) const {
		auto it = directory.find(name);
		AssetT* asset = it != directory.end() ? it->second.get() : nullptr;
		AST_CORE_ASSERT(asset, "Unable to find asset with name {0}", name);
		return asset;
	}


	// ================================================= ASSET REGISTRY ================================================

	template<AssetType AssetT>
	inline void AssetRegistry::Load(Box<AssetT> asset) {
		AST_CORE_ASSERT(false, "Asset is not a part of the registry");
	}

	template<AssetType AssetT>
	inline AssetT* AssetRegistry::Fetch(const std::string& name) const {
		AST_CORE_ASSERT(false, "Asset is not a part of the registry");
		return nullptr;
	}

	template<> inline void AssetRegistry::Load<Shader>(Box<Shader> shader) { return shaders.Load(std::move(shader)); }
	template<> inline void AssetRegistry::Load<Texture>(Box<Texture> texture) { return textures.Load(std::move(texture)); }
	template<> inline void AssetRegistry::Load<Material>(Box<Material> material) { return materials.Load(std::move(material)); }
	template<> inline void AssetRegistry::Load<Mesh>(Box<Mesh> mesh) { return meshes.Load(std::move(mesh)); }
	template<> inline void AssetRegistry::Load<Scene>(Box<Scene> scene) { return scenes.Load(std::move(scene)); }

	template<> inline Shader* AssetRegistry::Fetch<Shader>(const std::string& name) const { return shaders.Fetch(name); }
	template<> inline Texture* AssetRegistry::Fetch<Texture>(const std::string& name) const { return textures.Fetch(name); }
	template<> inline Material* AssetRegistry::Fetch<Material>(const std::string& name) const { return materials.Fetch(name); }
	template<> inline Mesh* AssetRegistry::Fetch<Mesh>(const std::string& name) const { return meshes.Fetch(name); }
	template<> inline Scene* AssetRegistry::Fetch<Scene>(const std::string& name) const { return scenes.Fetch(name); }
}

