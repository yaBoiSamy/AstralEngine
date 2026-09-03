#include "Common.h"
#include "Invoker.h"
#include "Astral/Rendering/Pipe/Command/Command.h"
#include "Astral/Rendering/Pipe/ResourceRegistry/ResourceRegistry.h"
#include "Astral/Rendering/Pipe/Command/CommandBuffer/CommandBuffer.h"

namespace Astral::Render {

	Invoker::Invoker(ResourceRegistry* registry, CommandBuffer* command_buffer) : registry(registry), command_buffer(command_buffer) {}


	// ======================================== VERTEX BUFFER ========================================

	ResourceHandle Invoker::CreateVertexBuffer(size_t length, size_t vertex_stride) const {
		ResourceHandle handle = registry->AllocateHandle();
		Command command = CreateVertexBufferCommand{
			.length = length,
			.vertex_stride = vertex_stride,
			.created_handle = handle
		};

		command_buffer->InvokeCommand(std::move(command));
		return handle;
	}

	void Invoker::WriteVertexBuffer(ResourceHandle handle, ByteBox data, size_t vertex_count, size_t vertex_offset) const {
		Command command = WriteVertexBufferCommand{
			.handle = handle,
			.data = std::move(data),
			.vertex_count = vertex_count,
			.vertex_offset = vertex_offset
		};

		command_buffer->InvokeCommand(std::move(command));
	}


	// ======================================== UNIFORM BUFFER ========================================

	ResourceHandle Invoker::CreateUniformBuffer(size_t stride) const {
		ResourceHandle handle = registry->AllocateHandle();
		Command command = CreateUniformBufferCommand{
			.stride = stride,
			.created_handle = handle
		};

		command_buffer->InvokeCommand(std::move(command));
		return handle;
	}

	void Invoker::WriteUniformBuffer(ResourceHandle handle, ByteBox data) const {
		Command command = WriteUniformBufferCommand{
			.handle = handle,
			.data = std::move(data)
		};

		command_buffer->InvokeCommand(std::move(command));
	}


	// =========================================== TEXTURE ===========================================

	ResourceHandle Invoker::CreateTexture(size_t width, size_t height) const {
		ResourceHandle handle = registry->AllocateHandle();
		Command command = CreateTextureCommand{
			.width = width,
			.height = height,
			.created_handle = handle
		};

		command_buffer->InvokeCommand(std::move(command));
		return handle;
	}

	void Invoker::WriteTexture(ResourceHandle handle, ByteBox data, size_t texel_count_x, size_t texel_count_y, size_t texel_offset_x, size_t texel_offset_y) const {
		Command command = WriteTextureCommand{
			.handle = handle,
			.data = std::move(data),
			.texel_count_x = texel_count_x,
			.texel_count_y = texel_count_y,
			.texel_offset_x = texel_offset_x,
			.texel_offset_y = texel_offset_y
		};

		command_buffer->InvokeCommand(std::move(command));
	}


	// ======================================== INDEX BUFFER ========================================

	ResourceHandle Invoker::CreateIndexBuffer(size_t length) const {
		ResourceHandle handle = registry->AllocateHandle();
		Command command = CreateIndexBufferCommand{
			.length = length,
			.created_handle = handle
		};

		command_buffer->InvokeCommand(std::move(command));
		return handle;
	}

	void Invoker::WriteIndexBuffer(ResourceHandle handle, ByteBox data, size_t index_count, size_t index_offset) const {
		Command command = WriteIndexBufferCommand{
			.handle = handle,
			.data = std::move(data),
			.index_count = index_count,
			.index_offset = index_offset
		};

		command_buffer->InvokeCommand(std::move(command));
	}


	// =========================================== SHADER ===========================================

	ResourceHandle Invoker::CreateShader(VertexLayout layout, std::string vertex_src, std::string fragment_src) const {
		ResourceHandle handle = registry->AllocateHandle();
		Command command = CreateShaderCommand{
			.layout = layout,
			.vertex_src = std::move(vertex_src),
			.fragment_src = std::move(fragment_src),
			.created_handle = handle
		};

		command_buffer->InvokeCommand(std::move(command));
		return handle;
	}


	// ========================================= RENDERING =========================================

	void Invoker::DeleteResource(ResourceHandle handle) const {
		Command command = DeleteResourceCommand{
			.handle = handle
		};

		command_buffer->InvokeCommand(std::move(command));
	}

	void Invoker::NewFrame(uint32_t viewport_id, size_t frame_width, size_t frame_height) const {
		Command command = NewFrameCommand{
			.viewport_id = viewport_id,
			.frame_width = frame_width,
			.frame_height = frame_height
		};

		command_buffer->InvokeCommand(std::move(command));
	}

	void Invoker::Draw(ResourceHandle shader, std::vector<ResourceBinding> bindings, size_t first_drawn_vertex, size_t drawn_vertex_count) const {
		Command command = DrawCommand{
			.shader = shader,
			.bindings = std::move(bindings),
			.first_drawn_vertex = first_drawn_vertex,
			.drawn_vertex_count = drawn_vertex_count
		};

		command_buffer->InvokeCommand(std::move(command));
	}

	void Invoker::DrawIndexed(ResourceHandle shader, ResourceHandle index_buffer, std::vector<ResourceBinding> bindings, size_t first_drawn_index, size_t drawn_index_count) const {
		Command command = DrawIndexedCommand{
			.shader = shader,
			.index_buffer = index_buffer,
			.bindings = std::move(bindings),
			.first_drawn_index = first_drawn_index,
			.drawn_index_count = drawn_index_count
		};

		command_buffer->InvokeCommand(std::move(command));
	}

	void Invoker::DrawImGui(std::function<void()> render_ui) const {
		Command command = DrawImGuiCommand{
			.render_ui = render_ui
		};

		command_buffer->InvokeCommand(std::move(command));
	}

	void Invoker::SubmitFrame() const {
		command_buffer->SwapBuffer(Role::Invoker);
	}
}