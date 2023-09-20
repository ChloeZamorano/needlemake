#pragma once
#include "pch.hpp"

inline std::filesystem::path ProjectDir;

inline std::filesystem::path ConfDir =
	std::string(std::getenv("APPDATA")) + "/chloeware";
inline std::filesystem::path ToolsDir =
	std::filesystem::path(std::getenv("LOCALAPPDATA")) / "Programs/needlemake";

inline std::filesystem::path DisksDir;
inline std::filesystem::path DlcDisksDir;
inline std::filesystem::path IntDir;
inline std::filesystem::path ModsDir;

inline std::filesystem::path BlueblurDisksDir;
inline std::filesystem::path BlueblurIntDir;
inline std::filesystem::path BlueblurModsDir;

inline std::filesystem::path Sonic2013DisksDir;
inline std::filesystem::path Sonic2013DlcDisksDir;
inline std::filesystem::path Sonic2013IntDir;
inline std::filesystem::path Sonic2013ModsDir;

inline std::filesystem::path WarsDisksDir;
inline std::filesystem::path WarsIntDir;
inline std::filesystem::path WarsModsDir;

inline std::filesystem::path RangersDisksDir;
inline std::filesystem::path RangersIntDir;
inline std::filesystem::path RangersModsDir;

inline std::filesystem::path CpkMaker;
inline std::filesystem::path PackCpk;

inline std::filesystem::path Packer;
inline std::filesystem::path Unpacker;

inline std::filesystem::path ar0pack;
inline std::filesystem::path ar0unpack;
inline std::filesystem::path pacpack;
inline std::filesystem::path SFPacZip;
inline std::filesystem::path SFPac;
inline std::filesystem::path frontpac; // TODO: Make this a thing
