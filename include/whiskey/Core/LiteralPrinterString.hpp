#ifndef __WHISKEY_Core_LiteralPrinterString_HPP
#define __WHISKEY_Core_LiteralPrinterString_HPP

#include <whiskey/Unicode/StringRef.hpp>
#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
class LiteralPrinterString : public LiteralPrinter {
private:
  StringRef value;
  char quote;
  bool useQuotes;

protected:
  virtual void onPrint(CharOutStream &os) const;

public:
  LiteralPrinterString(StringRef value,
                    char quote = '\"',
                    bool useQuotes = true);
  virtual ~LiteralPrinterString();

  StringRef &getValue();
  const StringRef &getValue() const;
  void setValue(StringRef value);

  char getQuote() const;
  void setQuote(char value);

  bool getUseQuotes() const;
  void setUseQuotes(bool value);
};
} // namespace whiskey

#endif
