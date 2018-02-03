#ifndef __WHISKEY_Parsing_EvalLiterals_HPP
#define __WHISKEY_Parsing_EvalLiterals_HPP

#include <whiskey/Core/Types.hpp>

namespace whiskey {
bool evalLiteralUInt(const std::string &text, UInt64 &value);
bool evalLiteralReal(const std::string &text, Real &value);
bool evalLiteralChar(const std::string &text, char &value);
bool evalLiteralString(const std::string &text, std::string &value);
} // namespace whiskey

#endif
