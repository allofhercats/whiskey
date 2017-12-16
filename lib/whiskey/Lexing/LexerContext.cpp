#include "Module.inc"

#include <whiskey/Lexing/LexerContext.hpp>

namespace whiskey {
LexerContext::LexerContext(Location start, std::vector<Token> &tokens, MessageBuffer &msgs) : first(start), last(start), tokens(&tokens), msgs(&msgs) {}

const Location &LexerContext::getFirst() const {
	return first;
}

const Location &LexerContext::getLast() const {
	return last;
}

Range LexerContext::getRange() const {
	return Range(first, last);
}

bool LexerContext::areMoreChars(size_t lookahead) const {
	return last.areMoreChars(lookahead);
}

char32_t LexerContext::getChar(size_t lookahead) const {
	return last.getChar(lookahead);
}

char32_t LexerContext::eatChar() {
	return last.eatChar();
}

bool LexerContext::hasText() const {
	return first.getOffset() != last.getOffset();
}

bool LexerContext::hasText(const std::string &value) const {
	if (last.getOffset() - first.getOffset() != value.size()) {
		return false;
	}

	Location si = first;
	std::string::const_iterator ti = value.begin();
	while (si.getOffset() != last.getOffset()) {
		if (si.getChar() != *ti) {
			return false;
		}

		si.eatChar();
		++ti;
	}

	return true;
}

void LexerContext::emitToken(Token::ID id) {
	Token token = Token(Range(first, last), id);
	tokens->push_back(token);
	skipToken();
}

void LexerContext::skipToken() {
	first = last;
}

MessageBuffer &LexerContext::getMsgs() {
	return *msgs;
}
}
