#include "pch.hpp"

#ifndef DEBUG
	#define DEBUG
#endif

#include "files.hpp"
#include "help.hpp"
#include "result.inl"
#include "conf.inl"
#include "util.inl"
#include "project.hpp"
#include "options.inl"
#include "disk_unpacker.hpp"
#include "mod.hpp"

Result program()
{
	std::filesystem::current_path(ProjectDir);

	try
	{
		Yaml::Node root;
		Yaml::Parse(root, (ConfDir / "chloeconf.yml").string().c_str());

		BlueblurDisksDir	= root["needlemake"]["blueblur"]["disks_dir"].	As<std::string>();
		BlueblurIntDir		= root["needlemake"]["blueblur"]["int_dir"].	As<std::string>();
		BlueblurModsDir		= root["needlemake"]["blueblur"]["mods_dir"].	As<std::string>();

		Sonic2013DisksDir	= root["needlemake"]["sonic2013"]["disks_dir"].		As<std::string>();
		Sonic2013DlcDisksDir= root["needlemake"]["sonic2013"]["dlc_disks_dir"].	As<std::string>();
		Sonic2013IntDir		= root["needlemake"]["sonic2013"]["int_dir"].		As<std::string>();
		Sonic2013ModsDir	= root["needlemake"]["sonic2013"]["mods_dir"].		As<std::string>();

		WarsDisksDir	= root["needlemake"]["wars"]["disks_dir"].	As<std::string>();
		WarsIntDir		= root["needlemake"]["wars"]["int_dir"].	As<std::string>();
		WarsModsDir		= root["needlemake"]["wars"]["mods_dir"].	As<std::string>();

		RangersDisksDir	= root["needlemake"]["rangers"]["disks_dir"].	As<std::string>();
		RangersIntDir	= root["needlemake"]["rangers"]["int_dir"].	As<std::string>();
		RangersModsDir	= root["needlemake"]["rangers"]["mods_dir"].	As<std::string>();


		CpkMaker	= ToolsDir / "CpkMaker.dll";
		PackCpk		= ToolsDir / "PackCpk.exe";

		ar0pack		= ToolsDir / "ar0pack.exe";
		ar0unpack	= ToolsDir / "ar0unpack.exe";

		pacpack		= ToolsDir / "pacpack.exe";

		SFPacZip	= ToolsDir / "SFPacZip.zip";
		SFPac		= ToolsDir / "SFPac.exe";
	}
	catch (const std::exception &e)
	{
		Yaml::Node root;

		root["needlemake"]["wars"]["disks_dir"] =
			"C:/Path/to/Sonic/Forces/disk/directory/";
		root["needlemake"]["wars"]["int_dir"] =
			"E:\\Path\\to\\intermediate\\directory.\\maybe\\in\\%TEMP%,\\doesnt\\matter";
		root["needlemake"]["wars"]["mods_dir"] =
			"C:/Path\\to/Sonic\\Forces/mods\\directory/";

		Yaml::Serialize(root, (ConfDir / "chloeconf.yml").string().c_str());
		
		return Result(
			ErrorCode::ConfigFileMissing,
			"Configuration file missing.\n"
			"A new file has been created: APPDATA/chloeware/chloeconf.yml.\n"
			"The file itself contains the instructions to fill it out."
		);
	}

	// TODO: Find out why these aren't downloading correctly.
	#define DOWNLOAD_STD(path, url)								\
	if(!std::filesystem::exists(path))							\
	{															\
		std::filesystem::create_directories(ToolsDir);			\
		Util::RunExternal("curl", { "-L", "-o", path.string(), url });\
	}															\
	
	//DOWNLOAD_STD(CpkMaker,	"https://raw.githubusercontent.com/blueskythlikesclouds"
	//	"/SkythTools/master/Common/CpkMaker.dll")
	//DOWNLOAD_STD(PackCpk,	"https://raw.githubusercontent.com/blueskythlikesclouds"
	//	"/SkythTools/master/Common/PackCpk.dll")
	//DOWNLOAD_STD(ar0pack,	"https://raw.githubusercontent.com/blueskythlikesclouds"
	//	"/SkythTools/master/Sonic+Generations/ar0pack.exe")
	//DOWNLOAD_STD(ar0unpack,	"https://raw.githubusercontent.com/blueskythlikesclouds"
	//	"/SkythTools/master/Sonic+Generations/ar0unpack.exe")
	//DOWNLOAD_STD(pacpack,	"https://github.com/DarioSamo/libgens-sonicglvl/blob"
	//	"/master/bin/pacpack.exe")
		
	#undef DOWNLOAD_STD

	//if(!std::filesystem::exists(SFPac))
	//{
	//	std::filesystem::create_directories(ToolsDir);
	//	Util::RunExternal("curl", {
	//		"-L", "-o", SFPacZip,
	//		// Why zipped :(
	//		"https://docs.google.com/uc?export=download&id=1kunzqJIsz5Tzr5zmHb-AaC2Bj516nJoT"
	//	});
	//	std::filesystem::current_path(ToolsDir);
	//	Util::RunExternal("tar", { "-xf", SFPacZip });
	//	std::filesystem::current_path(ProjectDir);
	//	std::filesystem::remove(SFPacZip);
	//}
	
	Result r;

	r = Project::Load();
	if(r.Error != ErrorCode::Success) return r;

	
	if(CmdOptions.CleanMod)
		std::filesystem::remove_all(ModsDir / Project::pathName / "disk");
	if(CmdOptions.CleanInt)
		std::filesystem::remove_all(IntDir);
		
	if(CmdOptions.ExtractDisks)
		Disks::Unpack();
	
	switch(CmdAction)
	{
	case Action::Help:
		std::cout << HelpSource << "\n";
		return Result();
	case Action::MakeProject:
		Project::Make();
		return Result();
	case Action::BuildMod:
		Mod::Build();
		return Result();
	default:
		std::cout << "Action is " << (u32)CmdAction << "\n";
		return Result(); // TODO: Error
	}

	if(CmdOptions.CleanMod)
		std::filesystem::remove_all(ModsDir / Project::pathName / "disk");
	if(CmdOptions.CleanInt)
		std::filesystem::remove_all(IntDir);

	return Result();
}

i32 main(const i32 argc, ccstr *argv)
{
	if(argc < 2)
	{
		std:: cout << "No options.\n";
		return 69;
	}
	else
	{
		BuildArgs(argc, argv);

		for(auto &project : CmdOptions.projects)
		{
			ProjectDir = project;
			Result result = program();

			if(result.Error != ErrorCode::Success)
			{
				result.Print();
				return static_cast<i32>(result.Error);
			}
		}
	}
	return 0;
}
