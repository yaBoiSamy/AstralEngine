#include "Common.h"
#include "Texture.h"
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace Astral::Assets {
	Texture::Texture(Render::Renderer* renderer, std::string name, std::filesystem::path& path) : Asset(name), renderer(renderer) {
		AST_CORE_ASSERT(renderer, "Texture cannot be constructed with null renderer");

		int w, h, _;
		const uint32_t CHANNELS = 4;
		stbi_set_flip_vertically_on_load(true);
		texture_data = stbi_load(path.string().c_str(), &w, &h, &_, CHANNELS);
		width = static_cast<size_t>(w);
		height = static_cast<size_t>(h);
		stbi_set_flip_vertically_on_load(false);

		AST_CORE_ASSERT(texture_data, "stb failed to parse image: {0}", stbi_failure_reason());
		texture_handle = renderer->Command().CreateTexture(width, height);
		renderer->Command().WriteTexture(texture_handle, ToBytesArray(Box<uint8_t>(texture_data)), width, height);
	}

	Texture::~Texture() {
		stbi_image_free(texture_data);
	}

	Render::ResourceHandle Texture::GetHandle() const {
		return texture_handle;
	}
}