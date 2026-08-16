#pragma once
#include "Common.h"
#include "Astral/Assets/Asset.h"
#include "Astral/Rendering/Shader/Shader.h"
#include <filesystem>
#include <fstream>
#include <sstream>


namespace Astral::Assets {

	std::string ParseShaderStageFile(std::filesystem::path filepath);

	class Shader : public Asset {
	public:
		Shader(std::string name, std::filesystem::path vertex_path, std::filesystem::path fragement_path);

		void Bind() const;

		template <typename T>
		void CreateUniform(const std::string& name, const T& data);

		template <typename T>
		void CreateUniformArray(const std::string& name);

		template <typename T>
		void SetUniform(const std::string& name, const T& data) const;

		template <typename T>
		void SetUniformArray(const std::string& name, std::span<const T> data) const;

	private:
		Render::Shader shader;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	inline Shader::Shader(std::string name, std::filesystem::path vertex_path, std::filesystem::path fragment_path) 
		: Asset(name), shader(ParseShaderStageFile(vertex_path), ParseShaderStageFile(fragment_path)) {}

	inline std::string ParseShaderStageFile(std::filesystem::path path) {
		std::ifstream file = std::ifstream(path, std::ios::in);
		std::stringstream buffer;

		buffer << file.rdbuf();
		std::string src = buffer.str();
		AST_CORE_ASSERT(src != "", "Shader path invalid: {0}", ( std::filesystem::current_path() / path ).string());
		return src;
	}

	inline void Shader::Bind() const {
		shader.Bind();
	}

	template <typename T>
	inline void Shader::CreateUniform(const std::string& name, const T& data) {
		shader.CreateUniform<T>(name, data);
	}

	template <typename T>
	inline void Shader::CreateUniformArray(const std::string& name) {
		shader.CreateUniformArray<T>(name);
	}

	template <typename T>
	inline void Shader::SetUniform(const std::string& name, const T& data) const {
		shader.SetUniform(name, data);
	}

	template <typename T>
	inline void Shader::SetUniformArray(const std::string& name, std::span<const T> data) const {
		shader.SetUniformArray(name, data);
	}
}

