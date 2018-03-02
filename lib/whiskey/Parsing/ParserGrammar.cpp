#include <whiskey/Parsing/ParserGrammar.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>

namespace whiskey {
ParserGrammar::ParserGrammar() : start(0) {}

std::vector<std::unique_ptr<ParserRule>>::size_type ParserGrammar::getNRules() const {
	return rules.size();
}

ParserRuleID ParserGrammar::addRule(std::unique_ptr<ParserRule> rule) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::move(rule));
	return rtn;
}

ParserRule &ParserGrammar::getRule(ParserRuleID ruleID) {
	return *rules[ruleID];
}

const ParserRule &ParserGrammar::getRule(ParserRuleID ruleID) const {
	return *rules[ruleID];
}

ParserRuleID ParserGrammar::getStartID() const {
	return start;
}

ParserRule &ParserGrammar::getStartRule() {
	return getRule(start);
}

const ParserRule &ParserGrammar::getStartRule() const {
	return getRule(start);
}

void ParserGrammar::setStartID(ParserRuleID ruleID) {
	start = ruleID;
}

ParserRuleID ParserGrammar::addEmpty(std::string name, ParserRuleEmpty::Action action) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleEmpty>(name, action));
	return rtn;
}

ParserRuleID ParserGrammar::addTerm(std::string name, TokenID tokenID, ParserRuleTerm::Action action) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleTerm>(name, tokenID, action));
	return rtn;
}

ParserRuleID ParserGrammar::addTerm(std::string name, TokenID tokenID, std::string tokenText, ParserRuleTerm::Action action) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleTerm>(name, tokenID, tokenText, action));
	return rtn;
}

ParserRuleID ParserGrammar::addTerm(std::string name, TokenID tokenID, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleTerm>(name, tokenID, tokenIDInjections, action));
	return rtn;
}

ParserRuleID ParserGrammar::addTerm(std::string name, TokenID tokenID, std::string tokenText, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleTerm>(name, tokenID, tokenText, tokenIDInjections, action));
	return rtn;
}

ParserRuleID ParserGrammar::addTerm(std::string name, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleTerm>(name, tokenIDInjections, action));
	return rtn;
}

ParserRuleID ParserGrammar::addConcat(std::string name, std::initializer_list<ParserRuleID> children, ParserRuleConcat::Action action, int requiredAfter) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleConcat>(name, children, action, requiredAfter));
	return rtn;
}

ParserRuleID ParserGrammar::addAny(std::string name, std::initializer_list<ParserRuleID> children) {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::make_unique<ParserRuleAny>(name, children));
	return rtn;
}

ParserRuleID ParserGrammar::addList(std::string name, ParserRuleID element, ParserRuleID left, ParserRuleID sep, ParserRuleID right, ActionList action) {
	ParserRuleID argsNonEmptyRec = addConcat(name, {
		element,
		sep
	}, [](const std::vector<Node> &nodes, MessageContext &ctx) {
		W_ASSERT_GE(nodes.size(), 3U, "Must have at least 3 nodes in concat.");

		Node list = nodes[2];
		if (list.getType() != NodeType::List) {
			Node tmp = Node(NodeType::List);
			tmp.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			tmp.getField(FieldTag::List_Children).template as<FieldNodeVector>().getValue().push_back(list);
			list = tmp;
		}

		list.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
			list.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().begin(),
			nodes[0]
		);

		return list;
	},
	0);
	
	ParserRuleID argsNonEmpty = addAny(name, {
		argsNonEmptyRec,
		element
	});

	static_cast<ParserRuleConcat &>(getRule(argsNonEmptyRec)).getChildren().push_back(argsNonEmpty);

	ParserRuleID empty = addEmpty(name, [](MessageContext &ctx) {
		return Node();
	});

	ParserRuleID args = addAny(name, {
		argsNonEmpty,
		empty
	});

	ParserRuleID list = addConcat(name, {
		left,
		args,
		right
	}, [action](const std::vector<Node> &nodes, MessageContext &ctx) {
		W_ASSERT_GE(nodes.size(), 3U, "Must have at least 3 nodes in concat.");
		if (nodes[1].getType() == NodeType::None) {
			std::vector<Node> tmp;
			return action(tmp, ctx);
		} else if (nodes[1].getType() == NodeType::List) {
			return action(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>().getValue(), ctx);
		} else {
			std::vector<Node> tmp;
			tmp.push_back(nodes[1]);
			return action(tmp, ctx);
		}
	});

	return list;
}

ParserRuleID ParserGrammar::addUnaryRight(std::string name, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionUnaryRight action) {
	ParserRuleID unaryRight = addAny(name, {});

	for (ParserRuleID op : ops) {
		ParserRuleID opRule = addConcat(name, {
			op,
			unaryRight
		}, [action](const std::vector<Node> &nodes, MessageContext &ctx) {
			return action(nodes[0].getToken(), nodes[1], ctx);
		});

		static_cast<ParserRuleAny &>(getRule(unaryRight)).getChildren().push_back(opRule);
	}

	static_cast<ParserRuleAny &>(getRule(unaryRight)).getChildren().push_back(rhs);

	return unaryRight;
}

ParserRuleID ParserGrammar::addUnaryLeft(std::string name, ParserRuleID lhs, std::initializer_list<ParserRuleID> ops, ActionUnaryLeft action) {
	ParserRuleID unaryLeftP = addAny(name, {});

	for (ParserRuleID op : ops) {
		ParserRuleID opRule = addConcat(name, {
			op,
			unaryLeftP
		}, [](const std::vector<Node> &nodes, MessageContext &ctx) {
			if (nodes[1].getType() == NodeType::None) {
				Node tmp(nodes[0].getToken());
				Node rtn(NodeType::List);
				rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(tmp);
				return rtn;
			} else if (nodes[1].getType() == NodeType::List) {
				Node rtn = nodes[1];
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().begin(),
					Node(nodes[0].getToken())
				);
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected node type.");
			}
		});

		static_cast<ParserRuleAny &>(getRule(unaryLeftP)).getChildren().push_back(opRule);
	}

	ParserRuleID empty = addEmpty(name, [](MessageContext &ctx) {
		return Node();
	});

	static_cast<ParserRuleAny &>(getRule(unaryLeftP)).getChildren().push_back(empty);

	ParserRuleID unaryLeft = addConcat(name, {
		lhs,
		unaryLeftP
	}, [action](const std::vector<Node> &nodes, MessageContext &ctx) {
		Node rtn = nodes[0];
		if (nodes[1].getType() == NodeType::List) {
			for (const Node &i : nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()) {
				rtn = action(rtn, i.getToken(), ctx);
			}
		}
		return rtn;
	});

	return unaryLeft;
}

ParserRuleID ParserGrammar::addBinary(std::string name, ParserRuleID lhs, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionBinary action) {
	// binary : lhs op0 binary
	//        | lhs op1 binary
	//        ...
	//        | rhs

	ParserRuleID binary = addAny(name, {});

	for (ParserRuleID op : ops) {
		ParserRuleID opRule = addConcat("hi", {
			lhs,
			op,
			binary
		}, [action](const std::vector<Node> &nodes, MessageContext &ctx) {
			return action(nodes[0], nodes[1].getToken(), nodes[2], ctx);
		}, 2);
		
		static_cast<ParserRuleAny &>(getRule(binary)).getChildren().push_back(opRule);
	}

	static_cast<ParserRuleAny &>(getRule(binary)).getChildren().push_back(rhs);

	return binary;
}
}
