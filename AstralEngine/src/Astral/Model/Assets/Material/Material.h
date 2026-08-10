#pragma once
#include "Astral/Rendering/Shader/Shader.h"

namespace Astral {

	class Material {
	public:
		void Bind() const;
	private:
		Shader* shader;
	};
}
