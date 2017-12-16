#ifndef __WHISKEY_Parsing_ParserContext_HPP
#define __WHISKEY_Parsing_ParserContext_HPP

#include <whiskey/Parsing/Module.inc>

#include <whiskey/Parsing/ParserResult.hpp>

namespace whiskey {
class ParserContext {
public:
	typedef std::function<ParserResult(ParserContext &)> Rule;

private:
	const std::vector<Token> *tokens;
	std::stack<Token> injected;
	unsigned int offset;
	MessageBuffer *msgs;

public:
	ParserContext(const std::vector<Token> &tokens, MessageBuffer &msgs, unsigned int offset = 0);

	bool areMoreTokens() const;
	Token getToken() const;
	Token eatToken();

	void injectToken(Token token);

	MessageBuffer &getMsgs() const;

	void emitMessageUnexpectedToken(const std::string &expected) const;

	Token tryToken(Token::ID id);
	Token expectToken(Token::ID id, const std::string &expected);

	ParserResult tryParse(Rule rule);
	ParserResult expectParse(Rule rule, const std::string &expected);

	ParserResult tryParseAny(std::initializer_list<Rule> rules);
	ParserResult expectParseAny(std::initializer_list<Rule> rules, const std::string &expected);
};
}

#endif
