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
void printLiteralUInt(std::ostream &os, UInt64 value, UInt64 base = W_LITERAL_INT_DEFAULT_BASE, unsigned int width = W_LITERAL_INT_NO_WIDTH, bool usePrefix = true);
void printLiteralInt(std::ostream &os, Int64 value, Int64 base = W_LITERAL_INT_DEFAULT_BASE, unsigned int width = W_LITERAL_INT_NO_WIDTH, bool usePrefix = true);
void printLiteralReal(std::ostream &os, Real value, unsigned int precision = W_LITERAL_REAL_DEFAULT_PRECISION, bool truncate = W_LITERAL_REAL_DEFAULT_TRUNCATE);
void printLiteralChar(std::ostream &os, Char32 value, char quote = '\'', bool useQuotes = true);
void printLiteralString(std::ostream &os, const std::string &value, char quote = '\"', bool useQuotes = true);

bool evalLiteralBool(const std::string &text, bool &value);
bool evalLiteralUInt(const std::string &text, UInt64 &value);
bool evalLiteralInt(const std::string &text, Int64 &value);
bool evalLiteralReal(const std::string &text, Real &value);
bool evalLiteralChar(const std::string &text, Char32 &value);
bool evalLiteralString(const std::string &text, std::string &value);
}

#endif
