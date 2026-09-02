#pragma once
#include "Common.h"
#include "Astral/Rendering/Backend/API.h"
#include "Astral/App/Window/Window.h"
#include "Astral/App/Application/StartupConfig.h"

namespace Astral::Render::OpenGL {

	class GraphicsAPI : public IGraphicsAPI {
	public:
		GraphicsAPI();

		virtual void Setup(const App::StartupConfig& config, App::Window* window) override;
		virtual void SetActiveFrameBuffer(uint32_t id) override;
		virtual void SetViewport(size_t frame_width, size_t frame_height) override;
		virtual void Clear(const glm::vec4& color) override;

		virtual Box<IVertexBuffer> CreateVertexBuffer(size_t length, size_t vertex_stride) override;
		virtual Box<IUniformBuffer> CreateUniformBuffer(size_t buffer_stride) override;
		virtual Box<ITexture> CreateTexture(size_t width, size_t height) override;
		virtual Box<IVertexBufferBinding> CreateVertexBufferBinding(uint32_t binding_slot, IVertexBuffer* resource) override;
		virtual Box<IUniformBufferBinding> CreateUniformBufferBinding(uint32_t binding_slot, IUniformBuffer* resource) override;
		virtual Box<ITextureBinding> CreateTextureBinding(uint32_t binding_slot, ITexture* resource) override;
		virtual Box<IIndexBuffer> CreateIndexBuffer(size_t length) override;
		virtual Box<IShader> CreateShader(VertexLayout interface, const std::string& vertex_src, const std::string& fragment_src) override;


		virtual void Draw(IShader* shader, std::span<IBinding*> bindings, size_t first_drawn_vertex, size_t drawn_vertex_count) override;
		virtual void DrawIndexed(IShader* shader, std::span<IBinding*> bindings, IIndexBuffer* indices, size_t first_drawn_index, size_t drawn_index_count) override;
	};
}
