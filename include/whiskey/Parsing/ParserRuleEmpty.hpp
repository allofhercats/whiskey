#ifndef __WHISKEY_Parsing_ParserRuleEmpty_HPP
#define __WHISKEY_Parsing_ParserRuleEmpty_HPP

#include <functional>

#include <whiskey/Source/TokenID.hpp>
#include <whiskey/Parsing/ParserRule.hpp>

namespace whiskey {
class Node;
class Token;

class ParserRuleEmpty : public ParserRule {
public:
	typedef std::function<std::unique_ptr<Node>(MessageContext &)> Action;

private:
	Action action;

protected:
	ParserResult onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const final;

public:
	ParserRuleEmpty(std::string name, Action action);

	const Action &getAction() const;
	void setAction(Action value);
};
}

#endif
