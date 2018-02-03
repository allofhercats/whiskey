#include <whiskey/Core/Types.hpp>

namespace whiskey {
int getCharWidth(char32_t value) {
	if ((value & 0xff) == value) {
		return 1;
	} else if ((value & 0xffff) == value) {
		return 2;
	} else {
		return 4;
	}
}
}
