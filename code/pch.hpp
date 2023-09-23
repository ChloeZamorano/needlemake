#pragma GCC diagnostic push "-Wno-error"
	//
	// STL Headers
	//
	#include <cstdint>

	#include <unordered_map>
	#include <vector>

	#include <string>
	#include <cstring>

	#include <memory>

	#include <iostream>

	#include <filesystem>

	#include <ctime>

	#include <unistd.h>
	#include <sys/wait.h>
	#include <cstdarg>

	//
	// Libraries
	//
	#include <Yaml.hpp>
	#include <ini.h>
#pragma GCC diagnostic pop

//
// Typedefs
//
typedef int8_t		i8;
typedef int16_t		i16;
typedef int32_t		i32;
typedef int64_t		i64;

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

typedef float		f32;
typedef double		f64;

typedef const char*	ccstr;
typedef char* 		cstr;

// TODO: Organize all this stuff

//
// Macros Constants
//
#undef __FILENAME__
#if defined(WINDOWS)
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

//
// Macro Functions
//
#define NDL_ADLER32(data, length)			\
({											\
	u32 adlerA = 1;							\
	u32 adlerB = 0;							\
	const unsigned char* ptr =				\
		reinterpret_cast<const u8*>(		\
		const_cast<const u8*>(data));		\
	const u8* end = ptr + length;			\
											\
	while (ptr < end)						\
	{										\
		adlerA = (adlerA + *ptr++) % 65521;	\
		adlerB = (adlerB + adlerA) % 65521;	\
	}										\
											\
	(adlerB << 16) | adlerA;				\
})                                          \

#define NDL_SWAP_8(x) (x)
#define NDL_SWAP_16(x) ((x << 8) | (x >> 8))
#define NDL_SWAP_32(x) (((x & 0xFF) << 24) | ((x & 0xFF00) << 8) |	((x & 0xFF0000) >> 8) | ((x >> 24) & 0xFF))
#define NDL_SWAP_64(x) (((x & 0xFFULL) << 56) | ((x & 0xFF00ULL) << 40) | ((x & 0xFF0000ULL) << 24) | ((x & 0xFF000000ULL) << 8) | ((x & 0xFF00000000ULL) >> 8) | ((x & 0xFF0000000000ULL) >> 24) | ((x & 0xFF000000000000ULL) >> 40) | ((x >> 56) & 0xFFULL))

#define NDL_STRINGIFY(x) #x

#define NDL_PRINT_HEX(buffer, width, color)														\
{																								\
	auto buf = reinterpret_cast<const u8*>(buffer);												\
																								\
	std::cout << std::setfill('0') << std::hex <<												\
	"                 |                     Hexadecimal                    |      ASCII      \n"\
	"          Offset | 00 01 02 03  04 05 06 07  08 09 0A 0B  0C 0D 0E 0F | 0123456789ABCDEF\n"\
	"-----------------|----------------------------------------------------|-----------------";	\
																								\
	for(u64 i = 0; i < width;)																	\
	{																							\
		std::cout <<																			\
			"\n" << std::setw(16) << i << " | ";												\
																								\
		u64 l = i;																				\
		for(u64 j = 0; j < 16; ++j)																\
		{																						\
			if(l < width)																		\
			{																					\
				std::cout << std::setw(2) << (u16)buf[l++] << " ";								\
				if((j + 1) % 4 == 0 && j < 15) std::cout << " ";								\
			}																					\
			else																				\
			{																					\
				std::cout << "   ";																\
				if((j + 1) % 4 == 0 && j < 15) std::cout << " ";								\
			}																					\
		}																						\
		std::cout << "| ";																		\
		l = i;																					\
		for(u64 j = 0; j < 16 && l < width; ++j)												\
		{																						\
			if(std::isprint(buf[l]))															\
				std::cout << buf[l];															\
			else																				\
			{																					\
				if(buf[l] == 0)																	\
				{																				\
					if(color)																	\
						std::cout << "\033[1;31m";												\
					std::cout << ".";															\
					if(color)																	\
						std::cout << "\033[1;0m";												\
				}																				\
				else																			\
				{																				\
					if(color)																	\
						std::cout << "\033[1;35m";												\
					std::cout << ".";															\
					if(color)																	\
						std::cout << "\033[1;0m";												\
				}																				\
			}																					\
			++l;																				\
		}																						\
		i = l;																					\
	}																							\
	std::cout << "\n";																			\
}																								\

//
// Architetural info and utility
//
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	#define NDL_ENDIAN_FLAG 'B'

	#undef NDL_BIG_ENDIAN
	#define NDL_LITTLE_ENDIAN

	#define NDL_CWAP_8 (x) (x)
	#define NDL_CWAP_16(x) (x)
	#define NDL_CWAP_32(x) (x)
	#define NDL_CWAP_64(x) (x)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	#define NDL_ENDIAN_FLAG 'L'

	#define NDL_BIG_ENDIAN
	#undef NDL_LITTLE_ENDIAN

	#define NDL_CWAP_8(x) (x)
	#define NDL_CWAP_16(x) NDL_SWAP_16(x)
	#define NDL_CWAP_32(x) NDL_SWAP_32(x)
	#define NDL_CWAP_64(x) NDL_SWAP_64(x)
#else
	#error Unsupported endianness. Please contact the developer at chloecake.com/cont.
#endif
