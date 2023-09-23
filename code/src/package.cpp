#include "pch.hpp"
#include "package.hpp"

#include "files.hpp"
#include "conf.inl"
#include "util.inl"
#include "project.hpp"

void HandlePackageContent(
	std::unique_ptr<NDL::File> &file,
	std::filesystem::path &projDir,
	std::filesystem::path &intDir)
{
	for(auto &overide : file->overrides)
	{
		projDir /= overide;
		intDir /= overide;

		if(!std::filesystem::exists(projDir))
			std::filesystem::copy_file(intDir, projDir);

		projDir = projDir.parent_path();
		intDir = intDir.parent_path();
	}
	for(auto &exclude : file->excludes)
	{
		projDir /= exclude;
		intDir /= exclude;

		if(std::filesystem::exists(intDir))
			std::filesystem::remove(intDir);

		projDir = projDir.parent_path();
		intDir = intDir.parent_path();
	}
}

void Package::Unpack(
	NDL::FolderMap &files,
	std::filesystem::path &diskDir,
	std::filesystem::path &projDir,
	std::filesystem::path &intDir)
{
	for(auto &file_entry : files)
	{
		std::string filename = file_entry.first;
		std::unique_ptr<NDL::File> &file = file_entry.second;
		
		if(file->type.compare("Package") == 0)
		{
			projDir /= filename;
			std::filesystem::create_directories(diskDir);
			std::filesystem::create_directories(intDir);
			diskDir /= filename + (
				(Project::game == Project::Game::Wars) ?
				".pac" : ".ar.00");
			intDir /= filename;
			std::filesystem::create_directories(projDir);
			
			Util::Shell(Unpacker.c_str(), {const_cast<char*>(diskDir.c_str())});
			
			diskDir = diskDir.parent_path() / filename;
			std::filesystem::rename(diskDir, intDir);

			HandlePackageContent(file, projDir, intDir);

			diskDir = diskDir.parent_path();
			intDir = intDir.parent_path();
			projDir = projDir.parent_path();
		}
		else if(file->type.compare("Folder") == 0)
		{
			diskDir /= filename;
			intDir /= filename;
			projDir /= filename;

			Unpack(file->files, diskDir, projDir, intDir);

			diskDir = diskDir.parent_path();
			intDir = intDir.parent_path();
			projDir = projDir.parent_path();
		}
		else if(file->type.compare("DISK") == 0)
		{
			diskDir /= filename;
			intDir /= filename;
			projDir /= filename;

			std::filesystem::create_directories(intDir);
			std::filesystem::create_directories(projDir);

			Unpack(file->files, diskDir, projDir, intDir);

			diskDir = diskDir.parent_path();
			intDir = intDir.parent_path();
			projDir = projDir.parent_path();
		}
		else
		{
			diskDir /= filename;
			intDir /= filename;
			std::filesystem::create_directories(projDir);
			projDir /= filename;


			if(!std::filesystem::exists(projDir))
				std::filesystem::copy(diskDir, projDir);


			diskDir = diskDir.parent_path();
			intDir = intDir.parent_path();
			projDir = projDir.parent_path();
		}
	}
}

void Package::Pack(
	NDL::FolderMap &files,
	std::filesystem::path &diskDir,
	std::filesystem::path &projDir,
	std::filesystem::path &intDir,
	std::filesystem::path &modDir,
	std::string &ext,
	std::string &split_ext,
	std::string &opt_ext,
	std::string &patch)
{
	for(auto &file_entry : files)
	{
		std::string filename = file_entry.first;
		std::unique_ptr<NDL::File> &file = file_entry.second;
		
		if(file->type.compare("DISK") == 0)
		{
			diskDir /= filename;
			projDir /= filename;
			intDir /= filename;
			modDir /=
				(patch.empty()) ?
				filename : patch;

			Pack(file->files,
				diskDir, projDir, intDir, modDir,
				ext, split_ext, opt_ext, patch);

			diskDir = diskDir.parent_path();
			projDir = projDir.parent_path();
			intDir = intDir.parent_path();
			modDir = modDir.parent_path();
		}
		else if(file->type.compare("Folder") == 0)
		{
			diskDir /= filename;
			projDir /= filename;
			intDir /= filename;
			modDir /= filename;

			Pack(file->files,
				diskDir, projDir, intDir, modDir,
				ext, split_ext, opt_ext, patch);

			diskDir = diskDir.parent_path();
			projDir = projDir.parent_path();
			intDir = intDir.parent_path();
			modDir = modDir.parent_path();
		}
		else if(file->type.compare("Package") == 0)
		{
			diskDir /= filename;
			projDir /= filename;
			auto intFolder = intDir / filename;
			intDir /= filename + ext;

			std::filesystem::create_directories(modDir);
			
			for(auto &file : std::filesystem::directory_iterator(projDir))
			{
				auto &filePath = file.path();
				auto targetPath = intFolder / filePath.filename();

				if(std::filesystem::exists(targetPath))
					std::filesystem::remove(targetPath);
				std::filesystem::copy(filePath, targetPath);
			}

			Util::Shell(Packer.c_str(), {const_cast<char*>(intFolder.c_str())});

			for(auto &file : std::filesystem::directory_iterator(intDir.parent_path()))
			{
				auto &filePath = file.path();
				auto filename = filePath.filename().string();

				if( (filename.rfind(split_ext) != std::string::npos) ||
					(filename.rfind(ext) == (filename.size() - 4)) ||
					(filename.rfind(opt_ext) == (filename.size() - 4)))
						std::filesystem::rename(filePath,
							modDir / filePath.filename());
			}

			diskDir = diskDir.parent_path();
			projDir = projDir.parent_path();
			intDir = intDir.parent_path();
		}
		else
		{
			diskDir /= filename;
			projDir /= filename;
			intDir /= filename;
			modDir /= filename;

			std::filesystem::create_directories(modDir.parent_path());

			std::filesystem::copy(projDir, modDir);

			diskDir = diskDir.parent_path();
			projDir = projDir.parent_path();
			intDir = intDir.parent_path();
			modDir = modDir.parent_path();
		}
	}
}
