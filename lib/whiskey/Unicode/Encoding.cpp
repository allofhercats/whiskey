#include <whiskey/Unicode/Encoding.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
int getEncodingWidth(Encoding value) {
	switch (value) {
		case Encoding::Auto:
			W_ASSERT_UNREACHABLE("Cannot get width of encoding Auto.");
		case Encoding::UTF8:
			return 1;
		case Encoding::UTF16LE:
			return 2;
		case Encoding::UTF16BE:
			return 2;
		case Encoding::UTF32LE:
			return 4;
		case Encoding::UTF32BE:
			return 4;
	}
}

Endianness getEncodingEndianness(Encoding value) {
	switch (value) {
		case Encoding::Auto:
			W_ASSERT_UNREACHABLE("Cannot get endianness of encoding Auto.");
		case Encoding::UTF8:
			W_ASSERT_UNREACHABLE("Cannot get endianness of encoding UTF8.");
		case Encoding::UTF16LE:
			return Endianness::Little;
		case Encoding::UTF16BE:
			return Endianness::Big;
		case Encoding::UTF32LE:
			return Endianness::Little;
		case Encoding::UTF32BE:
			return Endianness::Big;
	}
}
}
