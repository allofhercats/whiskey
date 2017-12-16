#include "Module.inc"

#include <whiskey/Parsing/ParserContext.hpp>

namespace whiskey {
ParserContext::ParserContext(const std::vector<Token> &tokens, MessageBuffer &msgs, unsigned int offset) : tokens(&tokens), offset(0), msgs(&msgs) {}

bool ParserContext::areMoreTokens() const {
	return !injected.empty() || offset < tokens->size();
}

Token ParserContext::getToken() const {
	if (injected.empty()) {
		if (offset < tokens->size()) {
			return (*tokens)[offset];
		} else {
			return Token();
		}
	} else {
		return injected.top();
	}
}

Token ParserContext::eatToken() {
	if (injected.empty()) {
		if (offset < tokens->size()) {
			return (*tokens)[offset++];
		} else {
			return Token();
		}
	} else {
		Token rtn = injected.top();
		injected.pop();
		return rtn;
	}
}

void ParserContext::injectToken(Token token) {
	injected.push(token);
}

MessageBuffer &ParserContext::getMsgs() const {
	return *msgs;
}

void ParserContext::emitMessageUnexpectedToken(const std::string &expected) const {
	msgs->describe() << "expected " << expected << ", not ";
	Token::printTokenID(msgs->describe(), getToken().getID());
	msgs->emit(getToken().getRange(), Message::UnexpectedToken);
}

Token ParserContext::tryToken(Token::ID id) {
	Token rtn = getToken();
	if (rtn.getID() != id) {
		return Token();
	} else {
		eatToken();
		return rtn;
	}
}

Token ParserContext::expectToken(Token::ID id, const std::string &expected) {
	Token rtn = getToken();
	if (rtn.getID() != id) {
		emitMessageUnexpectedToken(expected);
		return Token();
	} else {
		eatToken();
		return rtn;
	}
}

ParserResult ParserContext::tryParse(ParserContext::Rule rule) {
	ParserContext save = *this;
	ParserResult res = rule(save);
	if (res.isGood()) {
		*this = save;
	} else {
		res.setAST(nullptr);
	}
	return res;
}

ParserResult ParserContext::expectParse(Rule rule, const std::string &expected) {
	ParserContext save = *this;
	ParserResult res = rule(save);
	if (res.isGood()) {
		*this = save;
		return res;
	} else {
		emitMessageUnexpectedToken(expected);
		return ParserResult();
	}
}

ParserResult ParserContext::tryParseAny(std::initializer_list<ParserContext::Rule> rules) {
	ParserResult res;
	for (const Rule &rule : rules) {
		res = tryParse(rule);
		if (res.isGood()) {
			return res;
		}
	}

	return ParserResult();
}

ParserResult ParserContext::expectParseAny(std::initializer_list<ParserContext::Rule> rules, const std::string &expected) {
	ParserResult res;
	for (const Rule &rule : rules) {
		res = tryParse(rule);
		if (res.isGood()) {
			return res;
		}
	}

	emitMessageUnexpectedToken(expected);
	return ParserResult();
}
}
