workspace "needlemake"
	startproject "needlemake"
	architecture "x86_64"

	configurations
	{
		"debug",
		"release",
		"deploy",
	}

	platforms
	{
		"windows"
	}

	OUTDIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	BUILDOPS = "-Wall -Werror -Wextra -pedantic -pedantic-errors -Wno-trigraphs -Wno-error=unused-variable -Wno-error=unused-parameter -Wno-error=missing-field-initializers -Wno-error=sign-compare"

	project "mini-yaml"
		kind "StaticLib"
		language "C++"
		cppdialect "C++20"
		cdialect "C17"

		targetdir ("%{wks.location}/bin/"..OUTDIR.."/%{prj.name}")
		objdir ("%{wks.location}/obj/"..OUTDIR.."/%{prj.name}")

		files { "deps/mini-yaml/yaml/Yaml.cpp" }

		includedirs { "deps/mini-yaml/yaml" }
		symbols "Off"
		buildoptions ("-Ofast")

	project "needlemake"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		cdialect "C17"

		targetdir ("%{wks.location}/bin/"..OUTDIR.."/%{prj.name}")
		objdir ("%{wks.location}/obj/"..OUTDIR.."/%{prj.name}")

		links
		{
			"mini-yaml"
		}

		files
		{
			"main.cpp",

			"src/**.cpp",
			"src/**.c",
			
			"pch.hpp"
		}

		includedirs
		{
			".",
			"inc/",
			"deps/mini-yaml/yaml",
			"deps/mINI/src/mini"
		}

		pchheader "pch.hpp"

		filter "platforms:windows"
			defines { "WINDOWS" }

		filter "configurations:debug"
			defines { "DEBUG" }
			symbols "On"
			buildoptions (BUILDOPS .. " -O0")
		filter "configurations:release"
			defines { "RELEASE" }
			symbols "On"
			buildoptions (BUILDOPS .. " -O2")
		filter "configurations:deploy"
			defines { "DEPLOY" }
			symbols "Off"
			buildoptions (BUILDOPS .. " -Ofast")
