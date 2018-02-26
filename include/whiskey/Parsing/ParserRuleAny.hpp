#ifndef __WHISKEY_Parsing_ParserRuleAny_HPP
#define __WHISKEY_Parsing_ParserRuleAny_HPP

#include <vector>

#include <whiskey/Source/TokenID.hpp>
#include <whiskey/Parsing/ParserRule.hpp>

namespace whiskey {
class Node;
class Token;

class ParserRuleAny : public ParserRule {
private:
	std::vector<ParserRuleID> children;

protected:
	ParserResult onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const final;

public:
	ParserRuleAny(std::string name, std::initializer_list<ParserRuleID> children = {});

	std::vector<ParserRuleID> &getChildren();
	const std::vector<ParserRuleID> &getChildren() const;
};
}

#endif
