#ifndef __WHISKEY_Core_LiteralPrinterChar_HPP
#define __WHISKEY_Core_LiteralPrinterChar_HPP

#include <whiskey/Unicode/Char.hpp>
#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
class LiteralPrinterChar : public LiteralPrinter {
private:
  Char32 value;
  char quote;
  bool useQuotes;

protected:
  virtual void onPrint(CharOutStream &os) const;

public:
  LiteralPrinterChar(Char32 value,
                    char quote = '\'',
                    bool useQuotes = true);
  virtual ~LiteralPrinterChar();

  Char32 getValue() const;
  void setValue(Char32 value);

  char getQuote() const;
  void setQuote(char value);

  bool getUseQuotes() const;
  void setUseQuotes(bool value);
};
} // namespace whiskey

#endif
