#ifndef __WHISKEY_Parsing_EvalLiterals_HPP
#define __WHISKEY_Parsing_EvalLiterals_HPP

#include <whiskey/Parsing/Module.inc>

namespace whiskey {
void appendChar32ToString(std::string &value, char32_t chr);

bool evalLiteralUInt64(Range range, uint64_t &value);
bool evalLiteralReal(Range range, long double &value);
bool evalLiteralChar(Range range, char32_t &value);
bool evalLiteralString(Range range, std::string &value);
}

#endif
