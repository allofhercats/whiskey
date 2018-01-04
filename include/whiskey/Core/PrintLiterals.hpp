#ifndef __WHISKEY_Core_PrintLiterals_HPP
#define __WHISKEY_Core_PrintLiterals_HPP

#include <stdint.h>

#include <ostream>

namespace whiskey {
int getChar32MinWidth(char32_t value);
unsigned int getNDigits(uint64_t value, unsigned int base = 10);

void printLiteralBool(std::ostream &os, bool value);
void printLiteralInt(std::ostream &os,
                     int64_t value,
                     unsigned int base = 10,
                     bool prefix = true,
                     unsigned int width = 0);
void printLiteralUInt(std::ostream &os,
                      uint64_t value,
                      unsigned int base = 10,
                      bool prefix = true,
                      unsigned int width = 0);
void printLiteralReal(std::ostream &os,
                      long double value,
                      unsigned int precision = 5,
                      bool truncate = true);
void printLiteralChar(std::ostream &os, char32_t value);
void printLiteralCString8(std::ostream &os, const char *value, size_t length = 0);
void printLiteralCString16(std::ostream &os, const char16_t *value, size_t length = 0);
void printLiteralCString32(std::ostream &os, const char32_t *value, size_t length = 0);
void printLiteralString(std::ostream &os, const std::string &value);
void printLiteralString(std::ostream &os, const std::u16string &value);
void printLiteralString(std::ostream &os, const std::u32string &value);
} // namespace whiskey

#endif
