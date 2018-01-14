#ifndef __WHISKEY_Unicode_Encoding_HPP
#define __WHISKEY_Unicode_Encoding_HPP

#include <whiskey/Unicode/Endianness.hpp>

namespace whiskey {
enum class Encoding {
	Auto,
	ASCII,
	UTF8,
	UTF16LE,
	UTF16BE,
	UTF32LE,
	UTF32BE
};

int getEncodingWidth(Encoding value);
Endianness getEncodingEndianness(Encoding value);
}

#endif
