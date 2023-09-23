#include "pch.hpp"
#include "disk_unpacker.hpp"

#include "conf.inl"
#include "util.inl"
#include "project.hpp"
#include "options.inl"

void Disks::Unpack()
{
	std::filesystem::current_path(DisksDir);

	for(auto &disk : Project::disks)
	{
		std::string disk_dir_path = (DisksDir / disk.first).string();
		std::string disk_path = disk_dir_path + ".cpk";

		if(!std::filesystem::exists(disk_path))
		{
			disk_dir_path = (DlcDisksDir / disk_dir_path.substr(14, 4) / disk.first).string();
			disk_path = disk_dir_path + ".cpk";
		}

		if(std::filesystem::exists(disk_dir_path))
		{
			std::cout << "Disk folder " << disk.first << " already exists.\n";

			if(!CmdOptions.RextractDisks) continue;

			std::cout << "Do you wish to re-extract the disk?\n";

			if(Util::YesNoQuestion())
			{
				Util::Shell(PackCpk.c_str(), {const_cast<char*>(disk_path.c_str())});
			}
		}
		else
		{
			Util::Shell(PackCpk.c_str(), {const_cast<char*>(disk_path.c_str())});
		}
	}

	std::filesystem::current_path(ProjectDir);
}
