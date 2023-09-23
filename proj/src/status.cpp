#include "pch.hpp"
#include "status.hpp"

#include "conf.inl"
#include "util.inl"

void Status::Build::Print()
{
	std::cout
		<< ANSI::FG_Black << ANSI::BG_Blue << ANSI::Bold <<
		"===========================================================" << ANSI::Reset << "\n"

		<< ANSI::FG_Black << ANSI::BG_Blue << ANSI::Bold <<

		Name << " " << ANSI::Underline <<
		Major << "." << Minor << "." << Patch << Type
		<< ANSI::ResetUnderline <<

		" (" << Config << "-" << Platform << "-" << Architecture
		<< "-" << Environment << "-" << Compiler << ")"
			"            " << ANSI::Reset << "\n"

		<< ANSI::FG_Black << ANSI::BG_Blue << ANSI::Bold <<
		"===========================================================" << ANSI::Reset << "\n";
}

void Status::Config::Print()
{
	std::cout <<
		ANSI::Bold << ANSI::BG_Cyan << ANSI::FG_Black <<
		"Configuration:" << ANSI::Reset << "\n" <<
		"    Filepath: " <<
			ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			Conf << ANSI::Reset << "\n"

		"    BlueblurDisksDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			BlueblurDisksDir << ANSI::Reset << "\n" <<
		"    BlueblurIntDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			BlueblurIntDir << ANSI::Reset << "\n" <<
		"    BlueblurModsDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			BlueblurModsDir << ANSI::Reset << "\n" <<
		"    Sonic2013DisksDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			Sonic2013DisksDir << ANSI::Reset << "\n" <<
		"    Sonic2013DlcDisksDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			Sonic2013DlcDisksDir << ANSI::Reset << "\n" <<
		"    Sonic2013IntDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			Sonic2013IntDir << ANSI::Reset << "\n" <<
		"    Sonic2013ModsDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			Sonic2013ModsDir << ANSI::Reset << "\n" <<
		"    WarsDisksDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			WarsDisksDir << ANSI::Reset << "\n" <<
		"    WarsIntDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			WarsIntDir << ANSI::Reset << "\n" <<
		"    WarsModsDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			WarsModsDir << ANSI::Reset << "\n" <<
		"    RangersDisksDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			RangersDisksDir << ANSI::Reset << "\n" <<
		"    RangersIntDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			RangersIntDir << ANSI::Reset << "\n" <<
		"    RangersModsDir: " << ANSI::Underline << ANSI::FG_Cyan << ANSI::Bold <<
			RangersModsDir << ANSI::Reset << "\n" <<

		ANSI::Reset << "\n";
}

void Status::Toolset::PrintTool(
    const u32 check,
    const std::string &name,
    const std::filesystem::path &fp)
{
	if(!std::filesystem::exists(fp))
	{
		std::cout << ANSI::Bold << ANSI::BG_BrightMagenta << ANSI::FG_Black <<
			"    " << name << " is missing. Run the DownloadToolset action."
			<< ANSI::Reset << "\n";
	}
	else
	{
		u32 hash = Util::FileHashAdler32(fp);

		if(hash == check)
		{
			std::cout <<
				"    " << name << ": " << ANSI::FG_Green << ANSI::Bold <<
					ANSI::Underline << fp << ANSI::Reset << "\n";
		}
		else
		{
			std::cout <<
				"    " << name << ": " << ANSI::FG_Black << ANSI::BG_Red << ANSI::Bold <<
					ANSI::Underline << fp << ANSI::ResetUnderline <<
					": File is corrupted. Run the DownloadToolset action."
					<< ANSI::Reset << "\n";
		}
	}
}

void Status::Toolset::Print()
{
std::cout <<
	ANSI::Bold << ANSI::BG_Cyan << ANSI::FG_Black <<
	"Toolset:" << ANSI::Reset << "\n";

	PrintTool(0x5aeb0051, "ar0pack", ar0pack);
	PrintTool(0x6ca200f5, "ar0unpack", ar0unpack);
	PrintTool(0x28ed0051, "pacpack", pacpack);
	PrintTool(0x535f0001, "SFPac", SFPac);
	PrintTool(0x18000001, "PackCpk", PackCpk);
	PrintTool(0x18960001, "CpkMaker", CpkMaker);
	
	std::cout <<
		"    FrontiersPack: " << ANSI::FG_Black << ANSI::BG_Magenta << ANSI::Bold <<
			"lolno" << ANSI::Reset << "\n";
}
