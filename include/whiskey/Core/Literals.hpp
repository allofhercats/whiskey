#ifndef __WHISKEY_Core_Literals_HPP
#define __WHISKEY_Core_Literals_HPP

#include <ostream>
#include <string>

#include <whiskey/Core/Types.hpp>

#define W_LITERAL_INT_DEFAULT_BASE 10
#define W_LITERAL_INT_NO_WIDTH 0
#define W_LITERAL_REAL_DEFAULT_PRECISION 5
#define W_LITERAL_REAL_DEFAULT_TRUNCATE true

namespace whiskey {
void printLiteralBool(std::ostream &os, bool value);
void printLiteralUInt(std::ostream &os, uint64_t value, int base = W_LITERAL_INT_DEFAULT_BASE, int width = W_LITERAL_INT_NO_WIDTH, bool usePrefix = true);
void printLiteralInt(std::ostream &os, int64_t value, int base = W_LITERAL_INT_DEFAULT_BASE, int width = W_LITERAL_INT_NO_WIDTH, bool usePrefix = true);
void printLiteralReal(std::ostream &os, long double value, int precision = W_LITERAL_REAL_DEFAULT_PRECISION, bool truncate = W_LITERAL_REAL_DEFAULT_TRUNCATE);
void printLiteralChar(std::ostream &os, char32_t value, char quote = '\'', bool useQuotes = true);
void printLiteralString(std::ostream &os, const std::string &value, char quote = '\"', bool useQuotes = true);

bool evalLiteralBool(const std::string &text, bool &value);
bool evalLiteralUInt(const std::string &text, uint64_t &value);
bool evalLiteralReal(const std::string &text, long double &value);
bool evalLiteralChar(const std::string &text, char32_t &value);
bool evalLiteralString(const std::string &text, std::string &value);
}

#endif
