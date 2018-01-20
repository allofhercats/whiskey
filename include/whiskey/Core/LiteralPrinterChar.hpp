#ifndef __WHISKEY_Core_LiteralPrinterChar_HPP
#define __WHISKEY_Core_LiteralPrinterChar_HPP

#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
class LiteralPrinterChar : public LiteralPrinter {
private:
  char value;
  char quote;
  bool useQuotes;

protected:
  virtual void onPrint(std::ostream &os) const;

public:
  LiteralPrinterChar(char value,
                    char quote = '\'',
                    bool useQuotes = true);
  virtual ~LiteralPrinterChar();

  char getValue() const;
  void setValue(char value);

  char getQuote() const;
  void setQuote(char value);

  bool getUseQuotes() const;
  void setUseQuotes(bool value);
};
} // namespace whiskey

#endif
