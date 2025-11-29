#pragma once

#include <memory>
#include <spdlog/spdlog.h>

#include "Core.h"


namespace Astral{

	class ASTRAL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	};
}