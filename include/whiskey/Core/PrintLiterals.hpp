#ifndef __WHISKEY_Core_PrintLiterals_HPP
#define __WHISKEY_Core_PrintLiterals_HPP

#include <whiskey/Core/Module.inc>

namespace whiskey {
int getChar32MinWidth(char32_t value);
unsigned int getNDigits(uint64_t value, unsigned int base = 10);

void printLiteralBool(std::ostream &os, bool value);
void printLiteralInt64(std::ostream &os, int64_t value, unsigned int base = 10, bool prefix = true, unsigned int width = 0);
void printLiteralUInt64(std::ostream &os, uint64_t value, unsigned int base = 10, bool prefix = true, unsigned int width = 0);
void printLiteralReal(std::ostream &os, long double value, unsigned int precision = 5, bool truncate = true);
void printLiteralChar(std::ostream &os, char32_t value);
void printLiteralString(std::ostream &os, const std::string &value);
}

#endif