workspace "AstralEngine"
    startproject "Sandbox"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"    
    buildoptions { "/utf-8" }
    externalanglebrackets "On"
    externalwarnings "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    files { 
        "Sandbox/src/**.h", 
        "Sandbox/src/**.cpp",
    }

    externalincludedirs {
        "AstralEngine/vendors/spdlog/include",
        "AstralEngine/vendors/glfw/include",
        "AstralEngine/vendors/glad/include",
        "AstralEngine/vendors/imgui",
        "AstralEngine/vendors/imgui/backends",
        "AstralEngine/vendors/glm",
    }

    includedirs {
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
        "/wd6294",
        "/wd26495",
        "/wd26498",
        "/wd62800",
    }
    externalanglebrackets "On"
    externalwarnings "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    files { 
        "AstralEngine/src/**.h", 
        "AstralEngine/src/**.cpp"
    }

    externalincludedirs {
        "AstralEngine/vendors/spdlog/include",
        "AstralEngine/vendors/glfw/include",
        "AstralEngine/vendors/glad/include",
        "AstralEngine/vendors/imgui",
        "AstralEngine/vendors/imgui/backends",
        "AstralEngine/vendors/glm",
    }

    includedirs {
        "AstralEngine/src"
    }

    links{
        "GLFW",
        "GLAD",
        "opengl32.lib",
        "imgui"
    }
    
    pchheader "Common.h"
    pchsource "AstralEngine/src/Common.cpp"

    filter "system:windows" 
        systemversion "latest"
        staticruntime "On"

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