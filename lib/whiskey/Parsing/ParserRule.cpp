#include <whiskey/Parsing/ParserRule.hpp>

#include <whiskey/Core/Verbose.hpp>
#include <whiskey/Parsing/ParserResult.hpp>
#include <whiskey/Parsing/ParserContext.hpp>

namespace whiskey {
ParserRule::ParserRule(std::string name, std::string expected) : name(name), expected(expected) {}

std::string &ParserRule::getName() {
	return name;
}

const std::string &ParserRule::getName() const {
	return name;
}

void ParserRule::setName(std::string value) {
	name = value;
}

std::string &ParserRule::getExpected() {
	return expected;
}

const std::string &ParserRule::getExpected() const {
	return expected;
}

void ParserRule::setExpected(std::string value) {
	expected = value;
}

ParserResult ParserRule::parse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const {
	W_VERBOSE("parsing " << name);

	ParserContext save = ctx;
	ParserResult res = onParse(grammar, ctx, msgs);
	if (!res.isGood()) {
		res.setNode(Node());
		ctx = save;

		W_VERBOSE("failed " << name);
	} else {
		W_VERBOSE("parsed " << name);
		W_VERBOSE("ast " << res.getNode());
	}

	return res;
}
}
