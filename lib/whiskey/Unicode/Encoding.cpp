#include <whiskey/Unicode/Encoding.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
int getEncodingWidth(Encoding value) {
	switch (value) {
		case Encoding::Auto:
			W_ASSERT_UNREACHABLE("Cannot get width of encoding Auto.");
		case Encoding::ASCII:
			return 1;
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
}
