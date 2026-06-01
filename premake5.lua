workspace "AstralEngine"
    startproject "Sandbox"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    staticruntime "On"
    language "C++"
    cppdialect "C++20"
    buildoptions { "/utf-8" }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "AstralEngine/vendors/spdlog/include",
        "AstralEngine/vendors/glfw/include",
        "AstralEngine/vendors/glad/include",
        "%{prj.name}/vendors/imgui",
        "%{prj.name}/vendors/imgui/backends",
        "%{prj.name}/vendors/glm",
        "AstralEngine/src"
    }

    links {
        "AstralEngine"
    }

    filter "system:windows" 
        systemversion "latest"
        staticruntime "On"

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


group "Dependancies"
    include "AstralEngine/vendors/glfw"
    include "AstralEngine/vendors/glad"
    include "AstralEngine/vendors/imgui"
group ""


project "AstralEngine"
    location "AstralEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    buildoptions { 
        "/utf-8",
        "/external:I" .. "%{prj.name}/vendors",
        "/external:W0"
    }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp",
    }

    externalincludedirs {
        "%{prj.name}/vendors/spdlog/include",
        "%{prj.name}/vendors/glfw/include",
        "%{prj.name}/vendors/glad/include",
        "%{prj.name}/vendors/imgui",
        "%{prj.name}/vendors/imgui/backends",
        "%{prj.name}/vendors/glm",
    }

    includedirs {
        "%{prj.name}/src"
    }

    links{
        "GLFW",
        "GLAD",
        "opengl32.lib",
        "imgui"
    }

    pchheader "Common.h"
    pchsource "%{prj.name}/src/Common.cpp"

    filter "system:windows" 
        systemversion "latest"
        staticruntime "On"
        externalanglebrackets "On"
        externalwarnings "Off"

        defines {
            "AST_PLATFORM_WINDOWS",
            "AST_BUILD_DLL"
        }
    
    filter { "configurations:Debug" }
        defines { "AST_DEBUG" }
        symbols "On"
        runtime "Debug"

    filter { "configurations:Release" }
        defines { "AST_RELEASE" }
        optimize "On"
        runtime "Release"

    filter { "configurations:Dist" }
        defines { "AST_DIST" }
        optimize "On"
        runtime "Release"