project "GLAD"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "include/**.h",
        "src/**.c"
    }

    includedirs {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "Off"

        links { "opengl32" }

    filter { "configurations:Debug" }
        runtime "Debug"

    filter { "configurations:Release" }
        runtime "Release"

    filter { "configurations:Dist" }
        runtime "Release"