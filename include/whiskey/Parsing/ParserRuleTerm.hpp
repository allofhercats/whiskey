#ifndef __WHISKEY_Parsing_ParserRuleTerm_HPP
#define __WHISKEY_Parsing_ParserRuleTerm_HPP

#include <vector>
#include <functional>

#include <whiskey/Source/TokenID.hpp>
#include <whiskey/Parsing/ParserRule.hpp>

namespace whiskey {
class Node;
class Token;

class ParserRuleTerm : public ParserRule {
public:
	typedef std::function<std::unique_ptr<Node>(Token, MessageContext &)> Action;

private:
	TokenID tokenID;
	std::vector<std::pair<TokenID, TokenID>> tokenIDInjections;
	Action action;

protected:
	ParserResult onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const final;

public:
	ParserRuleTerm(std::string name, std::string expected, TokenID tokenID, Action action);
	ParserRuleTerm(std::string name, std::string expected, TokenID tokenID, std::vector<std::pair<TokenID, TokenID>> tokenIDInjections, Action action);
	ParserRuleTerm(std::string name, std::string expected, std::vector<std::pair<TokenID, TokenID>> tokenIDInjections, Action action);

	TokenID getTokenID() const;
	void setTokenID(TokenID value);

	std::vector<std::pair<TokenID, TokenID>> &getTokenIDInjections();
	const std::vector<std::pair<TokenID, TokenID>> &getTokenIDInjections() const;

	const Action &getAction() const;
	void setAction(Action value);
};
}

#endif
