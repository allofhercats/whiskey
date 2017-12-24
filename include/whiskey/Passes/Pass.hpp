#ifndef __WHISKEY_Passes_Pass_HPP
#define __WHISKEY_Passes_Pass_HPP

#include <whiskey/Passes/Module.inc>

#include <whiskey/Passes/PassContext.hpp>

namespace whiskey {
class Pass {
private:
	std::string name;
	std::vector<std::string> dependencies;

protected:
	virtual void onAST(PassContext<AST> &ctx);
	virtual void onType(PassContext<Type> &ctx);
	virtual void onTypeAtomic(PassContext<TypeAtomic> &ctx);
	virtual void onTypeSymbol(PassContext<TypeSymbol> &ctx);
	virtual void onTypeUnary(PassContext<TypeUnary> &ctx);
	virtual void onTypeBinary(PassContext<TypeBinary> &ctx);
	virtual void onTypeFunction(PassContext<TypeFunction> &ctx);
	virtual void onExpr(PassContext<Expr> &ctx);
	virtual void onExprLiteralInt(PassContext<ExprLiteralInt> &ctx);
	virtual void onExprLiteralFloat(PassContext<ExprLiteralFloat> &ctx);
	virtual void onExprSymbol(PassContext<ExprSymbol> &ctx);
	virtual void onExprUnary(PassContext<ExprUnary> &ctx);
	virtual void onExprBinary(PassContext<ExprBinary> &ctx);
	virtual void onExprCall(PassContext<ExprCall> &ctx);
	virtual void onStmt(PassContext<Stmt> &ctx);
	virtual void onStmtEmpty(PassContext<StmtEmpty> &ctx);
	virtual void onStmtExpr(PassContext<StmtExpr> &ctx);
	virtual void onStmtIf(PassContext<StmtIf> &ctx);
	virtual void onStmtWhile(PassContext<StmtWhile> &ctx);
	virtual void onStmtFor(PassContext<StmtFor> &ctx);
	virtual void onStmtForEach(PassContext<StmtForEach> &ctx);
	virtual void onStmtBlock(PassContext<StmtBlock> &ctx);
	virtual void onDecl(PassContext<Decl> &ctx);
	virtual void onDeclVariable(PassContext<DeclVariable> &ctx);
	virtual void onDeclFunction(PassContext<DeclFunction> &ctx);
	virtual void onDeclClass(PassContext<DeclClass> &ctx);
	virtual void onDeclNamespace(PassContext<DeclNamespace> &ctx);
	virtual void onImport(PassContext<Import> &ctx);

	virtual void onASTPost(PassContext<AST> &ctx);
	virtual void onTypePost(PassContext<Type> &ctx);
	virtual void onTypeAtomicPost(PassContext<TypeAtomic> &ctx);
	virtual void onTypeSymbolPost(PassContext<TypeSymbol> &ctx);
	virtual void onTypeUnaryPost(PassContext<TypeUnary> &ctx);
	virtual void onTypeBinaryPost(PassContext<TypeBinary> &ctx);
	virtual void onTypeFunctionPost(PassContext<TypeFunction> &ctx);
	virtual void onExprPost(PassContext<Expr> &ctx);
	virtual void onExprLiteralIntPost(PassContext<ExprLiteralInt> &ctx);
	virtual void onExprLiteralFloatPost(PassContext<ExprLiteralFloat> &ctx);
	virtual void onExprSymbolPost(PassContext<ExprSymbol> &ctx);
	virtual void onExprUnaryPost(PassContext<ExprUnary> &ctx);
	virtual void onExprBinaryPost(PassContext<ExprBinary> &ctx);
	virtual void onExprCallPost(PassContext<ExprCall> &ctx);
	virtual void onStmtPost(PassContext<Stmt> &ctx);
	virtual void onStmtEmptyPost(PassContext<StmtEmpty> &ctx);
	virtual void onStmtExprPost(PassContext<StmtExpr> &ctx);
	virtual void onStmtIfPost(PassContext<StmtIf> &ctx);
	virtual void onStmtWhilePost(PassContext<StmtWhile> &ctx);
	virtual void onStmtForPost(PassContext<StmtFor> &ctx);
	virtual void onStmtForEachPost(PassContext<StmtForEach> &ctx);
	virtual void onStmtBlockPost(PassContext<StmtBlock> &ctx);
	virtual void onDeclPost(PassContext<Decl> &ctx);
	virtual void onDeclVariablePost(PassContext<DeclVariable> &ctx);
	virtual void onDeclFunctionPost(PassContext<DeclFunction> &ctx);
	virtual void onDeclClassPost(PassContext<DeclClass> &ctx);
	virtual void onDeclNamespacePost(PassContext<DeclNamespace> &ctx);
	virtual void onImportPost(PassContext<Import> &ctx);

public:
	Pass(std::string name, std::initializer_list<std::string> dependencies = {});
	Pass(const Pass &) = delete;
	virtual ~Pass();

	const std::string &getName() const;
	const std::vector<std::string> &getDependencies() const;

	void run(PassContext<AST> &ctx);
	void runPost(PassContext<AST> &ctx);
};
}

#endif
