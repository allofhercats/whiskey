#ifndef __WHISKEY_Lexing_Lexer_HPP
#define __WHISKEY_Lexing_Lexer_HPP

#include <whiskey/Lexing/Module.inc>

#include <whiskey/Lexing/LexerContext.hpp>

namespace whiskey {
class Lexer {
private:
	LexerContext ctx;

public:
	static bool isWhitespaceChar(char32_t value);
	static bool isSymbolCharFirst(char32_t value);
	static bool isSymbolChar(char32_t value);
	static bool isNumericCharFirst(char32_t value);
	static bool isNumericChar(char32_t value);

	Lexer(Location start, std::vector<Token> &tokens, MessageBuffer &msgs);

	void lex();
};
}

#endif
