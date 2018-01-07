#ifndef __WHISKEY_Core_LiteralPrinterBool_HPP
#define __WHISKEY_Core_LiteralPrinterBool_HPP

#include <whiskey/Core/Types.hpp>
#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
class LiteralPrinterBool : public LiteralPrinter {
private:
  bool value;

protected:
  virtual void onPrint(std::ostream &os) const;

public:
  LiteralPrinterBool(bool value);
  virtual ~LiteralPrinterBool();

  bool getValue() const;
  void setValue(bool value);
};
} // namespace whiskey

#endif
