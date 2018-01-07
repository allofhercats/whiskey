#ifndef __WHISKEY_Core_LiteralPrinterInt_HPP
#define __WHISKEY_Core_LiteralPrinterInt_HPP

#include <whiskey/Core/Types.hpp>
#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
class LiteralPrinterInt : public LiteralPrinter {
private:
  UInt value;
  unsigned int base;
  bool usePrefix;
  unsigned int width;

protected:
  virtual void onPrint(std::ostream &os) const;

public:
  static bool isValidBase(unsigned int base);
  static void printBasePrefix(std::ostream &os, unsigned int base);

  LiteralPrinterInt(UInt value,
                    unsigned int base = 10,
                    bool usePrefix = true,
                    unsigned int width = 0);
  virtual ~LiteralPrinterInt();

  UInt getValue() const;
  void setValue(UInt value);

  unsigned int getBase() const;
  void setBase(unsigned int value);

  bool getUsePrefix() const;
  void setUsePrefix(bool value);

  unsigned int getWidth() const;
  void setWidth(unsigned int value);
};
} // namespace whiskey

#endif
