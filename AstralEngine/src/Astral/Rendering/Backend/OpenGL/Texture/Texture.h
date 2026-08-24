#pragma once
#include "Astral/Rendering/Backend/API.h"
#include <glad/glad.h>


namespace Astral::Render::OpenGL {
	class Texture : public ITexture {
	public:
		Texture(size_t width, size_t height);
		~Texture();
		virtual void Upload(const void* img_data, size_t texel_count_x, size_t texel_count_y, size_t texel_offset_x, size_t texel_offset_y) const override;
		virtual size_t Width() const override;
		virtual size_t Height() const override;

		virtual void Bind(uint32_t binding_slot) const override;

	private:
		GLuint handle;
		const size_t width, height;
	};
}
