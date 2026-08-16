#include "Common.h"
#include "Texture.h"
#include <filesystem>

#include "Astral/Rendering/Texture/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace Astral::Assets {
	

	Texture::Texture(std::filesystem::path& path) : Asset(path.stem().string()) {
		int w, h, _;
		const uint32_t CHANNELS = 4;
		stbi_set_flip_vertically_on_load(true);
		uint8_t* image_data = stbi_load(path.string().c_str(), &w, &h, &_, CHANNELS);
		uint32_t width = static_cast<uint32_t>(w);
		uint32_t height = static_cast<uint32_t>(h);
		stbi_set_flip_vertically_on_load(false);

		AST_CORE_ASSERT(image_data, "stb failed to parse image: {0}", stbi_failure_reason());

		texture.Load(image_data, width, height);

		stbi_image_free(image_data);
	}


	void Texture::Bind(uint32_t slot) const {
		texture.Bind(slot);
	}
	
}