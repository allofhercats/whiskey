#ifndef __WHISKEY_Core_LiteralPrinter_HPP
#define __WHISKEY_Core_LiteralPrinter_HPP

#include <whiskey/Unicode/CharOutStream.hpp>

namespace whiskey {
class LiteralPrinter {
protected:
  virtual void onPrint(CharOutStream &os) const = 0;

public:
  LiteralPrinter();
  virtual ~LiteralPrinter();

  void print(CharOutStream &os) const;
};
} // namespace whiskey

#endif
