#ifndef __WHISKEY_Parsing_ParserRuleConcat_HPP
#define __WHISKEY_Parsing_ParserRuleConcat_HPP

#include <functional>
#include <vector>

#include <whiskey/Source/TokenID.hpp>
#include <whiskey/Parsing/ParserRule.hpp>

namespace whiskey {
class Node;
class Token;

class ParserRuleConcat : public ParserRule {
public:
	typedef std::function<Node(const std::vector<Node> &, MessageContext &)> Action;

private:
	std::vector<ParserRuleID> children;
	Action action;
	int requiredAfter;

protected:
	ParserResult onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const final;

public:
	ParserRuleConcat(std::string name, std::initializer_list<ParserRuleID> children, Action action, int requiredAfter = 1);

	std::vector<ParserRuleID> &getChildren();
	const std::vector<ParserRuleID> &getChildren() const;

	const Action &getAction() const;
	void setAction(Action value);

	int getRequiredAfter() const;
	void setRequiredAfter(int value);
};
}

#endif
