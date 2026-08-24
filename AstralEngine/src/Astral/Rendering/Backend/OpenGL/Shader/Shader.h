#pragma once
#include "Common.h"
#include "Astral/Rendering/Backend/API.h"
#include <glad/glad.h>


namespace Astral::Render::OpenGL {

	class Shader : public IShader {
	public:
		Shader(VertexLayout interface, const std::string& vertex_src, const std::string& fragment_src);
		~Shader();
		void Bind() const;

	private:
		GLuint CompileShaderStage(uint32_t type, const std::string& src);
		GLuint shader_handle;
		GLuint vao_handle;
	};
}

