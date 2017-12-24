#ifndef __WHISKEY_AST_AST_HPP
#define __WHISKEY_AST_AST_HPP

#include <whiskey/AST/Module.inc>

namespace whiskey {
class AST : public Cloneable<AST> {
public:
	enum class ID {
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
		TypeGroup,
		TypeAccessUnary,
		TypeAccessBinary,
		TypeFunction,
		ExprLiteralInt,
		ExprLiteralFloat,
		ExprSymbol,
		ExprCall,
		ExprAccessUnary,
		ExprAccessBinary,
		ExprIncPre,
		ExprIncPost,
		ExprDecPre,
		ExprDecPost,
		ExprNegate,
		ExprBitNot,
		ExprExp,
		ExprMul,
		ExprDiv,
		ExprDivInt,
		ExprDivReal,
		ExprAdd,
		ExprSub,
		ExprMod,
		ExprBitShR,
		ExprBitShL,
		ExprBitAnd,
		ExprBitOr,
		ExprBitXor,
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
		ExprExpAssign,
		ExprMulAssign,
		ExprDivAssign,
		ExprDivIntAssign,
		ExprDivRealAssign,
		ExprAddAssign,
		ExprSubAssign,
		ExprModAssign,
		ExprBitShRAssign,
		ExprBitShLAssign,
		ExprBitAndAssign,
		ExprBitOrAssign,
		ExprBitXorAssign,
		ExprAssign,
		ExprGroup,
		StmtEmpty,
		StmtExpr,
		StmtReturn,
		StmtIf,
		StmtWhile,
		StmtFor,
		StmtForEach,
		StmtBlock,
		DeclVariable,
		DeclFunction,
		DeclClass,
		DeclNamespace,
		Import
	};

	static bool isType(ID id);
	static bool isTypeAtomic(ID id);
	static bool isTypeSymbol(ID id);
	static bool isTypeUnary(ID id);
	static bool isTypeBinary(ID id);
	static bool isTypeFunction(ID id);
	static bool isExpr(ID id);
	static bool isExprLiteralInt(ID id);
	static bool isExprLiteralFloat(ID id);
	static bool isExprSymbol(ID id);
	static bool isExprUnary(ID id);
	static bool isExprBinary(ID id);
	static bool isExprCall(ID id);
	static bool isStmt(ID id);
	static bool isStmtEmpty(ID id);
	static bool isStmtExpr(ID id);
	static bool isStmtIf(ID id);
	static bool isStmtWhile(ID id);
	static bool isStmtFor(ID id);
	static bool isStmtForEach(ID id);
	static bool isStmtBlock(ID id);
	static bool isDecl(ID id);
	static bool isDeclVariable(ID id);
	static bool isDeclFunction(ID id);
	static bool isDeclClass(ID id);
	static bool isDeclNamespace(ID id);
	static bool isImport(ID id);

private:
	ID id;
	Range range;

protected:
	virtual bool onCompare(const AST &other) const = 0;
	virtual void onGetChildren(std::queue<ContainerRef<AST>> &children) = 0;

public:
	template<class ValueType>
	static bool compare(const Container<ValueType> &lhs, const Container<ValueType> &rhs);

	template<class ValueType>
	static bool compare(const Ref<ValueType> &lhs, const Ref<ValueType> &rhs);

	template<class ValueType>
	static bool compare(const CRef<ValueType> &lhs, const CRef<ValueType> &rhs);

	template<class ValueType>
	static bool compare(const std::vector<Container<ValueType>> &lhs, const std::vector<Container<ValueType>> &rhs);

	template<class ValueType>
	static bool compare(const std::vector<Ref<ValueType>> &lhs, const std::vector<Ref<ValueType>> &rhs);

	template<class ValueType>
	static bool compare(const std::vector<CRef<ValueType>> &lhs, const std::vector<CRef<ValueType>> &rhs);

	AST(ID id, Range range);

	template<class ValueType>
	Ref<ValueType> as();

	template<class ValueType>
	CRef<ValueType> as() const;
	
	ID getID() const;

	const Range &getRange() const;
	void setRange(Range value);

	bool compare(const AST &other) const;
	template<class ValueType>
	bool compare(const Ref<ValueType> &other) const;
	template<class ValueType>
	bool compare(const CRef<ValueType> &other) const;
	template<class ValueType>
	bool compare(const Container<ValueType> &other) const;

	std::queue<ContainerRef<AST>> getChildren();
};
}

#include <whiskey/AST/AST.tpp>

#endif

