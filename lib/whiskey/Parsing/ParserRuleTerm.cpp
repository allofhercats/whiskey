#include <whiskey/Parsing/ParserRuleTerm.hpp>

#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/ParserResult.hpp>

namespace whiskey {
ParserResult ParserRuleTerm::onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const {
	if (tokenID != TokenID::None && ctx.get().getID() == tokenID) {
		return action(ctx.eat(), msgs);
	} else {
		for (const std::pair<TokenID, TokenID> &injection : tokenIDInjections) {
			if (ctx.get().getID() == injection.first) {
				Token token = ctx.eat();
				ctx.inject(injection.second);
				return action(token, msgs);
			}
		}
		return ParserResult();
	}
}

ParserRuleTerm::ParserRuleTerm(std::string name, std::string expected, TokenID tokenID, Action action) : ParserRule(name, expected), tokenID(tokenID), action(action) {}

ParserRuleTerm::ParserRuleTerm(std::string name, std::string expected, TokenID tokenID, std::vector<std::pair<TokenID, TokenID>> tokenIDInjections, Action action) : ParserRule(name, expected), tokenID(tokenID), tokenIDInjections(tokenIDInjections), action(action) {}

ParserRuleTerm::ParserRuleTerm(std::string name, std::string expected, std::vector<std::pair<TokenID, TokenID>> tokenIDInjections, Action action) : ParserRule(name, expected), tokenID(TokenID::None), tokenIDInjections(tokenIDInjections), action(action) {}

TokenID ParserRuleTerm::getTokenID() const {
	return tokenID;
}

void ParserRuleTerm::setTokenID(TokenID value) {
	tokenID = value;
}

std::vector<std::pair<TokenID, TokenID>> &ParserRuleTerm::getTokenIDInjections() {
	return tokenIDInjections;
}

const std::vector<std::pair<TokenID, TokenID>> &ParserRuleTerm::getTokenIDInjections() const {
	return tokenIDInjections;
}

const ParserRuleTerm::Action &ParserRuleTerm::getAction() const {
	return action;
}

void ParserRuleTerm::setAction(ParserRuleTerm::Action value) {
	action = value;
}
}
