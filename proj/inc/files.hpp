#pragma once
#include "pch.hpp"

namespace NDL
{
	struct File;
	typedef std::unordered_map<std::string, std::unique_ptr<File>> FolderMap;

	struct File
	{
		std::string type;
		FolderMap files;
		std::vector<std::string> overrides;
		std::vector<std::string> excludes;
	};

}
