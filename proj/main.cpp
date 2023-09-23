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
#include "status.hpp"

#define NEEDLEMAKE_VERSION "0.1.1b"

Result program()
{
	std::filesystem::current_path(ProjectDir);

	try
	{
		Yaml::Node root;
		Yaml::Parse(root, Conf.string().c_str());

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

		Yaml::Serialize(root, Conf.string().c_str());
		
		return Result(
			ErrorCode::ConfigFileMissing,
			"Configuration file missing.\n"
			"A new file has been created: APPDATA/chloeware/chloeconf.yml.\n"
			"The file itself contains the instructions to fill it out."
		);
	}
	
	if(CmdOptions.CleanMod)
		std::filesystem::remove_all(ModsDir / Project::pathName / "disk");
	if(CmdOptions.CleanInt)
		std::filesystem::remove_all(IntDir);
		
	if(CmdOptions.ExtractDisks)
		Disks::Unpack();
	
	switch(CmdAction)
	{
	case Action::Status:
		Status::Build::Print();
		Status::Config::Print();
		Status::Toolset::Print();
		return Result();
	case Action::DownloadToolset:
		std::filesystem::remove(CpkMaker);
		std::filesystem::remove(PackCpk);
		std::filesystem::remove(ar0pack);
		std::filesystem::remove(ar0unpack);
		std::filesystem::remove(pacpack);
		std::filesystem::remove(SFPacZip);
		std::filesystem::remove(SFPac);

		#define NDL_DOWNLOAD_TOOL(path, url)											\
			std::cout << ANSI::BG_BrightGreen << ANSI::FG_Black <<						\
				"Curling " << path.filename().string() << "..." << ANSI::Reset << "\n";	\
			std::filesystem::create_directories(ToolsDir);								\
			Util::Shell("curl", { "-L", "-o", const_cast<char*>(path.c_str()), url });	\

		NDL_DOWNLOAD_TOOL(CpkMaker, "https://github.com/blueskythlikesclouds/"
			"SkythTools/raw/master/Common/CpkMaker.dll")
		NDL_DOWNLOAD_TOOL(PackCpk, "https://github.com/blueskythlikesclouds/"
			"SkythTools/raw/master/Common/PackCpk.exe")
		NDL_DOWNLOAD_TOOL(ar0pack, "https://github.com/blueskythlikesclouds/"
			"/SkythTools/raw/master/Sonic+Generations/ar0pack.exe")
		NDL_DOWNLOAD_TOOL(ar0unpack, "https://github.com/blueskythlikesclouds/"
			"/SkythTools/raw/master/Sonic+Generations/ar0unpack.exe")
		NDL_DOWNLOAD_TOOL(pacpack, "https://github.com/DarioSamo"
			"/libgens-sonicglvl/raw/master/master/bin/pacpack.exe")

		#undef NDL_DOWNLOAD_TOOL
			
		if(!std::filesystem::exists(SFPac))
		{
			std::cout << ANSI::BG_BrightGreen << ANSI::FG_Black <<
				"Curling and unzipping SFPac..." << ANSI::Reset << "\n";
			std::filesystem::create_directories(ToolsDir);
			Util::Shell("curl", {
				"-L", "-o", const_cast<char*>(SFPacZip.c_str()),
				// Why zipped :(
				"https://docs.google.com/uc?export=download&id=1kunzqJIsz5Tzr5zmHb-AaC2Bj516nJoT"
			});
			std::filesystem::current_path(ToolsDir);
			Util::Shell("unzip", { 
				const_cast<char*>(SFPacZip.filename().c_str()) });
			std::filesystem::current_path(ProjectDir);
		}
		if(std::filesystem::exists(SFPacZip))
			std::filesystem::remove(SFPacZip);
		return Result();
	case Action::Help:
		std::cout << HelpSource << "\n";
		return Result();
	case Action::MakeProject:
		Project::Load();
		Project::Make();
		return Result();
	case Action::BuildMod:
		Project::Load();
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
