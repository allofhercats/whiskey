#ifndef __WHISKEY_AST2_Node_HPP
#define __WHISKEY_AST2_Node_HPP

#include <whiskey/AST2/Module.inc>

#include <whiskey/AST2/Field.hpp>

namespace whiskey {
class Node {
public:
	enum class Kind {
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
		ExprLiteralInt,
		ExprLiteralReal,
		ExprSymbol,
		ExprAccessUnary,
		ExprAccess,
		ExprGroup,
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

	static int getNFields(Kind kind);

	enum class FieldTag {
		TypeSymbol_Name = 0,
		TypeSymbol_TemplateEvalArgs = 1,
		TypeAccessUnary_Arg = 0,
		TypeAccess_Args = 0,
		TypeGroup_Arg = 0,
		TypeFunction_Return = 0,
		TypeFunction_Args = 1,
		ExprLiteralInt_Type = 0,
		ExprLiteralInt_Value = 1,
		ExprLiteralReal_Type = 0,
		ExprLiteralReal_Value = 1,
		ExprSymbol_Name = 0,
		ExprSymbol_TemplateEvalArgs = 1,
		ExprAccessUnary_Arg = 0,
		ExprAccess_Args = 0,
		ExprGroup_Arg = 0,
		ExprAdd_Args = 0,
		ExprIncPre_Arg = 0,
		ExprIncPost_Arg = 0,
		ExprSub_LHS = 0,
		ExprSub_RHS = 1,
		ExprNeg_Arg = 0,
		ExprDecPre_Arg = 0,
		ExprDecPost_Arg = 0,
		ExprMul_Args = 0,
		ExprExp_LHS = 0,
		ExprExp_RHS = 1,
		ExprDiv_LHS = 0,
		ExprDiv_RHS = 1,
		ExprDivInt_LHS = 0,
		ExprDivInt_RHS = 1,
		ExprDivReal_LHS = 0,
		ExprDivReal_RHS = 1,
		ExprMod_LHS = 0,
		ExprMod_RHS = 1,
		ExprBitNot_Arg = 0,
		ExprBitAnd_Args = 0,
		ExprBitOr_Args = 0,
		ExprBitXor_Args = 0,
		ExprBitShL_LHS = 0,
		ExprBitShL_RHS = 1,
		ExprBitShR_LHS = 0,
		ExprBitShR_RHS = 1,
		ExprBoolNot_Arg = 0,
		ExprBoolAnd_Args = 0,
		ExprBoolOr_Args = 0,
		ExprBoolImplies_Args = 0,
		ExprAddAssign_LHS = 0,
		ExprAddAssign_RHS = 1,
		ExprSubAssign_LHS = 0,
		ExprSubAssign_RHS = 1,
		ExprMulAssign_LHS = 0,
		ExprMulAssign_RHS = 1,
		ExprExpAssign_LHS = 0,
		ExprExpAssign_RHS = 1,
		ExprDivAssign_LHS = 0,
		ExprDivAssign_RHS = 1,
		ExprDivIntAssign_LHS = 0,
		ExprDivIntAssign_RHS = 1,
		ExprDivRealAssign_LHS = 0,
		ExprDivRealAssign_RHS = 1,
		ExprModAssign_LHS = 0,
		ExprModAssign_RHS = 1,
		ExprBitAndAssign_LHS = 0,
		ExprBitAndAssign_RHS = 1,
		ExprBitOrAssign_LHS = 0,
		ExprBitOrAssign_RHS = 1,
		ExprBitXorAssign_LHS = 0,
		ExprBitXorAssign_RHS = 1,
		ExprBitShLAssign_LHS = 0,
		ExprBitShLAssign_RHS = 1,
		ExprBitShRAssign_LHS = 0,
		ExprBitShRAssign_RHS = 1,
		ExprAssign_LHS = 0,
		ExprAssign_RHS = 1,
		StmtExpr_Expr = 0,
		StmtDecl_Decl = 0,
		StmtReturn_Arg = 0,
		StmtContinue_Name = 0,
		StmtBreak_Name = 0,
		StmtIf_Condition = 0,
		StmtIf_Then = 1,
		StmtIf_Else = 2,
		StmtWhile_Condition = 0,
		StmtWhile_Body = 1,
		StmtFor_Decls = 0,
		StmtFor_Condition = 1,
		StmtFor_Steps = 2,
		StmtFor_Body = 3,
		StmtForEach_Decls = 0,
		StmtForEach_Sequences = 1,
		StmtForEach_Body = 2,
		StmtBlock_Stmts = 0,
		DeclVariable_Type = 0,
		DeclVariable_Name = 1,
		DeclVariable_TemplateDeclArgs = 2,
		DeclVariable_Initial = 3,
		DeclFunction_Return = 0,
		DeclFunction_Name = 1,
		DeclFunction_TemplateDeclArgs = 2,
		DeclFunction_Args = 3,
		DeclFunction_Body = 4,
		DeclClass_Name = 0,
		DeclClass_TemplateDeclArgs = 1,
		DeclClass_Inherits = 2,
		DeclClass_Members = 3,
		DeclNamespace_Name = 0,
		DeclNamespace_Members = 1,
		Import_Path = 0,
		Unit_Members = 0
	};

private:
	Range range;
	Kind kind;
	Field **fields;
	Node *next;

	Node(Kind kind, std::initializer_list<Field *> fields, Range range);

public:
	Node(const Node &) = delete;
	~Node();

	static Node *createTypeAtomicBool(Range range = Range());
	static Node *createTypeAtomicInt8(Range range = Range());
	static Node *createTypeAtomicInt16(Range range = Range());
	static Node *createTypeAtomicInt32(Range range = Range());
	static Node *createTypeAtomicInt64(Range range = Range());
	static Node *createTypeAtomicUInt8(Range range = Range());
	static Node *createTypeAtomicUInt16(Range range = Range());
	static Node *createTypeAtomicUInt32(Range range = Range());
	static Node *createTypeAtomicUInt64(Range range = Range());
	static Node *createTypeAtomicFloat32(Range range = Range());
	static Node *createTypeAtomicFloat64(Range range = Range());
	static Node *createTypeAtomicReal(Range range = Range());
	static Node *createTypeSymbol(Field *name, Range range = Range());
	static Node *createTypeSymbol(Field *name, std::initializer_list<Node *> templateEvalArgs, Range range = Range());
	static Node *createTypeAccessUnary(Node *arg, Range range = Range());
	static Node *createTypeAccess(std::initializer_list<Node *> args, Range range = Range());
	static Node *createTypeGroup(Node *arg, Range range = Range());
	static Node *createTypeFunction(Node *ret, std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprLiteralInt(Node *type, Int value, Range range = Range());
	static Node *createExprLiteralReal(Node *type, Real value, Range range = Range());
	static Node *createExprSymbol(Field *name, Range range = Range());
	static Node *createExprSymbol(Field *name, std::initializer_list<Node *> templateEvalArgs, Range range = Range());
	static Node *createExprAccessUnary(Node *arg, Range range = Range());
	static Node *createExprAccess(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprGroup(Node *arg, Range range = Range());
	static Node *createExprAdd(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprIncPre(Node *arg, Range range = Range());
	static Node *createExprIncPost(Node *arg, Range range = Range());
	static Node *createExprSub(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprNeg(Node *arg, Range range = Range());
	static Node *createExprDecPre(Node *arg, Range range = Range());
	static Node *createExprDecPost(Node *arg, Range range = Range());
	static Node *createExprMul(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprExp(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprDiv(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprDivInt(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprDivReal(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprMod(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBitNot(Node *arg, Range range = Range());
	static Node *createExprBitAnd(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprBitOr(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprBitXor(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprBitShL(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBitShR(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBoolNot(Node *arg, Range range = Range());
	static Node *createExprBoolAnd(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprBoolOr(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprBoolImplies(std::initializer_list<Node *> args, Range range = Range());
	static Node *createExprAddAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprSubAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprMulAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprExpAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprDivAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprDivIntAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprDivRealAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprModAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBitAndAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBitOrAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBitXorAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBitShLAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprBitShRAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createExprAssign(Node *lhs, Node *rhs, Range range = Range());
	static Node *createStmtEmpty(Range range = Range());
	static Node *createStmtExpr(Node *expr, Range range = Range());
	static Node *createStmtDecl(Node *decl, Range range = Range());
	static Node *createStmtReturn(Node *arg, Range range = Range());
	static Node *createStmtContinue(Field *name, Range range = Range());
	static Node *createStmtBreak(Field *name, Range range = Range());
	static Node *createStmtIf(Node *condition, Node *then, Range range = Range());
	static Node *createStmtIf(Node *condition, Node *then, Node *_else, Range range = Range());
	static Node *createStmtWhile(Node *condition, Node *body, Range range = Range());
	static Node *createStmtFor(std::initializer_list<Node *> decls, Node *condition, std::initializer_list<Node *> steps, Node *body, Range range = Range());
	static Node *createStmtForEach(std::initializer_list<Node *> decls, std::initializer_list<Node *> sequences, Node *body, Range range = Range());
	static Node *createStmtBlock(std::initializer_list<Node *> stmts, Range range = Range());
	static Node *createDeclVariable(Node *type, Field *name, Range range = Range());
	static Node *createDeclVariable(Node *type, Field *name, Node *initial, Range range = Range());
	static Node *createDeclVariable(Node *type, Field *name, std::initializer_list<Node *> templateDeclArgs, Range range = Range());
	static Node *createDeclVariable(Node *type, Field *name, std::initializer_list<Node *> templateDeclArgs, Node *initial, Range range = Range());
	static Node *createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> args, Range range = Range());
	static Node *createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> templateDeclArgs, std::initializer_list<Node *> args, Range range = Range());
	static Node *createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> args, Node *body, Range range = Range());
	static Node *createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> templateDeclArgs, std::initializer_list<Node *> args, Node *body, Range range = Range());
	static Node *createDeclClass(Field *name, std::initializer_list<Node *> members, Range range = Range());
	static Node *createDeclClass(Field *name, std::initializer_list<Node *> inherits, std::initializer_list<Node *> members, Range range = Range());
	static Node *createDeclClass(Field *name, std::initializer_list<Node *> templateDeclArgs, std::initializer_list<Node *> inherits, std::initializer_list<Node *> members, Range range = Range());
	static Node *createDeclNamespace(Field *name, std::initializer_list<Node *> members, Range range = Range());
	static Node *createImport(Field *path, Range range = Range());
	static Node *createUnit(std::initializer_list<Node *> members);

	Node *clone() const;

	const Range &getRange() const;
	void setRange(Range value);

	Kind getKind() const;

	int getNFields() const;
	Field *getField(int index);
	const Field *getField(int index) const;
	void setField(int index, Field *value);

	Node *getNext();
	const Node *getNext() const;
	void setNext(Node *value);

	bool compare(const Node *other) const;
};
}

#endif
