#include "Common.h"
#include "Texture.h"



namespace Astral::Render {

	void Texture::Load(uint8_t* img_data, uint32_t width, uint32_t height) {

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
            img_data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
	}

    Texture::~Texture() {
        glDeleteTextures(1, &handle);
    }

    void Texture::Bind(uint32_t slot) const {
        AST_CORE_ASSERT(handle != 0, "Binding texture before loading it's data");
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, handle);
    }

}
