#ifndef __WHISKEY_Parsing_Parser_HPP
#define __WHISKEY_Parsing_Parser_HPP

#include <whiskey/Parsing/Module.inc>

#include <whiskey/Parsing/ParserResult.hpp>
#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/EvalLiterals.hpp>

namespace whiskey {
class Parser {
private:
	ParserContext ctx;

	static ParserResult parseBoundList(ParserContext &ctx, Token::ID left, ParserContext::Rule rule, const std::string &expected, Token::ID right);
	static ParserResult parseBoundSeparatedList(ParserContext &ctx, Token::ID left, ParserContext::Rule rule, const std::string &expected, Token::ID sep, Token::ID right);
	static ParserResult parseTemplateList(ParserContext &ctx, ParserContext::Rule rule, const std::string &expected);
	static ParserResult parseSymbol(ParserContext &ctx, ParserContext::Rule templateArgRule, std::function<ParserResult(Range, Node *)> builder);
	static ParserResult parseUnaryRight(ParserContext &ctx, Token::ID op, ParserContext::Rule rhsRule, ParserContext::Rule baseRule, const std::string &expected, std::function<ParserResult(Range, Node *)> builder);
	static ParserResult parseUnaryLeft(ParserContext &ctx, Token::ID op, ParserContext::Rule rhsRule, ParserContext::Rule baseRule, const std::string &expected, std::function<ParserResult(Range, Node *)> builder);
	static ParserResult parseBinary(ParserContext &ctx, Token::ID op, ParserContext::Rule lhsRule, ParserContext::Rule rhsRule, ParserContext::Rule baseRule, const std::string &expected, std::function<ParserResult(Range, Node *, Node *)> builder);

public:
	static ParserResult parseTemplateEvalArg(ParserContext &ctx);

	static ParserResult parseTypeSymbol(ParserContext &ctx);
	static ParserResult parseTypeTerm(ParserContext &ctx);
	static ParserResult parseTypeAccessUnary(ParserContext &ctx);
	static ParserResult parseTypeAccessBinary(ParserContext &ctx);
	static ParserResult parseTypeFunction(ParserContext &ctx);
	static ParserResult parseTypeGroup(ParserContext &ctx);
	static ParserResult parseType(ParserContext &ctx);

	static ParserResult parseExprSymbol(ParserContext &ctx);
	static ParserResult parseExprLiteralInt(ParserContext &ctx);
	static ParserResult parseExprLiteralFloat(ParserContext &ctx);
	static ParserResult parseExprGroup(ParserContext &ctx);
	static ParserResult parseExprTerm(ParserContext &ctx);
	static ParserResult parseExprAccessUnary(ParserContext &ctx);
	static ParserResult parseExprAccessBinary(ParserContext &ctx);
	static ParserResult parseExprCall(ParserContext &ctx);
	static ParserResult parseExprUnaryRight(ParserContext &ctx);
	static ParserResult parseExprUnaryLeft(ParserContext &ctx);
	static ParserResult parseExprExp(ParserContext &ctx);
	static ParserResult parseExprMul(ParserContext &ctx);
	static ParserResult parseExprAdd(ParserContext &ctx);
	static ParserResult parseExprMod(ParserContext &ctx);
	static ParserResult parseExprBitShR(ParserContext &ctx);
	static ParserResult parseExprBitShL(ParserContext &ctx);
	static ParserResult parseExprBitAnd(ParserContext &ctx);
	static ParserResult parseExprBitOr(ParserContext &ctx);
	static ParserResult parseExprCompare(ParserContext &ctx);
	static ParserResult parseExprBoolNot(ParserContext &ctx);
	static ParserResult parseExprBoolAnd(ParserContext &ctx);
	static ParserResult parseExprBoolOr(ParserContext &ctx);
	static ParserResult parseExprBoolImplies(ParserContext &ctx);
	static ParserResult parseExprAssign(ParserContext &ctx);
	static ParserResult parseExpr(ParserContext &ctx);

	static ParserResult parseStmtEmpty(ParserContext &ctx);
	static ParserResult parseStmtExpr(ParserContext &ctx);
	static ParserResult parseStmtReturn(ParserContext &ctx);
	static ParserResult parseStmtIf(ParserContext &ctx);
	static ParserResult parseStmtWhile(ParserContext &ctx);
	static ParserResult parseStmtFor(ParserContext &ctx);
	static ParserResult parseStmtForEach(ParserContext &ctx);
	static ParserResult parseStmtBlock(ParserContext &ctx);
	static ParserResult parseStmt(ParserContext &ctx);
	
	static ParserResult parseDeclVariable(ParserContext &ctx);
	static ParserResult parseDeclFunction(ParserContext &ctx);
	static ParserResult parseDeclClass(ParserContext &ctx);
	static ParserResult parseDeclNamespace(ParserContext &ctx);
	static ParserResult parseDecl(ParserContext &ctx);

	static ParserResult parseImport(ParserContext &ctx);
	static ParserResult parseTopLevel(ParserContext &ctx);

	Parser(const std::vector<Token> &tokens, MessageBuffer &msgs, unsigned int offset = 0);

	Node *parse();
};
}

#endif
