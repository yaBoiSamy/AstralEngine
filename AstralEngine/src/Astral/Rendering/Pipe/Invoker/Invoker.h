#pragma once
#include "Common.h"
#include "Astral/Rendering/Pipe/ResourceRegistry/ResourceRegistry.h"
#include "Astral/Rendering/Pipe/Command/CommandBuffer/CommandBuffer.h"

namespace Astral::Render {

	class Invoker {
	public:
		Invoker(ResourceRegistry* registry, CommandBuffer* command_buffer);

		ResourceHandle CreateVertexBuffer(size_t length, size_t vertex_stride) const;
		void WriteVertexBuffer(ResourceHandle handle, ByteBox data, size_t vertex_count, size_t vertex_offset = 0) const;

		ResourceHandle CreateUniformBuffer(size_t stride) const;
		void WriteUniformBuffer(ResourceHandle handle, ByteBox data) const;

		ResourceHandle CreateTexture(size_t width, size_t height) const;
		void WriteTexture(ResourceHandle handle, ByteBox data, size_t texel_count_x, size_t  texel_count_y, size_t texel_offset_x = 0, size_t texel_offset_y = 0) const;

		ResourceHandle CreateIndexBuffer(size_t length) const;
		void WriteIndexBuffer(ResourceHandle handle, ByteBox data, size_t index_count, size_t index_offset = 0) const;

		ResourceHandle CreateShader(VertexLayout layout, std::string vertex_src, std::string fragment_src) const;
		void DeleteResource(ResourceHandle handle) const;

		void NewFrame(uint32_t viewport_id, size_t frame_width, size_t frame_height) const;
		void Draw(ResourceHandle shader, std::vector<ResourceBinding> bindings, size_t first_drawn_vertex, size_t drawn_vertex_count) const;
		void DrawIndexed(ResourceHandle shader, ResourceHandle index_buffer, std::vector<ResourceBinding> bindings, size_t first_drawn_index, size_t drawn_index_count) const;
		void DrawImGui(std::function<void()> render_ui) const;
		void SubmitFrame() const;

	private:
		ResourceRegistry* registry;
		CommandBuffer* command_buffer;
	};

}
