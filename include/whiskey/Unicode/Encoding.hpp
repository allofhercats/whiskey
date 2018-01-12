#ifndef __WHISKEY_Unicode_Encoding_HPP
#define __WHISKEY_Unicode_Encoding_HPP

namespace whiskey {
enum class Encoding {
	Auto,
	UTF8,
	UTF16LE,
	UTF16BE,
	UTF32LE,
	UTF32BE
};
}

#endif
