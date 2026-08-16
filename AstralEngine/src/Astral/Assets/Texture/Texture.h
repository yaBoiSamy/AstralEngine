#pragma once
#include "Common.h"
#include "Astral/Rendering/Texture/Texture.h"
#include "Astral/Assets/Asset.h"
#include <filesystem>


namespace Astral::Assets {

	class Texture : public Asset {
	public:
		Texture(std::filesystem::path& path);

		void Bind(uint32_t slot) const;

	private:
		Render::Texture texture;
	};
}

