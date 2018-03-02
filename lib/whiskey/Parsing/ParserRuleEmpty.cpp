#include <whiskey/Parsing/ParserRuleEmpty.hpp>

#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/ParserResult.hpp>

namespace whiskey {
ParserResult ParserRuleEmpty::onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const {
	return action(msgs);
}

ParserRuleEmpty::ParserRuleEmpty(std::string name, Action action) : ParserRule(name), action(action) {}

const ParserRuleEmpty::Action &ParserRuleEmpty::getAction() const {
	return action;
}

void ParserRuleEmpty::setAction(ParserRuleEmpty::Action value) {
	action = value;
}
}
