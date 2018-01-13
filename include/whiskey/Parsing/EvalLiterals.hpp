#ifndef __WHISKEY_Parsing_EvalLiterals_HPP
#define __WHISKEY_Parsing_EvalLiterals_HPP

#include <whiskey/Unicode/Char.hpp>
#include <whiskey/Core/Types.hpp>

namespace whiskey {
class Range;

void appendChar16ToString8(std::string &value, char16_t chr);
void appendChar32ToString8(std::string &value, char32_t chr);
void appendChar32ToString16(std::u16string &value, char32_t chr);

bool evalLiteralUInt(const Range &range, UInt &value);
bool evalLiteralReal(const Range &range, Real &value);
bool evalLiteralChar(const Range &range, Char32 &value);
bool evalLiteralString8(const Range &range, std::string &value);
bool evalLiteralString16(const Range &range, std::u16string &value);
bool evalLiteralString32(const Range &range, std::u32string &value);
} // namespace whiskey

#endif
