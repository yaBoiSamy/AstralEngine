#pragma once
#include "Common.h"
#include <glad/glad.h>

namespace Astral::Render {

	class Texture {
	public:
		Texture() = default;
		~Texture();

		void Load(uint8_t* img_data, uint32_t width, uint32_t height);

		void Bind(uint32_t slot) const;

	private:
		uint32_t width, height;
		GLuint handle;
	};
}

