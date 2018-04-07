#ifndef __WHISKEY_Parsing_ParserGrammar_HPP
#define __WHISKEY_Parsing_ParserGrammar_HPP

#include <memory>
#include <vector>

#include <whiskey/Parsing/ParserRule.hpp>
#include <whiskey/Parsing/ParserRuleAny.hpp>
#include <whiskey/Parsing/ParserRuleConcat.hpp>
#include <whiskey/Parsing/ParserRuleEmpty.hpp>
#include <whiskey/Parsing/ParserRuleTerm.hpp>

namespace whiskey {
class ParserGrammar {
public:
	typedef std::function<Node(const std::vector<Node> &, MessageContext &)> ActionList;
	typedef std::function<Node(Token, Node, MessageContext &)> ActionUnaryRight;
	typedef std::function<Node(Node, Token, MessageContext &)> ActionUnaryLeft;
	typedef std::function<Node(Node, Token, Node, MessageContext &)> ActionBinary;

private:
	std::vector<std::unique_ptr<ParserRule>> rules;
	ParserRuleID start;

public:
	ParserGrammar();

	std::vector<std::unique_ptr<ParserRule>>::size_type getNRules() const;

	ParserRuleID addForward();
	ParserRuleID addRule(std::unique_ptr<ParserRule> rule);
	ParserRuleID addRule(ParserRuleID forward, std::unique_ptr<ParserRule> rule);
	ParserRule &getRule(ParserRuleID ruleID);
	const ParserRule &getRule(ParserRuleID ruleID) const;

	ParserRuleID getStartID() const;
	ParserRule &getStartRule();
	const ParserRule &getStartRule() const;
	void setStartID(ParserRuleID ruleID);

	ParserRuleID addEmpty(std::string name, ParserRuleEmpty::Action action);
	ParserRuleID addEmpty(ParserRuleID forward, std::string name, ParserRuleEmpty::Action action);
	ParserRuleID addTerm(std::string name, std::string expected, TokenID tokenID, ParserRuleTerm::Action action);
	ParserRuleID addTerm(ParserRuleID forward, std::string name, std::string expected, TokenID tokenID, ParserRuleTerm::Action action);
	ParserRuleID addTerm(std::string name, std::string expected, TokenID tokenID, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action);
	ParserRuleID addTerm(ParserRuleID forward, std::string name, std::string expected, TokenID tokenID, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action);
	ParserRuleID addTerm(std::string name, std::string expected, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action);
	ParserRuleID addTerm(ParserRuleID forward, std::string name, std::string expected, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action);
	ParserRuleID addConcat(std::string name, std::string expected, std::initializer_list<ParserRuleID> children, ParserRuleConcat::Action action, int requiredAfter = 1);
	ParserRuleID addConcat(ParserRuleID forward, std::string name, std::string expected, std::initializer_list<ParserRuleID> children, ParserRuleConcat::Action action, int requiredAfter = 1);
	ParserRuleID addAny(std::string name, std::string expected, std::initializer_list<ParserRuleID> children);
	ParserRuleID addAny(ParserRuleID forward, std::string name, std::string expected, std::initializer_list<ParserRuleID> children);

	ParserRuleID addOptional(std::string name, std::string expected, ParserRuleID base, ParserRuleEmpty::Action action);
	ParserRuleID addOptional(ParserRuleID forward, std::string name, std::string expected, ParserRuleID base, ParserRuleEmpty::Action action);
	ParserRuleID addList(std::string name, std::string expected, ParserRuleID element, ActionList action);
	ParserRuleID addList(ParserRuleID forward, std::string name, std::string expected, ParserRuleID element, ActionList action);
	ParserRuleID addListSeparated(std::string name, std::string expected, ParserRuleID element, ParserRuleID sep, ActionList action);
	ParserRuleID addListSeparated(ParserRuleID forward, std::string name, std::string expected, ParserRuleID element, ParserRuleID sep, ActionList action);
	ParserRuleID addListBound(std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID right, ActionList action);
	ParserRuleID addListBound(ParserRuleID forward, std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID right, ActionList action);
	ParserRuleID addListBoundSeparated(std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID sep, ParserRuleID right, ActionList action);
	ParserRuleID addListBoundSeparated(ParserRuleID forward, std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID sep, ParserRuleID right, ActionList action);
	ParserRuleID addUnaryRight(std::string name, std::string expected, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionUnaryRight action);
	ParserRuleID addUnaryRight(ParserRuleID forward, std::string name, std::string expected, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionUnaryRight action);
	ParserRuleID addUnaryLeft(std::string name, std::string expected, ParserRuleID lhs, std::initializer_list<ParserRuleID> ops, ActionUnaryLeft action);
	ParserRuleID addUnaryLeft(ParserRuleID forward, std::string name, std::string expected, ParserRuleID lhs, std::initializer_list<ParserRuleID> ops, ActionUnaryLeft action);
	ParserRuleID addBinary(std::string name, std::string expected, ParserRuleID lhs, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionBinary action);
	ParserRuleID addBinary(ParserRuleID forward, std::string name, std::string expected, ParserRuleID lhs, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionBinary action);
};
}

#endif
