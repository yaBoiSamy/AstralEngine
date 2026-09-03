#pragma once
#include "Common.h"
#include "Astral/Rendering/Backend/API.h"
#include "Astral/Rendering/Pipe/ResourceRegistry/ResourceRegistry.h"

namespace Astral::Render {

	enum class Role {
		Invoker,
		Executor
	};


	// ========================================= VERTEX BUFFER =========================================

	struct CreateVertexBufferCommand {
		const size_t length;
		const size_t vertex_stride;
		const ResourceHandle created_handle;
	};

	struct WriteVertexBufferCommand {
		const ResourceHandle handle;
		ByteBox data;
		const size_t vertex_count;
		const size_t vertex_offset = 0;
	};

	struct VertexBufferBinding {
		const uint32_t binding_slot;
		const ResourceHandle resource;
	};


	// ========================================= UNIFORM BUFFER =========================================

	struct CreateUniformBufferCommand {
		const size_t stride;
		const ResourceHandle created_handle;
	};

	struct WriteUniformBufferCommand {
		const ResourceHandle handle;
		ByteBox data;
	};

	struct UniformBufferBinding {
		const uint32_t binding_slot;
		const ResourceHandle resource;
	};


	// ============================================ TEXTURE ============================================

	struct CreateTextureCommand {
		const size_t width;
		const size_t height;
		const ResourceHandle created_handle;
	};

	struct WriteTextureCommand {
		const ResourceHandle handle;
		ByteBox data;
		const size_t texel_count_x;
		const size_t texel_count_y;
		const size_t texel_offset_x = 0;
		const size_t texel_offset_y = 0;
	};

	struct TextureBinding {
		const uint32_t binding_slot;
		const ResourceHandle resource;
	};


	// ========================================= INDEX BUFFER =========================================

	struct CreateIndexBufferCommand {
		const size_t length;
		const ResourceHandle created_handle;
	};

	struct WriteIndexBufferCommand {
		const ResourceHandle handle;
		ByteBox data;
		const size_t index_count;
		const size_t index_offset = 0;
	};


	// ============================================ SHADERS ============================================

	struct CreateShaderCommand {
		const VertexLayout layout;
		const std::string vertex_src;
		const std::string fragment_src;
		const ResourceHandle created_handle;
	};


	// =========================================== RENDERING ===========================================

	using ResourceBinding = std::variant<
		VertexBufferBinding,
		UniformBufferBinding,
		TextureBinding
	>;

	struct DeleteResourceCommand {
		const ResourceHandle handle;
	};

	struct NewFrameCommand {
		const uint32_t viewport_id;
		const size_t frame_width, frame_height;
	};

	struct DrawCommand {
		const ResourceHandle shader;
		const std::vector<ResourceBinding> bindings;
		const size_t first_drawn_vertex;
		const size_t drawn_vertex_count;
	};

	struct DrawIndexedCommand {
		const ResourceHandle shader;
		const ResourceHandle index_buffer;
		const std::vector<ResourceBinding> bindings;
		const size_t first_drawn_index;
		const size_t drawn_index_count;
	};

	struct DrawImGuiCommand {
		std::function<void()> render_ui;
	};


	// ============================================ VARIANT ============================================

	using Command = std::variant<
		CreateVertexBufferCommand, 
		WriteVertexBufferCommand,

		CreateUniformBufferCommand,
		WriteUniformBufferCommand,

		CreateTextureCommand,
		WriteTextureCommand,

		CreateIndexBufferCommand,
		WriteIndexBufferCommand,

		CreateShaderCommand,
		DeleteResourceCommand,

		NewFrameCommand,
		DrawCommand,
		DrawIndexedCommand,
		DrawImGuiCommand
	>;
}