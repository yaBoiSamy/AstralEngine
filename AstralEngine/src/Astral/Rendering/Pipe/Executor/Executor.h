#pragma once
#include "Astral/Rendering/Backend/API.h"
#include "Astral/Rendering/Pipe/Command/Command.h"
#include "Astral/Rendering/Pipe/Command/CommandBuffer/CommandBuffer.h"
#include "Astral/Rendering/Pipe/ResourceRegistry/ResourceRegistry.h"
#include "Astral/App/Window/Window.h"


namespace Astral::Render {

	enum class API {
		OpenGL
	};

	class Executor {
	public:
		Executor(ResourceRegistry* registry, CommandBuffer* command_buffer, App::Window* window, API graphics_api);
		void ExecuteCommands();

	private:
		void CreateVertexBuffer(const CreateVertexBufferCommand& command);
		void WriteVertexBuffer(const WriteVertexBufferCommand& command);

		void CreateUniformBuffer(const CreateUniformBufferCommand& command);
		void WriteUniformBuffer(const WriteUniformBufferCommand& command);

		void CreateTexture(const CreateTextureCommand& command);
		void WriteTexture(const WriteTextureCommand& command);

		void CreateIndexBuffer(const CreateIndexBufferCommand& command);
		void WriteIndexBuffer(const WriteIndexBufferCommand& command);

		void CreateShader(const CreateShaderCommand& command);
		void DeleteResource(const DeleteResourceCommand& command);

		void GenerateBindings(const std::vector<ResourceBinding>& handle_bindings, std::vector<Box<IBinding>>& bindings, std::vector<IBinding*>& raw_bindings);
		void NewFrame(const NewFrameCommand& command);
		void Draw(const DrawCommand& command);
		void DrawIndexed(const DrawIndexedCommand& command);
		void DrawImGui(const DrawImGuiCommand& command);

		void OptimizeCommands();

		Box<IGraphicsAPI> api;

		ResourceRegistry* registry;
		CommandBuffer* command_buffer;
		App::Window* window;

	};

}

