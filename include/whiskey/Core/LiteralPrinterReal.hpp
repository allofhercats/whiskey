#ifndef __WHISKEY_Core_LiteralPrinterReal_HPP
#define __WHISKEY_Core_LiteralPrinterReal_HPP

#include <whiskey/Core/LiteralPrinter.hpp>
#include <whiskey/Core/Types.hpp>

namespace whiskey {
class LiteralPrinterReal : public LiteralPrinter {
private:
  Real value;
  unsigned int precision;
  bool truncate;

protected:
  virtual void onPrint(std::ostream &os) const;

public:
  LiteralPrinterReal(Real value,
                     unsigned int precision = 5,
                     bool truncate = true);
  virtual ~LiteralPrinterReal();

  Real getValue() const;
  void setValue(Real value);

  unsigned int getPrecision() const;
  void setPrecision(unsigned int value);

  bool getTruncate() const;
  void setTruncate(bool value);
};
} // namespace whiskey

#endif
