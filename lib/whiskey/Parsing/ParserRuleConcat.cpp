#include <whiskey/Parsing/ParserRuleConcat.hpp>

#include <whiskey/Core/Verbose.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Parsing/ParserGrammar.hpp>
#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/ParserResult.hpp>

namespace whiskey {
ParserResult ParserRuleConcat::onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const {
	std::vector<Node> nodes;

	int n = 0;
	for (ParserRuleID id : children) {
		ParserResult res = grammar.getRule(id).parse(grammar, ctx, msgs);
		if (!res.isGood()) {
			if (requiredAfter > 0 && n >= requiredAfter) {
				W_VERBOSE("concat requirement failed after " << n << " >= " << requiredAfter << " for " << getName());
				msgs.describe() << "expected " << grammar.getRule(id).getName() << ", instead of ";
				printTokenID(msgs.describe(), ctx.get().getID());
				msgs.emit(ctx.get(), Message::Severity::Error);
				return ParserResult();
			} else {
				return ParserResult();
			}
		} else {
			nodes.push_back(res.getNode());
		}

		n++;
	}

	return action(nodes);
}

ParserRuleConcat::ParserRuleConcat(std::string name, std::initializer_list<ParserRuleID> children, Action action, int requiredAfter) : ParserRule(name), children(children), action(action), requiredAfter(requiredAfter) {}

std::vector<ParserRuleID> &ParserRuleConcat::getChildren() {
	return children;
}

const std::vector<ParserRuleID> &ParserRuleConcat::getChildren() const {
	return children;
}

const ParserRuleConcat::Action &ParserRuleConcat::getAction() const {
	return action;
}

void ParserRuleConcat::setAction(ParserRuleConcat::Action value) {
	action = value;
}

int ParserRuleConcat::getRequiredAfter() const {
	return requiredAfter;
}

void ParserRuleConcat::setRequiredAfter(int value) {
	requiredAfter = value;
}
}
