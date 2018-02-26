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
	typedef std::function<Node(const std::vector<Node> &)> ActionList;
	typedef std::function<Node(Token, Node)> ActionUnaryRight;
	typedef std::function<Node(Node, Token)> ActionUnaryLeft;
	typedef std::function<Node(Node, Token, Node)> ActionBinary;

private:
	std::vector<std::unique_ptr<ParserRule>> rules;
	ParserRuleID start;

public:
	ParserGrammar();

	std::vector<std::unique_ptr<ParserRule>>::size_type getNRules() const;

	ParserRuleID addRule(std::unique_ptr<ParserRule> rule);
	ParserRule &getRule(ParserRuleID ruleID);
	const ParserRule &getRule(ParserRuleID ruleID) const;

	ParserRuleID getStartID() const;
	ParserRule &getStartRule();
	const ParserRule &getStartRule() const;
	void setStartID(ParserRuleID ruleID);

	ParserRuleID addEmpty(std::string name, ParserRuleEmpty::Action action);
	ParserRuleID addTerm(std::string name, TokenID tokenID, ParserRuleTerm::Action action);
	ParserRuleID addTerm(std::string name, TokenID tokenID, std::string tokenText, ParserRuleTerm::Action action);
	ParserRuleID addTerm(std::string name, TokenID tokenID, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action);
	ParserRuleID addTerm(std::string name, TokenID tokenID, std::string tokenText, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action);
	ParserRuleID addTerm(std::string name, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action);
	ParserRuleID addConcat(std::string name, std::initializer_list<ParserRuleID> children, ParserRuleConcat::Action action, int requiredAfter = 1);
	ParserRuleID addAny(std::string name, std::initializer_list<ParserRuleID> children);

	ParserRuleID addList(std::string name, ParserRuleID element, ParserRuleID left, ParserRuleID sep, ParserRuleID right, ActionList action);
	ParserRuleID addUnaryRight(std::string name, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionUnaryRight action);
	ParserRuleID addUnaryLeft(std::string name, ParserRuleID lhs, std::initializer_list<ParserRuleID> ops, ActionUnaryLeft action);
	ParserRuleID addBinary(std::string name, ParserRuleID lhs, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionBinary action);
};
}

#endif
