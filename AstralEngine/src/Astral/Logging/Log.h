#pragma once

#include <Common.h>
#include <spdlog/spdlog.h>

#include "Astral/Core.h"

#define AST_CORE_TRACE(msg, ...) Astral::Log::GetCoreLogger()->trace(msg, __VA_ARGS__)
#define AST_CORE_INFO(msg, ...) Astral::Log::GetCoreLogger()->info(msg, __VA_ARGS__)
#define AST_CORE_WARN(msg, ...) Astral::Log::GetCoreLogger()->warn(msg, __VA_ARGS__)
#define AST_CORE_ERROR(msg, ...) Astral::Log::GetCoreLogger()->error(msg, __VA_ARGS__)

#define AST_USER_TRACE(msg, ...) Astral::Log::GetClientLogger()->trace(msg, __VA_ARGS__)
#define AST_USER_INFO(msg, ...) Astral::Log::GetClientLogger()->info(msg, __VA_ARGS__)
#define AST_USER_WARN(msg, ...) Astral::Log::GetClientLogger()->warn(msg, __VA_ARGS__)
#define AST_USER_ERROR(msg, ...) Astral::Log::GetClientLogger()->error(msg, __VA_ARGS__)


namespace Astral{

	class ASTRAL_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> GetCoreLogger() { return CoreLogger; }
		static std::shared_ptr<spdlog::logger> GetClientLogger() { return ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	};

}