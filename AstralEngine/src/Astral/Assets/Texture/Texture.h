#pragma once
#include "Common.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Assets/Asset.h"
#include <filesystem>


namespace Astral::Assets {

	class Texture : public Asset {
	public:
		Texture(Render::Renderer* renderer, std::string name, std::filesystem::path& path);
		Render::ResourceHandle GetHandle() const;

	private:
		Render::Renderer* renderer;
		Render::ResourceHandle texture_handle;
		std::vector<uint8_t> texture_data;
		size_t width, height;
	};
}

