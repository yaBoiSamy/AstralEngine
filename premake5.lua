workspace "AstralEngine"
    startproject "Sandbox"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

    filter "system:windows"
        externalanglebrackets "On"   -- #include <...> are considered external
        externalwarnings "Off"
    filter {}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    buildoptions { "/utf-8" }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "AstralEngine/vendors/spdlog/include",
        "AstralEngine/src"
    }

    links {
        "AstralEngine"
    }

    filter "system:windows" 
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "AST_PLATFORM_WINDOWS"
        }
    
    filter { "configurations:Debug" }
        defines { "AST_DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "AST_RELEASE" }
        optimize "On"

    filter { "configurations:Dist" }
        defines { "AST_DIST" }
        optimize "On"

project "AstralEngine"
    location "AstralEngine"
    kind "SharedLib"
    language "C++"
    buildoptions { "/utf-8" }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/vendors/spdlog/include",
        "%{prj.name}/src"
    }

    pchheader "Common.h"
    pchsource "%{prj.name}/src/Common.cpp"

    filter "system:windows" 
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "AST_PLATFORM_WINDOWS",
            "AST_BUILD_DLL"
        }

        postbuildcommands { 
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter { "configurations:Debug" }
        defines { "AST_DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "AST_RELEASE" }
        optimize "On"

    filter { "configurations:Dist" }
        defines { "AST_DIST" }
        optimize "On"