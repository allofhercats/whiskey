#ifndef __WHISKEY_Core_LiteralPrinter_HPP
#define __WHISKEY_Core_LiteralPrinter_HPP

#include <whiskey/Core/Module.inc>

namespace whiskey {
class LiteralPrinter {
protected:
	virtual void onPrint(std::ostream &os) const = 0;

public:
	LiteralPrinter();
	virtual ~LiteralPrinter();

	void print(std::ostream &os) const;
};
}

#endif
