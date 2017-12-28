#ifndef __WHISKEY_Parsing_EvalLiterals_HPP
#define __WHISKEY_Parsing_EvalLiterals_HPP

#include <whiskey/Parsing/Module.inc>

namespace whiskey {
void appendChar16ToString8(std::string &value, char16_t chr);
void appendChar32ToString8(std::string &value, char32_t chr);
void appendChar32ToString16(std::u16string &value, char32_t chr);

bool evalLiteralUInt(Range range, UInt &value);
bool evalLiteralReal(Range range, Real &value);
bool evalLiteralChar(Range range, Char32 &value);
bool evalLiteralString8(Range range, std::string &value);
bool evalLiteralString16(Range range, std::u16string &value);
bool evalLiteralString32(Range range, std::u32string &value);
} // namespace whiskey

#endif
