#pragma once
#include "pch.hpp"

#include "terminal_colors.inl"

namespace Util
{
inline u32 FileHashAdler32(const std::string &fp)
{
		std::ifstream file(fp, std::ifstream::binary);

		file.seekg (0, file.end);
		u32 len = file.tellg();
		file.seekg (0, file.beg);

		u8 *buf = new u8[len];

		file.close();
		
		u32 hash = NDL_ADLER32(buf, len);
		delete buf;

		return hash;
}

inline std::string C_TimeToString(std::tm &tm)
{
	std::stringstream ss;
	switch(tm.tm_mon)
	{
		case  1:	ss << tm.tm_mday << "-Jan-" << tm.tm_year + 1900; break;
		case  2:	ss << tm.tm_mday << "-Feb-" << tm.tm_year + 1900; break;
		case  3:	ss << tm.tm_mday << "-Mar-" << tm.tm_year + 1900; break;
		case  4:	ss << tm.tm_mday << "-Apr-" << tm.tm_year + 1900; break;
		case  5:	ss << tm.tm_mday << "-May-" << tm.tm_year + 1900; break;
		case  6:	ss << tm.tm_mday << "-Jun-" << tm.tm_year + 1900; break;
		case  7:	ss << tm.tm_mday << "-Jul-" << tm.tm_year + 1900; break;
		case  8:	ss << tm.tm_mday << "-Aug-" << tm.tm_year + 1900; break;
		case  9:	ss << tm.tm_mday << "-Sep-" << tm.tm_year + 1900; break;
		case 10:	ss << tm.tm_mday << "-Oct-" << tm.tm_year + 1900; break;
		case 11:	ss << tm.tm_mday << "-Nov-" << tm.tm_year + 1900; break;
		case 12:	ss << tm.tm_mday << "-Dec-" << tm.tm_year + 1900; break;
	}
	return ss.str();
}

inline u64 C_LongRand()
{
	u64 out = 0;
	u32 *parts = reinterpret_cast<u32*>(&out);

	parts[0] = rand();
	parts[1] = rand();

	return out;
}

inline bool YesNoQuestion()
{
	std::cout << "Y/N\n";
	
	char reply = ' ';
	while(
		reply != 'y' && reply != 'Y' &&
		reply != 'n' && reply != 'N')
			std::cin >> reply;

	if(reply == 'y' || reply == 'Y')
		return true;
	return false;
}

inline void YamlForeach(
	Yaml::Node &root, void* params,
	void (*fun)(Yaml::Node&, void* params)) 
{
	for(auto i = root.Begin(); i != root.End(); i++)
		fun((*i).second, params);
}

inline u32 Shell(ccstr program, std::vector<char*> arguments)
{
	pid_t pid = fork();

	arguments.emplace(arguments.begin(), const_cast<char*>(program));
	arguments.emplace_back(static_cast<char*>(NULL));

	if(pid == 0)
	{
		i32 result = execvp(arguments[0], arguments.data());
		if(result == -1)
		{
			std::cout << ANSI::BG_Red << ANSI::FG_Black <<
				"execvp terminated abnormally with code " << result << ANSI::Reset << "\n";
			exit(0);
		}
	}
	int status;
	waitpid(pid, &status, 0);
	return WIFEXITED(status) ? WEXITSTATUS(status) : -WTERMSIG(status);
}
}
