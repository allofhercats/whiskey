#include "Module.inc"

#include <whiskey/Passes/Pass.hpp>

namespace whiskey {
void Pass::onAST(PassContext<AST> &ctx) {}
void Pass::onType(PassContext<Type> &ctx) {}
void Pass::onTypeAtomic(PassContext<TypeAtomic> &ctx) {}
void Pass::onTypeSymbol(PassContext<TypeSymbol> &ctx) {}
void Pass::onTypeUnary(PassContext<TypeUnary> &ctx) {}
void Pass::onTypeBinary(PassContext<TypeBinary> &ctx) {}
void Pass::onTypeFunction(PassContext<TypeFunction> &ctx) {}
void Pass::onExpr(PassContext<Expr> &ctx) {}
void Pass::onExprLiteralInt(PassContext<ExprLiteralInt> &ctx) {}
void Pass::onExprLiteralFloat(PassContext<ExprLiteralFloat> &ctx) {}
void Pass::onExprSymbol(PassContext<ExprSymbol> &ctx) {}
void Pass::onExprUnary(PassContext<ExprUnary> &ctx) {}
void Pass::onExprBinary(PassContext<ExprBinary> &ctx) {}
void Pass::onExprCall(PassContext<ExprCall> &ctx) {}
void Pass::onStmt(PassContext<Stmt> &ctx) {}
void Pass::onStmtEmpty(PassContext<StmtEmpty> &ctx) {}
void Pass::onStmtExpr(PassContext<StmtExpr> &ctx) {}
void Pass::onStmtIf(PassContext<StmtIf> &ctx) {}
void Pass::onStmtWhile(PassContext<StmtWhile> &ctx) {}
void Pass::onStmtFor(PassContext<StmtFor> &ctx) {}
void Pass::onStmtForEach(PassContext<StmtForEach> &ctx) {}
void Pass::onStmtBlock(PassContext<StmtBlock> &ctx) {}
void Pass::onDecl(PassContext<Decl> &ctx) {}
void Pass::onDeclVariable(PassContext<DeclVariable> &ctx) {}
void Pass::onDeclFunction(PassContext<DeclFunction> &ctx) {}
void Pass::onDeclClass(PassContext<DeclClass> &ctx) {}
void Pass::onDeclNamespace(PassContext<DeclNamespace> &ctx) {}
void Pass::onImport(PassContext<Import> &ctx) {}

Pass::Pass(std::string name, std::initializer_list<std::string> dependencies) : name(name), dependencies(dependencies) {}

const std::string &Pass::getName() const {
	return name;
}

const std::vector<std::string> &Pass::getDependencies() const {
	return dependencies;
}

void Pass::run(PassContext<AST> &ctx) {
	onAST(ctx);
}
}
