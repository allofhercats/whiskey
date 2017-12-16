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

public:
	Pass(std::string name, std::initializer_list<std::string> dependencies = {});
	Pass(const Pass &) = delete;

	const std::string &getName() const;
	const std::vector<std::string> &getDependencies() const;

	void run(PassContext<AST> &ctx);
	void runPost(PassContext<AST> &ctx);
};
}

#endif
