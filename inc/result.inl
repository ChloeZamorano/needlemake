#pragma once
#include "pch.hpp"

#include "terminal_colors.inl"

// TODO: Cripple the logging system on DEPLOY builds.

#define X(x) x,

#define ENTRIES				\
	X(ProjectFileMissing)	\
	X(ConfigFileMissing)	\
	X(UnknownGame)			\

enum class ErrorCode : u32
{
	Success = 0,
	ENTRIES
};

#undef X
#define X(x)				\
		case ErrorCode::x:	\
			return #x;		\

inline ccstr ErrorCodeName(const ErrorCode& v)
{
	switch(v)
	{
		case ErrorCode::Success:
			return "Success (Why are you printing this code???)";

		ENTRIES

		default:
			return "UNKNOWN";
	}
}

#undef ENTRIES
#undef X

struct Result
{
	ErrorCode Error;
	std::string Message;

	Result() :
		Error(ErrorCode::Success), Message("")
	{}
	
	Result(
		const ErrorCode &error,
		const std::string &message) :

		Error(error), Message(message)
	{}

	inline void Print()
	{
		std::cout << ANSI::Reset <<
			ANSI::BG_Red << ANSI::FG_Black <<
			"The program encountered the error" << ANSI::Reset << " " <<

			ANSI::FG_Red << ANSI::Underline <<
			ErrorCodeName(Error) << ANSI::Reset <<

			":\n" <<

			ANSI::Bold << ANSI::FG_BrightRed <<
			Message << ANSI::Reset <<

			"\n";
	}
};
