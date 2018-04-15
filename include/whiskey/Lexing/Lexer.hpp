#ifndef __WHISKEY_Lexing_Lexer_HPP
#define __WHISKEY_Lexing_Lexer_HPP

#include <whiskey/Core/Types.hpp>

#define W_LEXER_SAVE_LAST 2

namespace whiskey {
class LexerContext;
class MessageContext;

class Lexer {
private:
	enum State {
		Start,
		Comment,
		CommentLine,
		CommentBlock,
		Symbol,
		SymbolPrimes,
		Int,
		Real,
		Char,
		String,
		Period,
		Add,
		Sub,
		Mul,
		Exp,
		Div,
		DivInt,
		DivReal,
		Mod,
		BitAnd,
		BitOr,
		BitXor,
		LT,
		BitShL,
		GT,
		BitShR,
		Assign,
		NE
	};

	static const char *getStateName(State state);

	State state;
	Char8 chr;
	Char8 last[W_LEXER_SAVE_LAST];
	bool handled;
	bool running;
	int commentBlockLevel;

	void emitSymbol(LexerContext &ctx);
	void lexOne(LexerContext &ctx, MessageContext &msg);

public:
	Lexer();
	Lexer(const Lexer &) = delete;

	void lex(LexerContext &ctx, MessageContext &msg);
};
}

#endif
