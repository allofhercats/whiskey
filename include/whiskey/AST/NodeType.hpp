#ifndef __WHISKEY_AST_NodeType_HPP
#define __WHISKEY_AST_NodeType_HPP

#include <ostream>
#include <vector>

#include <whiskey/AST/FieldTag.hpp>

namespace whiskey {
enum class NodeType {
  List,
  TypeVoid,
  TypeAtomicBool,
  TypeAtomicInt8,
  TypeAtomicInt16,
  TypeAtomicInt32,
  TypeAtomicInt64,
  TypeAtomicUInt8,
  TypeAtomicUInt16,
  TypeAtomicUInt32,
  TypeAtomicUInt64,
  TypeAtomicFloat32,
  TypeAtomicFloat64,
  TypeAtomicReal,
  TypeSymbol,
  TypeAccessUnary,
  TypeAccess,
  TypeGroup,
  TypeFunction,
  ExprLiteralBool,
  ExprLiteralInt8,
  ExprLiteralInt16,
  ExprLiteralInt32,
  ExprLiteralInt64,
  ExprLiteralUInt8,
  ExprLiteralUInt16,
  ExprLiteralUInt32,
  ExprLiteralUInt64,
  ExprLiteralChar8,
  ExprLiteralChar16,
  ExprLiteralChar32,
  ExprLiteralFloat32,
  ExprLiteralFloat64,
  ExprLiteralReal,
  ExprSymbol,
  ExprAccessUnary,
  ExprAccess,
  ExprGroup,
  ExprCall,
  ExprAdd,
  ExprIncPre,
  ExprIncPost,
  ExprSub,
  ExprNeg,
  ExprDecPre,
  ExprDecPost,
  ExprMul,
  ExprExp,
  ExprDiv,
  ExprDivInt,
  ExprDivReal,
  ExprMod,
  ExprBitNot,
  ExprBitAnd,
  ExprBitOr,
  ExprBitXor,
  ExprBitShL,
  ExprBitShR,
  ExprLT,
  ExprLE,
  ExprGT,
  ExprGE,
  ExprNE,
  ExprEQ,
  ExprBoolNot,
  ExprBoolAnd,
  ExprBoolOr,
  ExprBoolImplies,
  ExprAddAssign,
  ExprSubAssign,
  ExprMulAssign,
  ExprExpAssign,
  ExprDivAssign,
  ExprDivIntAssign,
  ExprDivRealAssign,
  ExprModAssign,
  ExprBitAndAssign,
  ExprBitOrAssign,
  ExprBitXorAssign,
  ExprBitShLAssign,
  ExprBitShRAssign,
  ExprAssign,
  StmtEmpty,
  StmtExpr,
  StmtDecl,
  StmtReturn,
  StmtContinue,
  StmtBreak,
  StmtIf,
  StmtWhile,
  StmtFor,
  StmtForEach,
  StmtBlock,
  DeclVariable,
  DeclFunction,
  DeclClass,
  DeclNamespace,
  Import,
  Unit
};

bool evalNodeType(const std::string &text, NodeType &value);
bool evalFieldTag(NodeType nodeType, const std::string &text, FieldTag &value);
std::ostream &operator<<(std::ostream &os, NodeType value);

enum class NodeTypeCategory {
  None,
  Internal,
	Type,
	Expr,
	Stmt,
	Decl,
	Import,
	Unit
};

std::ostream &operator<<(std::ostream &os, NodeTypeCategory value);

class NodeTypeInfo {
private:
	std::string name;
	NodeTypeCategory category;
	std::vector<FieldTag> fields;

public:
	static const NodeTypeInfo &get(NodeType type);

	NodeTypeInfo(std::string name, NodeTypeCategory category, std::initializer_list<FieldTag> fields);

	const std::string &getName() const;
	NodeTypeCategory getCategory() const;
	const std::vector<FieldTag> &getFields() const;
};
}

#endif
