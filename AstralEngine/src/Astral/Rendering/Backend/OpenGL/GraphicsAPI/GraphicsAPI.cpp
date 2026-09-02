#include "Common.h"
#include "GraphicsAPI.h"
#include "Astral/Rendering/Backend/API.h"
#include "Astral/Rendering/Backend/OpenGL/VertexBuffer/VertexBuffer.h"
#include "Astral/Rendering/Backend/OpenGL/UniformBuffer/UniformBuffer.h"
#include "Astral/Rendering/Backend/OpenGL/Texture/Texture.h"
#include "Astral/Rendering/Backend/OpenGL/IndexBuffer/IndexBuffer.h"
#include "Astral/Rendering/Backend/OpenGL/Binding/Binding.h"
#include "Astral/Rendering/Backend/OpenGL/Shader/Shader.h"

#include "Astral/App/Window/Window.h"
#include "Astral/App/Application/StartupConfig.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Astral::Render::OpenGL {

	GraphicsAPI::GraphicsAPI() {}

	static void OpenGLMessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);

	static const char* ToGLSLVersion(int major, int minor) {
		if (major == 3 && minor == 0) return "#version 130";
		if (major == 3 && minor == 1) return "#version 140";
		if (major == 3 && minor == 2) return "#version 150";
		if (major == 3 && minor == 3) return "#version 330";
		if (major == 4 && minor == 0) return "#version 400";
		if (major == 4 && minor == 1) return "#version 410";
		if (major == 4 && minor == 2) return "#version 420";
		if (major == 4 && minor == 3) return "#version 430";
		if (major == 4 && minor == 4) return "#version 440";
		if (major == 4 && minor == 5) return "#version 450";
		if (major == 4 && minor == 6) return "#version 460";

		AST_CORE_ASSERT(false, "Unsupported OpenGL version");
		return "";
	}

	void GraphicsAPI::Setup(const App::StartupConfig& config, App::Window* window) {
		window->MakeContextCurrent();
		window->SetVSync(config.vsync);
		
		// Load OpenGL functions using glad
		int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		AST_CORE_ASSERT(success, "Failed to populate graphics programming functions");

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport / Platform Windows        
		
		// Styling
		ImGui::StyleColorsDark();

		float scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
		ImGuiStyle& style = ImGui::GetStyle();
		style.ScaleAllSizes(scale);
		style.FontScaleDpi = scale;

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
		ImGui_ImplOpenGL3_Init(ToGLSLVersion(config.version_major, config.version_minor));

		if (glDebugMessageCallback && AST_DEBUG) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, this);
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		AST_CORE_INFO("\nOpenGL Info:\n    Vendor: {0}\n    Renderer: {1}\n    Version: {2}",
			(char*)glGetString(GL_VENDOR),
			(char*)glGetString(GL_RENDERER),
			(char*)glGetString(GL_VERSION));
	}

	void GraphicsAPI::SetActiveFrameBuffer(uint32_t id) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicsAPI::SetViewport(size_t framebuffer_width, size_t frame_height) {
		glViewport(0, 0, static_cast<GLsizei>(framebuffer_width), static_cast<GLsizei>(frame_height));
	}

	void GraphicsAPI::Clear(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	Box<IVertexBuffer> GraphicsAPI::CreateVertexBuffer(size_t length, size_t vertex_stride) {
		return std::make_unique<VertexBuffer>(length, vertex_stride);
	}

	Box<IUniformBuffer> GraphicsAPI::CreateUniformBuffer(size_t buffer_stride) {
		return std::make_unique<UniformBuffer>(buffer_stride);
	}

	Box<ITexture> GraphicsAPI::CreateTexture(size_t width, size_t height) {
		return std::make_unique<Texture>(width, height);
	}

	Box<IVertexBufferBinding> GraphicsAPI::CreateVertexBufferBinding(uint32_t binding_slot, IVertexBuffer* resource) {
		return std::make_unique<VertexBufferBinding>(binding_slot, resource);
	}

	Box<IUniformBufferBinding> GraphicsAPI::CreateUniformBufferBinding(uint32_t binding_slot, IUniformBuffer* resource) {
		return std::make_unique<UniformBufferBinding>(binding_slot, resource);
	}

	Box<ITextureBinding> GraphicsAPI::CreateTextureBinding(uint32_t binding_slot, ITexture* resource) {
		return std::make_unique<TextureBinding>(binding_slot, resource);
	}

	Box<IIndexBuffer> GraphicsAPI::CreateIndexBuffer(size_t length) {
		return std::make_unique<IndexBuffer>(length);
	}

	Box<IShader> GraphicsAPI::CreateShader(VertexLayout interface, const std::string& vertex_src, const std::string& fragment_src) {
		return std::make_unique<Shader>(interface, vertex_src, fragment_src);
	}


	void BindDescriptors(IShader* shader, std::span<IBinding*>& descriptors) {
		for (const IBinding* descriptor : descriptors) {
			AST_CORE_ASSERT(descriptor, "Cannot bind null descriptor");
			descriptor->Bind(shader);
		}
	}

	void GraphicsAPI::Draw(IShader* shader, std::span<IBinding*> bindings, size_t first_drawn_vertex, size_t drawn_vertex_count) {
		AST_CORE_ASSERT(shader, "Cannot draw with null shader");
		dynamic_cast<Shader*>(shader)->Bind();
		BindDescriptors(shader, bindings);
		glDrawArrays(GL_TRIANGLES, static_cast<GLint>(first_drawn_vertex), static_cast<GLsizei>(drawn_vertex_count));
	}

	void GraphicsAPI::DrawIndexed(IShader* shader, std::span<IBinding*> bindings, IIndexBuffer* indices, size_t first_drawn_index, size_t drawn_index_count) {
		AST_CORE_ASSERT(shader, "Cannot draw with null shader");
		AST_CORE_ASSERT(indices, "Cannot draw with null indices");
		dynamic_cast<Shader*>(shader)->Bind();
		dynamic_cast<IndexBuffer*>(indices)->Bind();
		BindDescriptors(shader, bindings);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(drawn_index_count), GL_UNSIGNED_INT, reinterpret_cast<void*>(static_cast<GLintptr>(first_drawn_index * sizeof(uint32_t))));
	}


	// ================================== CALLBACK DEFINITION ==================================

	static const char* GetSourceString(GLenum source) {
		switch (source) {
		case GL_DEBUG_SOURCE_API:				return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "WindowSystem";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "ShaderCompiler";
		case GL_DEBUG_SOURCE_THIRD_PARTY:		return "ThirdParty";
		case GL_DEBUG_SOURCE_APPLICATION:		return "Application";
		case GL_DEBUG_SOURCE_OTHER:				return "Other";
		default:								return "Unknown";
		}
	}

	static const char* GetTypeString(GLenum type) {
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:               return "Error";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "UndefinedBehavior";
		case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
		case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
		case GL_DEBUG_TYPE_MARKER:              return "Marker";
		case GL_DEBUG_TYPE_PUSH_GROUP:          return "PushGroup";
		case GL_DEBUG_TYPE_POP_GROUP:           return "PopGroup";
		case GL_DEBUG_TYPE_OTHER:               return "Other";
		default:								return "Unknown";
		}
	}

	static void APIENTRY OpenGLMessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam) {
		(void)length;
		(void)userParam;

		const char* src = GetSourceString(source);
		const char* typ = GetTypeString(type);

		std::string msg(message ? message : "");

		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			AST_CORE_ERROR("[OpenGL][{}][{}][{}] {}", src, typ, id, msg);
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			AST_CORE_WARN("[OpenGL][{}][{}][{}] {}", src, typ, id, msg);
			break;

		case GL_DEBUG_SEVERITY_LOW:
			AST_CORE_INFO("[OpenGL][{}][{}][{}] {}", src, typ, id, msg);
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			AST_CORE_TRACE("[OpenGL][{}][{}][{}] {}", src, typ, id, msg);
			break;
		}
	}
}