#include "Common.h"

#define TRACY_ENABLE
#include <tracy/Tracy.hpp>

#include "Executor.h"
#include "Astral/Rendering/Backend/API.h"
#include "Astral/Rendering/Backend/OpenGL/GraphicsAPI/GraphicsAPI.h"
#include "Astral/Rendering/Pipe/Command/Command.h"
#include "Astral/Rendering/Pipe/Command/CommandBuffer/CommandBuffer.h"
#include "Astral/App/Window/Window.h"
#include "Astral/App/Application/StartupConfig.h"



namespace Astral::Render {
	Box<IGraphicsAPI> ConstructAPI(API graphics_api) {
		switch (graphics_api) {
		case API::OpenGL: return std::make_unique<OpenGL::GraphicsAPI>();
		default: AST_CORE_ASSERT(false, "Unsupported API requested"); return Box<IGraphicsAPI>(nullptr);
		}
	}

	Executor::Executor(ResourceRegistry* registry, CommandBuffer* command_buffer, App::Window* window, API graphics_api, const App::StartupConfig& config) :
		api(ConstructAPI(graphics_api)),
		registry(registry),
		command_buffer(command_buffer),
		window(window)
	{
		AST_CORE_ASSERT(window, "Window cannot be null at Executor construction");
		api->Setup(config, window);
	}

	void Executor::OptimizeCommands() {
		ZoneScoped;
	}

	void Executor::ExecuteCommands() {
		ZoneScoped;
		OptimizeCommands();
		for (Command& command : command_buffer->ProcessedCommands()) {
			std::visit(overloaded{
				[&](const CreateVertexBufferCommand& command) {
					ZoneScopedN("CreateVertexBuffer");
					CreateVertexBuffer(command);
				},
				[&](const WriteVertexBufferCommand& command) {
					ZoneScopedN("WriteVertexBuffer");
					WriteVertexBuffer(command);
				},
				[&](const CreateUniformBufferCommand& command) {
					ZoneScopedN("CreateUniformBuffer");
					CreateUniformBuffer(command);
				},
				[&](const WriteUniformBufferCommand& command) {
					ZoneScopedN("WriteUniformBuffer");
					WriteUniformBuffer(command);
				},
				[&](const CreateTextureCommand& command) {
					ZoneScopedN("CreateTexture");
					CreateTexture(command);
				},
				[&](const WriteTextureCommand& command) {
					ZoneScopedN("WriteTexture");
					WriteTexture(command);
				},
				[&](const CreateIndexBufferCommand& command) {
					ZoneScopedN("CreateIndexBuffer");
					CreateIndexBuffer(command);
				},
				[&](const WriteIndexBufferCommand& command) {
					ZoneScopedN("WriteIndexBuffer");
					WriteIndexBuffer(command);
				},
				[&](const CreateShaderCommand& command) {
					ZoneScopedN("CreateShader");
					CreateShader(command);
				},
				[&](const DeleteResourceCommand& command) {
					ZoneScopedN("DeleteResource");
					DeleteResource(command);
				},
				[&](const NewFrameCommand& command) {
					ZoneScopedN("NewFrame");
					NewFrame(command);
				},
				[&](const DrawCommand& command) {
					ZoneScopedN("Draw");
					Draw(command);
				},
				[&](const DrawIndexedCommand& command) {
					ZoneScopedN("DrawIndexed");
					DrawIndexed(command);
				},
				[&](const DrawImGuiCommand& command) {
					ZoneScopedN("DrawImGui");
					DrawImGui(command);
				}
			}, command);
		} {
			ZoneScopedN("VSync rate limiting");
			window->SwapBuffers();
		}
		command_buffer->ProcessedCommands().clear();
		{
			ZoneScopedN("CPU bottlenecking");
			command_buffer->SwapBuffer(Role::Executor);
		}
	}

	// ======================================== VERTEX BUFFER ========================================

	void Executor::CreateVertexBuffer(const CreateVertexBufferCommand& command) {
		Box<IVertexBuffer> buffer = api->CreateVertexBuffer(command.length, command.vertex_stride);
		registry->AssignHandle(command.created_handle, std::move(buffer));
	}

	void Executor::WriteVertexBuffer(const WriteVertexBufferCommand& command) {
		IVertexBuffer* buffer = dynamic_cast<IVertexBuffer*>(registry->ResolveHandle(command.handle));
		buffer->Upload(command.data.get(), command.vertex_count, command.vertex_offset);
	}
	

	// ======================================== UNIFORM BUFFER ========================================

	void Executor::CreateUniformBuffer(const CreateUniformBufferCommand& command) {
		Box<IUniformBuffer> buffer = api->CreateUniformBuffer(command.stride);
		registry->AssignHandle(command.created_handle, std::move(buffer));
	}

	void Executor::WriteUniformBuffer(const WriteUniformBufferCommand& command) {
		IUniformBuffer* buffer = dynamic_cast<IUniformBuffer*>(registry->ResolveHandle(command.handle));
		buffer->Upload(command.data.get());
	}


	// =========================================== TEXTURE ===========================================

	void Executor::CreateTexture(const CreateTextureCommand& command) {
		Box<ITexture> texture = api->CreateTexture(command.width, command.height);
		registry->AssignHandle(command.created_handle, std::move(texture));
	}

	void Executor::WriteTexture(const WriteTextureCommand& command) {
		ITexture* texture = dynamic_cast<ITexture*>(registry->ResolveHandle(command.handle));
		texture->Upload(command.data.get(), command.texel_count_x, command.texel_count_y, command.texel_offset_x, command.texel_offset_y);
	}


	// ======================================== INDEX BUFFER ========================================

	void Executor::CreateIndexBuffer(const CreateIndexBufferCommand& command) {
		Box<IIndexBuffer> buffer = api->CreateIndexBuffer(command.length);
		registry->AssignHandle(command.created_handle, std::move(buffer));
	}

	void Executor::WriteIndexBuffer(const WriteIndexBufferCommand& command) {
		IIndexBuffer* buffer = dynamic_cast<IIndexBuffer*>(registry->ResolveHandle(command.handle));
		buffer->Upload(command.data.get(), command.index_count, command.index_offset);
	}


	// =========================================== SHADER ===========================================
	
	void Executor::CreateShader(const CreateShaderCommand& command) {
		Box<IShader> shader = api->CreateShader(command.layout, command.vertex_src, command.fragment_src);
		registry->AssignHandle(command.created_handle, std::move(shader));
	}


	// ========================================= RENDERING =========================================

	void Executor::DeleteResource(const DeleteResourceCommand& command) {
		registry->DeallocateResource(command.handle);
	}

	void Executor::NewFrame(const NewFrameCommand& command) {
		api->SetActiveFrameBuffer(command.viewport_id);
		api->SetViewport(command.frame_width, command.frame_height);
		api->Clear(glm::vec4(0.1, 0.1, 0.1, 1.0));
	}

	void Executor::GenerateBindings(const std::vector<ResourceBinding>& handle_bindings, std::vector<Box<IBinding>>& bindings, std::vector<IBinding*>& raw_bindings) {
		for (const ResourceBinding& resource_binding : handle_bindings) {
			std::visit(overloaded{
				[&](const VertexBufferBinding& handle_binding) {
					IVertexBuffer* vertex_buffer = dynamic_cast<IVertexBuffer*>(registry->ResolveHandle(handle_binding.resource));
					Box<IVertexBufferBinding> binding = api->CreateVertexBufferBinding(handle_binding.binding_slot, vertex_buffer);
					raw_bindings.push_back(binding.get());
					bindings.push_back(std::move(binding));
				},
				[&](const UniformBufferBinding& handle_binding) {
					IUniformBuffer* uniform_buffer = dynamic_cast<IUniformBuffer*>(registry->ResolveHandle(handle_binding.resource));
					Box<IUniformBufferBinding> binding = api->CreateUniformBufferBinding(handle_binding.binding_slot, uniform_buffer);
					raw_bindings.push_back(binding.get());
					bindings.push_back(std::move(binding));
				},
				[&](const TextureBinding& handle_binding) {
					ITexture* texture = dynamic_cast<ITexture*>(registry->ResolveHandle(handle_binding.resource));
					Box<ITextureBinding> binding = api->CreateTextureBinding(handle_binding.binding_slot, texture);
					raw_bindings.push_back(binding.get());
					bindings.push_back(std::move(binding));
				}
			}, resource_binding);
		}
	}

	void Executor::Draw(const DrawCommand& command) {
		IShader* shader = dynamic_cast<IShader*>(registry->ResolveHandle(command.shader));
		const size_t binding_count = command.bindings.size();
		std::vector<Box<IBinding>> bindings;
		std::vector<IBinding*> raw_bindings;
		bindings.reserve(binding_count);
		raw_bindings.reserve(binding_count);
		GenerateBindings(command.bindings, bindings, raw_bindings);
		api->Draw(shader, raw_bindings, command.first_drawn_vertex, command.drawn_vertex_count);
	}

	void Executor::DrawIndexed(const DrawIndexedCommand& command) {
		IShader* shader = dynamic_cast<IShader*>(registry->ResolveHandle(command.shader));
		IIndexBuffer* index_buffer = dynamic_cast<IIndexBuffer*>(registry->ResolveHandle(command.index_buffer));
		AST_CORE_ASSERT(index_buffer->Length() >= command.first_drawn_index + command.drawn_index_count, "Drawing past index buffer bounds");
		const size_t binding_count = command.bindings.size();
		std::vector<Box<IBinding>> bindings;
		std::vector<IBinding*> raw_bindings;
		bindings.reserve(binding_count);
		raw_bindings.reserve(binding_count);
		GenerateBindings(command.bindings, bindings, raw_bindings);
		api->DrawIndexed(shader, raw_bindings, index_buffer, command.first_drawn_index, command.drawn_index_count);
	}

	void Executor::DrawImGui(const DrawImGuiCommand& command) {
		command.render_ui();
	}
}
