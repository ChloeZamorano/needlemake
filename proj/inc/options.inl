#pragma once
#include "pch.hpp"

#define X(x) x,

#define ENTRIES				\
	X(Help)					\
	X(MakeProject)			\
	X(BuildMod)				\
	X(DownloadToolset)		\
	X(Status)				\

enum class Action : u32
{
	INVALID = 0,
	ENTRIES
};

#undef X
// Trusting the compiler will add the elses
#define X(x)								\
	if(v.compare(#x) == 0) return Action::x;\

inline Action GetAction(const std::string& v)
{
	ENTRIES
	return Action::INVALID;
}

#undef ENTRIES
#undef X

struct Options
{
	std::vector<std::filesystem::path> projects;
	bool ExtractDisks;
	bool RextractDisks;
	bool PrecleanMod;
	bool PrecleanInt;
	bool CleanMod;
	bool CleanInt;
};

inline Options CmdOptions;
inline Action CmdAction;

inline void BuildArgs(const u32 argc, ccstr *argv)
{
	if(argc < 2)
	{
		std::cout << "TODO: Message for empty call.\n";
	}
	CmdAction = GetAction(argv[1]);
	if(argc > 2)
	{
		for(u32 i = 2; i < argc; ++i)
		{
			std::string str(argv[i]);

			if(str.find("-") != 0)
			{
				std::cout << "TODO: Message for extra actions.\n";
			}
			else if(str.find("-p=") == 0)
			{
				CmdOptions.projects.emplace_back(str.substr(3));
			}
			else
			{
				if(str.find("Ex" ) != std::string::npos) CmdOptions.ExtractDisks	= true;
				if(str.find("Rx" ) != std::string::npos) CmdOptions.RextractDisks	= true;
				if(str.find("Pcm") != std::string::npos) CmdOptions.PrecleanMod		= true;
				if(str.find("Pci") != std::string::npos) CmdOptions.PrecleanInt		= true;
				if(str.find("Cm" ) != std::string::npos) CmdOptions.CleanMod		= true;
				if(str.find("Ci" ) != std::string::npos) CmdOptions.CleanInt		= true;
			}
		}
	}
	if(CmdOptions.projects.size() < 1)
	{
		CmdOptions.projects.push_back(std::filesystem::current_path());
	}
}
