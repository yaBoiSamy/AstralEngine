#include "Common.h"
#include "GLSLCompiler.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>



namespace Astral
{
	static const char* GetSourceString(GLenum source)
	{
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:				return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "WindowSystem";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "ShaderCompiler";
		case GL_DEBUG_SOURCE_THIRD_PARTY:		return "ThirdParty";
		case GL_DEBUG_SOURCE_APPLICATION:		return "Application";
		case GL_DEBUG_SOURCE_OTHER:				return "Other";
		default:								return "Unknown";
		}
	}

	static const char* GetTypeString(GLenum type)
	{
		switch (type)
		{
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
		const void* userParam)
	{
		(void)length;
		(void)userParam;

		const char* src = GetSourceString(source);
		const char* typ = GetTypeString(type);

		std::string msg(message ? message : "");

		switch (severity)
		{
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

	GLSLCompiler::GLSLCompiler() {
		AST_CORE_ASSERT(glDebugMessageCallback != nullptr, "GLAD Extension not included");
		if (glDebugMessageCallback) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, this);
		}
	}

	ShaderHandle GLSLCompiler::CompileShader(uint32_t type, const std::string& src) {
		ShaderHandle shaderID = glCreateShader(type);
		const char* rawsrc = src.c_str();
		glShaderSource(shaderID, 1, &rawsrc, nullptr);
		glCompileShader(shaderID);

		int result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			std::string message = std::string(length, '\0');
			glGetShaderInfoLog(shaderID, length, &length, message.data());
			AST_CORE_ERROR("Failed to compile shader: {0}", message);
			glDeleteShader(shaderID);
			return 0;
		}

		return shaderID;
	}

	std::string GLSLCompiler::StringifyShader(const std::string& path)
	{
		std::ifstream file = std::ifstream(path, std::ios::in);
		std::stringstream buffer;

		buffer << file.rdbuf();
		return buffer.str();
	}

	ShaderProgramHandle GLSLCompiler::CreateShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		ShaderProgramHandle programID = glCreateProgram();
		ShaderHandle vs = CompileShader(GL_VERTEX_SHADER, StringifyShader(vertexShaderPath));
		ShaderHandle fs = CompileShader(GL_FRAGMENT_SHADER, StringifyShader(fragmentShaderPath));

		if (vs == 0 || fs == 0)
			return 0;

		glAttachShader(programID, vs);
		glAttachShader(programID, fs);
		glLinkProgram(programID);
		glValidateProgram(programID);

		// Intermediates deletion
		glDeleteShader(vs);
		glDeleteShader(fs);

		return programID;
	}
}