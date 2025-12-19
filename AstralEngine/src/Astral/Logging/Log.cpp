#include <Common.h>

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Astral {
	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		CoreLogger = spdlog::stdout_color_mt("ASTRAL");
		CoreLogger->set_level(spdlog::level::trace);

		ClientLogger = spdlog::stdout_color_mt("APP");
		ClientLogger->set_level(spdlog::level::trace);

		AST_CORE_TRACE("logger initialized");
	}

	void InitLogger() {
		Log::Init();
	}
}
