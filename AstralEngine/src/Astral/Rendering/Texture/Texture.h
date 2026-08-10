#pragma once
#include "Common.h"
#include <glad/glad.h>

namespace Astral {

	class Texture {
	public:
		Texture(std::string path);
		~Texture();

		void Bind(uint32_t slot) const;

	private:
		uint32_t width, height;
		GLuint handle;
	};
}

