#include "Module.inc"

#include <whiskey/Printing/Printer.hpp>

namespace whiskey {
const unsigned int Printer::defaultTabWidth = 2;

void Printer::printNewline(std::ostream &os, unsigned int indent) {
	os << "\n";
	for (unsigned int i = 0; i < indent * tabWidth; i++) {
		os << ' ';
	}
}

Printer::Printer(unsigned int tabWidth) : tabWidth(tabWidth) {}

Printer::~Printer() {}

unsigned int Printer::getTabWidth() const {
	return tabWidth;
}

void Printer::setTabWidth(unsigned int value) {
	tabWidth = value;
}

void Printer::print(std::ostream &os, const Node *node, unsigned int indent, Precedence outer) {
	bool np = needsParenthesis(getPrecedence(node->getKind()), outer);
	if (np) {
		os << "(";
	}
	onPrint(os, node, indent);
	if (np) {
		os << ")";
	}
}
}
