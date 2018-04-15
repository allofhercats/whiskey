#ifndef __WHISKEY_Lexing_UnLexUtils_HPP
#define __WHISKEY_Lexing_UnLexUtils_HPP

#include <whiskey/Source/Token.hpp>

namespace whiskey {
std::string getSourceFromTokens(const std::vector<Token> &tokens);
// std::string stripUnneededFromSource(const std::string &text, bool stripComments = true);
}

#endif
