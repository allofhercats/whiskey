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

ParserRuleID ParserGrammar::addForward() {
	ParserRuleID rtn = rules.size();
	rules.push_back(std::unique_ptr<ParserRule>());
	return rtn;
}

ParserRuleID ParserGrammar::addRule(std::unique_ptr<ParserRule> rule) {
	return addRule(addForward(), std::move(rule));
}

ParserRuleID ParserGrammar::addRule(ParserRuleID forward, std::unique_ptr<ParserRule> rule) {
	rules[forward] = std::move(rule);
	return forward;
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
	return addEmpty(addForward(), name, action);
}

ParserRuleID ParserGrammar::addEmpty(ParserRuleID forward, std::string name, ParserRuleEmpty::Action action) {
	return addRule(forward, std::make_unique<ParserRuleEmpty>(name, action));
}

ParserRuleID ParserGrammar::addTerm(std::string name, std::string expected, TokenID tokenID, ParserRuleTerm::Action action) {
	return addTerm(addForward(), name, expected, tokenID, action);
}

ParserRuleID ParserGrammar::addTerm(ParserRuleID forward, std::string name, std::string expected, TokenID tokenID, ParserRuleTerm::Action action) {
	return addRule(forward, std::make_unique<ParserRuleTerm>(name, expected, tokenID, action));
}

ParserRuleID ParserGrammar::addTerm(std::string name, std::string expected, TokenID tokenID, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action) {
	return addTerm(addForward(), name, expected, tokenID, tokenIDInjections, action);
}

ParserRuleID ParserGrammar::addTerm(ParserRuleID forward, std::string name, std::string expected, TokenID tokenID, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action) {
	return addRule(forward, std::make_unique<ParserRuleTerm>(name, expected, tokenID, tokenIDInjections, action));
}

ParserRuleID ParserGrammar::addTerm(std::string name, std::string expected, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action) {
	return addTerm(addForward(), name, expected, tokenIDInjections, action);
}

ParserRuleID ParserGrammar::addTerm(ParserRuleID forward, std::string name, std::string expected, std::initializer_list<std::pair<TokenID, TokenID>> tokenIDInjections, ParserRuleTerm::Action action) {
	return addRule(forward, std::make_unique<ParserRuleTerm>(name, expected, tokenIDInjections, action));
}

ParserRuleID ParserGrammar::addConcat(std::string name, std::string expected, std::initializer_list<ParserRuleID> children, ParserRuleConcat::Action action, int requiredAfter) {
	return addConcat(addForward(), name, expected, children, action, requiredAfter);
}

ParserRuleID ParserGrammar::addConcat(ParserRuleID forward, std::string name, std::string expected, std::initializer_list<ParserRuleID> children, ParserRuleConcat::Action action, int requiredAfter) {
	return addRule(forward, std::make_unique<ParserRuleConcat>(name, expected, children, action, requiredAfter));
}

ParserRuleID ParserGrammar::addAny(std::string name, std::string expected, std::initializer_list<ParserRuleID> children) {
	return addAny(addForward(), name, expected, children);
}

ParserRuleID ParserGrammar::addAny(ParserRuleID forward, std::string name, std::string expected, std::initializer_list<ParserRuleID> children) {
	return addRule(forward, std::make_unique<ParserRuleAny>(name, expected, children));
}

ParserRuleID ParserGrammar::addOptional(std::string name, std::string expected, ParserRuleID base, ParserRuleEmpty::Action action) {
	return addOptional(addForward(), name, expected, base, action);
}

ParserRuleID ParserGrammar::addOptional(ParserRuleID forward, std::string name, std::string expected, ParserRuleID base, ParserRuleEmpty::Action action) {
	ParserRuleID empty = addEmpty(
		"OptionalEmpty",
		action
	);

	addAny(
		forward,
		name,
		expected,
		{
			base,
			empty
		}
	);

	return forward;
}








ParserRuleID ParserGrammar::addListBound(std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID right, ActionList action) {
	return addListBound(addForward(), name, expected, element, left, right, action);
}

ParserRuleID ParserGrammar::addListBound(ParserRuleID forward, std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID right, ActionList action) {
	ParserRuleID argsNonEmptyRec = addConcat("ListArgsNonEmptyRec", "", {
		element
	}, [](const std::vector<Node> &nodes, MessageContext &ctx) {
		W_ASSERT_GE(nodes.size(), 3U, "Must have at least 3 nodes in concat.");

		Node list = nodes[1];
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
	
	ParserRuleID argsNonEmpty = addAny("ListArgsNonEmpty", "", {
		argsNonEmptyRec,
		element
	});

	static_cast<ParserRuleConcat &>(getRule(argsNonEmptyRec)).getChildren().push_back(argsNonEmpty);

	ParserRuleID empty = addEmpty("Empty", [](MessageContext &ctx) {
		return Node();
	});

	ParserRuleID args = addAny("ListArgs", "", {
		argsNonEmpty,
		empty
	});

	ParserRuleID list = addConcat(forward, name, expected, {
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









ParserRuleID ParserGrammar::addListBoundSeparated(std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID sep, ParserRuleID right, ActionList action) {
	return addListBoundSeparated(addForward(), name, expected, element, left, sep, right, action);
}

ParserRuleID ParserGrammar::addListBoundSeparated(ParserRuleID forward, std::string name, std::string expected, ParserRuleID element, ParserRuleID left, ParserRuleID sep, ParserRuleID right, ActionList action) {
	ParserRuleID argsNonEmptyRec = addConcat("ListArgsNonEmptyRec", "", {
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
	
	ParserRuleID argsNonEmpty = addAny("ListArgsNonEmpty", "", {
		argsNonEmptyRec,
		element
	});

	static_cast<ParserRuleConcat &>(getRule(argsNonEmptyRec)).getChildren().push_back(argsNonEmpty);

	ParserRuleID empty = addEmpty("Empty", [](MessageContext &ctx) {
		return Node();
	});

	ParserRuleID args = addAny("ListArgs", "", {
		argsNonEmpty,
		empty
	});

	ParserRuleID list = addConcat(forward, name, expected, {
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

ParserRuleID ParserGrammar::addUnaryRight(std::string name, std::string expected, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionUnaryRight action) {
	return addUnaryRight(addForward(), name, expected, rhs, ops, action);
}

ParserRuleID ParserGrammar::addUnaryRight(ParserRuleID forward, std::string name, std::string expected, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionUnaryRight action) {
	ParserRuleID unaryRight = addAny(forward, name, expected, {});

	for (ParserRuleID op : ops) {
		ParserRuleID opRule = addConcat("UnaryRightOp", "", {
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

ParserRuleID ParserGrammar::addUnaryLeft(std::string name, std::string expected, ParserRuleID lhs, std::initializer_list<ParserRuleID> ops, ActionUnaryLeft action) {
	return addUnaryLeft(addForward(), name, expected, lhs, ops, action);
}

ParserRuleID ParserGrammar::addUnaryLeft(ParserRuleID forward, std::string name, std::string expected, ParserRuleID lhs, std::initializer_list<ParserRuleID> ops, ActionUnaryLeft action) {
	ParserRuleID unaryLeftP = addAny("UnaryLeftOpRec", "", {});

	for (ParserRuleID op : ops) {
		ParserRuleID opRule = addConcat("UnaryLeftOp", "", {
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

	ParserRuleID empty = addEmpty("Empty", [](MessageContext &ctx) {
		return Node();
	});

	static_cast<ParserRuleAny &>(getRule(unaryLeftP)).getChildren().push_back(empty);

	ParserRuleID unaryLeft = addConcat(forward, name, expected, {
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

ParserRuleID ParserGrammar::addBinary(std::string name, std::string expected, ParserRuleID lhs, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionBinary action) {
	return addBinary(addForward(), name, expected, lhs, rhs, ops, action);
}

ParserRuleID ParserGrammar::addBinary(ParserRuleID forward, std::string name, std::string expected, ParserRuleID lhs, ParserRuleID rhs, std::initializer_list<ParserRuleID> ops, ActionBinary action) {
	ParserRuleID opsRule = addAny("BinaryOps", "", ops);
	
	ParserRuleID rhsRec = addAny(
		"RHSRec",
		"",
		{
			forward,
			rhs
		}
	);

	ParserRuleID binaryOpNonOptional = addConcat(
		"BinaryOpNonOptional",
		"",
		{
			opsRule,
			rhsRec
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[0]);
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[1]);
			return rtn;
		}
	);

	ParserRuleID binaryOpOptional = addEmpty(
		"BinaryOpOptional",
		[](MessageContext &msgs) {
			return Node();
		}
	);

	ParserRuleID binaryOp = addAny(
		"BinaryOp",
		"",
		{
			binaryOpNonOptional,
			binaryOpOptional
		}
	);

	addConcat(
		forward,
		name,
		expected,
		{
			lhs,
			binaryOp
		},
		[action](const std::vector<Node> &nodes, MessageContext &msgs) {
			if (nodes[1].getType() == NodeType::None) {
				return nodes[0];
			} else {
				return action(nodes[0], nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()[0].getToken(), nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()[1], msgs);
			}
		}
	);

	return forward;
}
}
