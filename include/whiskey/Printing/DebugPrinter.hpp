#ifndef __WHISKEY_Printing_DebugPrinter_HPP
#define __WHISKEY_Printing_DebugPrinter_HPP

#include <whiskey/Printing/Module.inc>

#include <whiskey/Printing/Precedence.hpp>
#include <whiskey/Printing/Printer.hpp>

namespace whiskey {
class DebugPrinter : public Printer {
private:
	template<class T>
	void printHelper(std::ostream &os, const std::string &label, CRef<T> ast, unsigned int indent);

	template<class T>
	void printVectorHelper(std::ostream &os, const std::string &label, const std::vector<Container<T>> &ast, unsigned int indent);

protected:
	void onPrint(std::ostream &os, CRef<AST> ast, unsigned int indent);

public:
	DebugPrinter(unsigned int tabWidth = Printer::defaultTabWidth);
};
}

#include <whiskey/Printing/DebugPrinter.tpp>

#endif
