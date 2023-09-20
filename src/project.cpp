#include "pch.hpp"
#include "project.hpp"

#include "files.hpp"
#include "conf.inl"
#include "package.hpp"

void Project::Make()
{
	std::filesystem::path diskDir = DisksDir;
	std::filesystem::path projDir = ProjectDir;
	std::filesystem::path intDir = IntDir;
	
	return Package::Unpack(
		Project::disks,
		diskDir,
		projDir,
		intDir);
}

void LoadPackage(
	std::unique_ptr<NDL::File> &file, Yaml::Node &yamlFile)
{
	file->overrides = std::vector<std::string>();
	file->excludes = std::vector<std::string>();

	if(!yamlFile["overrides"].IsNone())
		for(auto i = yamlFile["overrides"].Begin(); i != yamlFile["overrides"].End(); i++)
		{
			file->overrides.emplace_back((*i).second.As<std::string>());
		}
	if(!yamlFile["excludes"].IsNone())
		for(auto i = yamlFile["excludes"].Begin(); i != yamlFile["excludes"].End(); i++)
		{
			file->excludes.emplace_back((*i).second.As<std::string>());
		}
}

void LoadFolder(
	std::unique_ptr<NDL::File> &file, Yaml::Node &yamlFile)
{
	for(auto i = yamlFile.Begin(); i != yamlFile.End(); i++)
	{
		std::string name = (*i).first;
		if ((name.compare("type") == 0) ||
			(name.compare("overrides") == 0) ||
			(name.compare("excludes") == 0)
		) continue;

		Yaml::Node &yamlFile_out = (*i).second;

		file->files.insert({name, std::make_unique<NDL::File>(NDL::File{
			.type = yamlFile_out["type"].As<std::string>(),
			.files = NDL::FolderMap(),
			.overrides = std::vector<std::string>(),
			.excludes = std::vector<std::string>(),
		})});
		std::unique_ptr<NDL::File> &file_out = file->files[name];

		if(file_out->type.compare("Folder") == 0)
		{
			LoadFolder(file_out, yamlFile_out);
		}
		else if(file_out->type.compare("Package") == 0)
		{
			LoadPackage(file_out, yamlFile_out);
		}
	}
}

Result Project::Load()
{
	Yaml::Node root;
	try
	{
		Yaml::Parse(root, (ProjectDir / "needlemake.yml").string().c_str());

		Project::game			= StringToGame(root["game"].As<std::string>());

		Project::pathName		= root["pathName"].		As<std::string>();

		Project::title			= root["Title"].		As<std::string>();
		Project::description	= root["Description"].	As<std::string>();
		Project::version		= root["Version"].		As<std::string>();
		Project::author			= root["Author"].		As<std::string>();
		Project::authorURL		= root["AuthorURL"].	As<std::string>();

		switch(Project::game)
		{
		case Project::Game::Blueblur:
			DisksDir = BlueblurDisksDir;
			IntDir = BlueblurIntDir;
			ModsDir = BlueblurModsDir;

			Packer = ar0pack;
			Unpacker = ar0unpack;
			break;
		case Project::Game::Sonic2013:
			DisksDir = Sonic2013DisksDir;
			DlcDisksDir = Sonic2013DlcDisksDir;
			IntDir = Sonic2013IntDir;
			ModsDir = Sonic2013ModsDir;

			Packer = pacpack;
			Unpacker = pacpack;
			break;
		case Project::Game::Wars:
			DisksDir = WarsDisksDir;
			IntDir = WarsIntDir;
			ModsDir = WarsModsDir;

			Packer = SFPac;
			Unpacker = SFPac;
			break;
		case Project::Game::Rangers:
			DisksDir = RangersDisksDir;
			IntDir = RangersIntDir;
			ModsDir = RangersModsDir;

			Packer = frontpac;
			Unpacker = frontpac;
			break;
		default:
			return Result(
				ErrorCode::UnknownGame,
				"Supported games currently are:\n" // TODO: Update this
				"- Wars\n"
				"- Blueblur\n");
		}

		Project::disks = NDL::FolderMap();
		for(auto i = root["disks"].Begin(); i != root["disks"].End(); i++)
		{
			std::string name = (*i).first;
			Yaml::Node &yamlDisk = (*i).second;

			Project::disks.insert({name, std::make_unique<NDL::File>(NDL::File {
				.type = "DISK",
				.files = NDL::FolderMap(),
				.overrides = std::vector<std::string>(),
				.excludes = std::vector<std::string>(),
			})});
			auto &disk = Project::disks[name];

			LoadFolder(disk, yamlDisk);
		}

		return Result();
	}
	catch (const std::exception &e)
	{
		return Result(
			ErrorCode::ProjectFileMissing,
			"There is no project file in this directory.\n"
			"Make sure you're in the correct directory, if "
			"the file is just not there, you can use the -H "
			"option for help on making a project file."
		);
	}
}

