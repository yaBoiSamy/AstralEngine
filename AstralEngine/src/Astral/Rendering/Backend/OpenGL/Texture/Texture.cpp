#include "Common.h"
#include "Texture.h"


namespace Astral::Render::OpenGL {
	Texture::Texture(size_t width, size_t height) : handle(0), width(width), height(height) {
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
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height),
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			nullptr
		);
	}

	Texture::~Texture() {
		if (handle != 0)
			glDeleteTextures(1, &handle);
	}

	void Texture::Upload(const void* img_data, size_t texel_count_x, size_t texel_count_y, size_t texel_offset_x, size_t texel_offset_y) const {
		AST_CORE_ASSERT(texel_count_x + texel_offset_x <= width, "Writing texels past texture's row capacity");
		AST_CORE_ASSERT(texel_count_y + texel_offset_y <= height, "Writing texels past texture's column capacity");
		glTexSubImage2D(
			GL_TEXTURE_2D,
			0,              // mip level
			static_cast<GLint>(texel_offset_x), static_cast<GLint>(texel_offset_y),  // destination offset
			static_cast<GLsizei>(texel_count_x), static_cast<GLsizei>(texel_count_y),
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			img_data
		);

		glGenerateMipmap(GL_TEXTURE_2D);
	}


	size_t Texture::Width() const {
		return width;
	}
	size_t Texture::Height() const {
		return height;
	}

	void Texture::Bind(uint32_t binding_slot) const {
		glBindTexture(GL_TEXTURE_2D, handle);
	}

}