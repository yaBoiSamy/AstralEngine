#include "Common.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Astral {

	Texture::Texture(std::string path) {
		int _;
		const uint32_t CHANNELS = 4;
        stbi_set_flip_vertically_on_load(true);
		uint8_t* image_data = stbi_load(path.c_str(), (int*)&width, (int*)&height, &_, CHANNELS);
        stbi_set_flip_vertically_on_load(false);

        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image_data
        );

        glGenerateMipmap(GL_TEXTURE_2D);

        if (image_data)
            stbi_image_free(image_data);
	}

    Texture::~Texture() {
        glDeleteTextures(1, &handle);
    }

    void Texture::Bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, handle);
    }

}
