#ifndef __WHISKEY_Parsing_EvalLiterals_HPP
#define __WHISKEY_Parsing_EvalLiterals_HPP

#include <whiskey/Core/Types.hpp>

namespace whiskey {
class Range;

bool evalLiteralUInt(const Range &range, UInt64 &value);
bool evalLiteralReal(const Range &range, Real &value);
bool evalLiteralChar(const Range &range, char &value);
bool evalLiteralString(const Range &range, std::string &value);
} // namespace whiskey

#endif
