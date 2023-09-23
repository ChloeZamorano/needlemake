#include "pch.hpp"
#include "mod.hpp"

#include "project.hpp"
#include "conf.inl"
#include "util.inl"
#include "package.hpp"

void UpdateModINI(mINI::INIStructure &ini)
{
	auto t = std::time(0);
	std::tm now = *std::gmtime(&t);

	ini["Desc"]["Author"] 		= Project::author;
	ini["Desc"]["Title"]		= Project::title;
	ini["Desc"]["Version"]		= Project::version;
	ini["Desc"]["Description"]	= Project::description;
	ini["Desc"]["AuthorURL"]	= Project::authorURL;
	ini["Desc"]["Date"]			= Util::C_TimeToString(now);
}

void Mod::Build()
{
	std::filesystem::path diskDir = DisksDir;
	std::filesystem::path projDir = ProjectDir;
	std::filesystem::path intDir = IntDir;
	std::filesystem::path modDir = ModsDir / Project::pathName;
	std::filesystem::path iniDir = modDir / "mod.ini";
	modDir /= "disk";
	
	if(!std::filesystem::exists(iniDir))
	{
		mINI::INIFile file(iniDir.string());
		mINI::INIStructure ini;

		UpdateModINI(ini);

		ini["Main"]["UpdateServer"]		= "";
		ini["Main"]["SaveFile"]			= "";
		ini["Main"]["ID"]				= std::to_string(Util::C_LongRand());
		ini["Main"]["IncludeDir0"]		= ".";
		ini["Main"]["IncludeDirCount"]	= "1";
		ini["Main"]["DependsCount"]		= "0";
		ini["Main"]["DLLFile"]			= "";
		ini["Main"]["CodeFile"]			= "";
		ini["Main"]["ConfigSchemaFile"]	= "";

		file.generate(ini, true);
	}
	else
	{
		mINI::INIFile file(iniDir.string());
		mINI::INIStructure ini;
		file.read(ini);

		UpdateModINI(ini);

		file.write(ini, true);
	}
	
	std::string
		extension,
		split_extension,
		list_extension,
		patch_disk;
	switch(Project::game)
	{
	case Project::Game::Blueblur:
		extension = ".ar.00";
		split_extension = ".ar.";
		list_extension = ".arl";
		patch_disk = "NONE";
		break;
	case Project::Game::Sonic2013:
		extension = ".pac";
		split_extension = ".pac.";
		list_extension = "NONE";
		patch_disk = "sonic2013_patch_0";
		break;
	case Project::Game::Wars:
		extension = ".pac";
		split_extension = ".pac.";
		list_extension = "NONE";
		patch_disk = "wars_patch";
		break;
	case Project::Game::Rangers:
		extension = ".pac";
		split_extension = ".pac.";
		list_extension = "NONE";
		patch_disk = "TODO";
		break;
	default:
		return; // TODO: Error
	}

	Package::Pack(Project::disks,
		diskDir, projDir, intDir, modDir,
		extension, split_extension,
		list_extension, patch_disk);
}
