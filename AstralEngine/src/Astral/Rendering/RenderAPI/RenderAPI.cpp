#include "Common.h"
#include "RenderAPI.h"
#include <glad/glad.h>

namespace Astral {

	static OpenGLRenderAPI api = OpenGLRenderAPI();

	RenderAPI& GfxAPI() {
		return api;
	}

	OpenGLRenderAPI::OpenGLRenderAPI() {}

	static void OpenGLMessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);

	void OpenGLRenderAPI::Setup() {
		AST_CORE_ASSERT(glDebugMessageCallback != nullptr, "GLAD Extension not included");
		if (glDebugMessageCallback && AST_DEBUG) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, this);
		}

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		AST_CORE_INFO("\nOpenGL Info:\n    Vendor: {0}\n    Renderer: {1}\n    Version: {2}",
			(char*)glGetString(GL_VENDOR),
			(char*)glGetString(GL_RENDERER),
			(char*)glGetString(GL_VERSION));
	}

	void OpenGLRenderAPI::SetActiveFrameBuffer(uint32_t id) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLRenderAPI::SetViewport(std::pair<uint32_t, uint32_t> framebufferSize) {
		auto [fbw, fbh] = framebufferSize;
		glViewport(0, 0, fbw, fbh);
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::Draw(const IVertexArray& vertexArray) {
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexArray.Length()), GL_UNSIGNED_INT, nullptr);
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