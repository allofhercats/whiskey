#ifndef __WHISKEY_Core_LiteralPrinterString_HPP
#define __WHISKEY_Core_LiteralPrinterString_HPP

#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
class LiteralPrinterString : public LiteralPrinter {
private:
  std::string value;
  char quote;
  bool useQuotes;

protected:
  virtual void onPrint(std::ostream &os) const;

public:
  LiteralPrinterString(std::string value,
                       char quote = '\"',
                       bool useQuotes = true);
  virtual ~LiteralPrinterString();

  std::string &getValue();
  const std::string &getValue() const;
  void setValue(std::string value);

  char getQuote() const;
  void setQuote(char value);

  bool getUseQuotes() const;
  void setUseQuotes(bool value);
};
} // namespace whiskey

#endif
