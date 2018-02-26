#include <whiskey/Parsing/Parser.hpp>

#include <whiskey/AST/Node.hpp>
#include <whiskey/Parsing/ParserResult.hpp>
#include <whiskey/Parsing/ParserContext.hpp>

namespace whiskey {
ParserRuleID Parser::createGrammarType(ParserGrammar &grammar) {
	ParserRuleID atomicBool = grammar.addTerm(
		"'bool'",
		TokenID::Symbol,
		"bool",
		[](Token token) {
			return Node(NodeType::TypeAtomicBool, token);
		}
	);

	ParserRuleID atomicInt8 = grammar.addTerm(
		"'int8'",
		TokenID::Symbol,
		"int8",
		[](Token token) {
			return Node(NodeType::TypeAtomicInt8, token);
		}
	);

	ParserRuleID atomicInt16 = grammar.addTerm(
		"'int16'",
		TokenID::Symbol,
		"int16",
		[](Token token) {
			return Node(NodeType::TypeAtomicInt16, token);
		}
	);

	ParserRuleID atomicInt32 = grammar.addTerm(
		"'int32'",
		TokenID::Symbol,
		"int32",
		[](Token token) {
			return Node(NodeType::TypeAtomicInt32, token);
		}
	);

	ParserRuleID atomicInt64 = grammar.addTerm(
		"'int64'",
		TokenID::Symbol,
		"int64",
		[](Token token) {
			return Node(NodeType::TypeAtomicInt64, token);
		}
	);

	ParserRuleID atomicUInt8 = grammar.addTerm(
		"'uint8'",
		TokenID::Symbol,
		"uint8",
		[](Token token) {
			return Node(NodeType::TypeAtomicUInt8, token);
		}
	);

	ParserRuleID atomicUInt16 = grammar.addTerm(
		"'uint16'",
		TokenID::Symbol,
		"uint16",
		[](Token token) {
			return Node(NodeType::TypeAtomicUInt16, token);
		}
	);

	ParserRuleID atomicUInt32 = grammar.addTerm(
		"'uint32'",
		TokenID::Symbol,
		"uint32",
		[](Token token) {
			return Node(NodeType::TypeAtomicUInt32, token);
		}
	);

	ParserRuleID atomicUInt64 = grammar.addTerm(
		"'uint64'",
		TokenID::Symbol,
		"uint64",
		[](Token token) {
			return Node(NodeType::TypeAtomicUInt64, token);
		}
	);

	ParserRuleID atomicFloat32 = grammar.addTerm(
		"'float32'",
		TokenID::Symbol,
		"float32",
		[](Token token) {
			return Node(NodeType::TypeAtomicFloat32, token);
		}
	);

	ParserRuleID atomicFloat64 = grammar.addTerm(
		"'float64'",
		TokenID::Symbol,
		"float64",
		[](Token token) {
			return Node(NodeType::TypeAtomicFloat64, token);
		}
	);

	ParserRuleID atomicReal = grammar.addTerm(
		"'real'",
		TokenID::Symbol,
		"real",
		[](Token token) {
			return Node(NodeType::TypeAtomicReal, token);
		}
	);

	ParserRuleID symbolNoTemplateArgs = grammar.addTerm(
		"type",
		TokenID::Symbol,
		[](Token token) {
			return Node(NodeType::TypeSymbol, token);
		}
	)

	ParserRuleID term = grammar.addAny(
		"type",
		{
			atomicBool,
			atomicInt8,
			atomicInt16,
			atomicInt32,
			atomicInt64,
			atomicUInt8,
			atomicUInt16,
			atomicUInt32,
			atomicUInt64,
			atomicFloat32,
			atomicFloat64,
			atomicReal,
			symbol
		}
	);
}

ParserRuleID Parser::createGrammarExpr(ParserGrammar &grammar) {
	
}

ParserRuleID Parser::createGrammarStmt(ParserGrammar &grammar) {
	
}

ParserRuleID Parser::createGrammarDecl(ParserGrammar &grammar) {
	
}

void Parser::createGrammar(ParserGrammar &grammar) {

}

Parser::Parser() {}

bool Parser::isGrammarInitted() const {
	return grammar.getNRules() > 0;
}

void Parser::initGrammar() {
	grammar = ParserGrammar();
	createGrammar(grammar);
}

Node Parser::parse(ParserContext &ctx, MessageContext &msgs) const {
	Node rtn = grammar.getStartRule().parse(grammar, ctx, msgs).getNode();
	W_ASSERT_FALSE(ctx.more(), "Not all tokens parsed.");
	return rtn;
}
} // namespace whiskey
