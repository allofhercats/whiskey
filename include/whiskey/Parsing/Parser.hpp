#ifndef __WHISKEY_Parsing_Parser_HPP
#define __WHISKEY_Parsing_Parser_HPP

#include <memory>

#include <whiskey/Parsing/ParserGrammar.hpp>

namespace whiskey {
class Node;

class Parser {
private:
	ParserRuleID ruleType;
	ParserRuleID ruleExpr;
	ParserRuleID ruleStmt;
	ParserRuleID ruleDecl;
	ParserGrammar grammar;

public:
	Parser();

	bool isGrammarInitted() const;
	void initGrammar();
	const ParserGrammar &getGrammar() const;
	ParserRuleID getGrammarRuleType() const;
	ParserRuleID getGrammarRuleExpr() const;
	ParserRuleID getGrammarRuleStmt() const;
	ParserRuleID getGrammarRuleDecl() const;

	Node parse(ParserContext &ctx, MessageContext &msgs) const;
};
} // namespace whiskey

#endif
