#ifndef __WHISKEY_Printing_Printer_HPP
#define __WHISKEY_Printing_Printer_HPP

#include <whiskey/Printing/Precedence.hpp>

namespace whiskey {
class Node;

class Printer {
private:
  bool usePrecedence;
  unsigned int tabWidth;

protected:
  virtual void
  onPrint(std::ostream &os, const Node &ast, unsigned int indent) = 0;

public:
  static const unsigned int defaultTabWidth;

  void printNewline(std::ostream &os, unsigned int indent);

  Printer(bool usePrecedence = true, unsigned int tabWidth = defaultTabWidth);
  Printer(const Printer &) = delete;
  ~Printer();

  bool getUsePrecedence() const;
  void setUsePrecedence(bool value);

  unsigned int getTabWidth() const;
  void setTabWidth(unsigned int value);

  void print(std::ostream &os,
             const Node &node,
             unsigned int indent = 0,
             Precedence outer = Precedence::None);
};
} // namespace whiskey

#endif
