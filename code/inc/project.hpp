#pragma once
#include "pch.hpp"

#include "files.hpp"
#include "result.inl"

namespace Project
{
	#define X(x) x,

	#define ENTRIES	\
		X(Blueblur)	\
		X(Sonic2013)\
		X(Wars)		\
		X(Rangers)	\

	enum class Game : u8
	{
		Unkown = 0,
		ENTRIES
	};

	#undef X
	#define X(x) if(v.compare(#x) == 0) return Game::x;\


	inline Game StringToGame(std::string v)
	{
		std::transform(v.cbegin(), v.cend(), v.begin(), 
			[](unsigned char c) { return std::tolower(c); });
		std::transform(v.cbegin(), v.cbegin() + 1, v.begin(),
			[](unsigned char c) { return std::toupper(c); });

		ENTRIES
	
		return Game::Unkown;
	}

	#undef ENTRIES
	#undef X

	inline Game game;
	inline std::string pathName;

	inline std::string title;
	inline std::string description;
	inline std::string version;
	inline std::string author;
	inline std::string authorURL;

	inline NDL::FolderMap disks;

	// TODO: Result
	void Make();

	Result Load();
}
