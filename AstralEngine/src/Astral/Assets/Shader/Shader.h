#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include <filesystem>


namespace Astral::Assets {

	std::string ParseShaderStageFile(std::filesystem::path filepath);

	class Shader : public Asset {
	public:
		Shader(Render::Renderer* renderer, std::string name, Render::VertexLayout& layout, std::filesystem::path vertex_path, std::filesystem::path fragement_path);

		Render::ResourceHandle GetHandle() const;

	private:
		Render::ResourceHandle shader_handle;
		Render::Renderer* renderer;
	};
}

