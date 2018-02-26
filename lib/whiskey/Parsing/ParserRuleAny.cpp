#include <whiskey/Parsing/ParserRuleAny.hpp>

#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Parsing/ParserGrammar.hpp>
#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/ParserResult.hpp>

namespace whiskey {
ParserResult ParserRuleAny::onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const {
	for (ParserRuleID id : children) {
		ParserResult res = grammar.getRule(id).parse(grammar, ctx, msgs);
		if (res.isGood()) {
			return res;
		}
	}

	return ParserResult();
}

ParserRuleAny::ParserRuleAny(std::string name, std::initializer_list<ParserRuleID> children) : ParserRule(name), children(children) {}

std::vector<ParserRuleID> &ParserRuleAny::getChildren() {
	return children;
}

const std::vector<ParserRuleID> &ParserRuleAny::getChildren() const {
	return children;
}
}
