#include <whiskey/Printing/Printer.hpp>

#include <whiskey/AST/Node.hpp>

namespace whiskey {
const unsigned int Printer::defaultTabWidth = 2;

void Printer::printNewline(std::ostream &os, unsigned int indent) {
  os << "\n";
  for (unsigned int i = 0; i < indent * tabWidth; i++) {
    os << ' ';
  }
}

Printer::Printer(bool usePrecedence, unsigned int tabWidth)
    : usePrecedence(usePrecedence), tabWidth(tabWidth) {
}

Printer::~Printer() {
}

bool Printer::getUsePrecedence() const {
  return usePrecedence;
}

void Printer::setUsePrecedence(bool value) {
  usePrecedence = value;
}

unsigned int Printer::getTabWidth() const {
  return tabWidth;
}

void Printer::setTabWidth(unsigned int value) {
  tabWidth = value;
}

void Printer::print(std::ostream &os,
                    const Node &node,
                    unsigned int indent,
                    Precedence outer) {
  bool np = false;
  if (usePrecedence) {
    np = needsParenthesis(getPrecedence(node.getType()), outer);
  }
  if (np) {
    os << "(";
  }
  onPrint(os, node, indent);
  if (np) {
    os << ")";
  }
}
} // namespace whiskey
