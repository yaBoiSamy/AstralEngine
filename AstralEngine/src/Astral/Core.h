#pragma once

#ifdef AST_PLATFORM_WINDOWS
	#ifdef AST_BUILD_DLL
		#define ASTRAL_API _declspec(dllexport)
	#else
		#define ASTRAL_API _declspec(dllimport)
	#endif
#else
	#error Astral only supported on windows
#endif
