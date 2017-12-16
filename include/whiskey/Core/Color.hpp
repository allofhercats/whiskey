#ifndef __WHISKEY_Core_Color_HPP
#define __WHISKEY_Core_Color_HPP

#include <whiskey/Core/Module.inc>

namespace whiskey {
class Color {
private:
	const char *text;

public:
	static bool enabled;

	Color(const char *text);

	static const Color reset;
	static const Color red;
	static const Color green;
	static const Color yellow;
	static const Color blue;
	static const Color magenta;
	static const Color cyan;
	static const Color greyLight;
	static const Color greyDark;
	static const Color redLight;
	static const Color greenLight;
	static const Color yellowLight;
	static const Color blueLight;
	static const Color magentaLight;
	static const Color cyanLight;
	static const Color white;

	void print(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, const Color &value);
}

#endif
