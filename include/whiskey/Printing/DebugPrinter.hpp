#ifndef __WHISKEY_Printing_DebugPrinter_HPP
#define __WHISKEY_Printing_DebugPrinter_HPP

#include <whiskey/Printing/Module.inc>

#include <whiskey/Printing/Precedence.hpp>
#include <whiskey/Printing/Printer.hpp>

namespace whiskey {
class DebugPrinter : public Printer {
protected:
	void onPrint(std::ostream &os, const Node *node, unsigned int indent);

public:
	DebugPrinter(unsigned int tabWidth = Printer::defaultTabWidth);
};
}

#endif
