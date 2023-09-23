#pragma once
#include "pch.hpp"

namespace Status::Build
{
	const std::string Name = "Needlemake";
	const std::string Config = "Debug";
	const std::string Platform = "Windows";
	const std::string Architecture = "x64";
	const std::string Environment = "MSYS2";
	const std::string Compiler = "G++";

	const u16 Major = 0;
	const u16 Minor = 1;
	const u16 Patch = 1;
	const char Type = 'a';

	void Print();
}

namespace Status::Config
{
	void Print();
}

namespace Status::Toolset
{
	void PrintTool(
		const u32 check,
		const std::string &name,
		const std::filesystem::path &fp);

	void Print();
}
