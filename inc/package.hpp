#pragma once
#include "pch.hpp"

#include "files.hpp"
#include "conf.inl"
#include "util.inl"
#include "result.inl"

namespace Package
{
	void Unpack(
		NDL::FolderMap &files,
		std::filesystem::path &diskDir,
		std::filesystem::path &projDir,
		std::filesystem::path &intDir);

	void Pack(
		NDL::FolderMap &files,
		std::filesystem::path &diskDir,
		std::filesystem::path &projDir,
		std::filesystem::path &intDir,
		std::filesystem::path &modDir,
		std::string &ext,
		std::string &split_ext,
		std::string &opt_ext,
		std::string &patch);
}
