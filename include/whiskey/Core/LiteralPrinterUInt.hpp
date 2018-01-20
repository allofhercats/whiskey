#ifndef __WHISKEY_Core_LiteralPrinterUInt_HPP
#define __WHISKEY_Core_LiteralPrinterUInt_HPP

#include <whiskey/Core/Types.hpp>
#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
class LiteralPrinterUInt : public LiteralPrinter {
private:
  UInt64 value;
  int base;
  bool usePrefix;
  int width;

protected:
  virtual void onPrint(std::ostream &os) const;

public:
  static bool isValidBase(int base);
  static void printBasePrefix(std::ostream &os, int base);

  LiteralPrinterUInt(UInt64 value,
                    int base = 10,
                    bool usePrefix = true,
                    int width = 0);
  virtual ~LiteralPrinterUInt();

  UInt64 getValue() const;
  void setValue(UInt64 value);

  int getBase() const;
  void setBase(int value);

  bool getUsePrefix() const;
  void setUsePrefix(bool value);

  int getWidth() const;
  void setWidth(int value);
};
} // namespace whiskey

#endif
