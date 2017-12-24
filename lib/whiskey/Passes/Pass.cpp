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

void Pass::onASTPost(PassContext<AST> &ctx) {}
void Pass::onTypePost(PassContext<Type> &ctx) {}
void Pass::onTypeAtomicPost(PassContext<TypeAtomic> &ctx) {}
void Pass::onTypeSymbolPost(PassContext<TypeSymbol> &ctx) {}
void Pass::onTypeUnaryPost(PassContext<TypeUnary> &ctx) {}
void Pass::onTypeBinaryPost(PassContext<TypeBinary> &ctx) {}
void Pass::onTypeFunctionPost(PassContext<TypeFunction> &ctx) {}
void Pass::onExprPost(PassContext<Expr> &ctx) {}
void Pass::onExprLiteralIntPost(PassContext<ExprLiteralInt> &ctx) {}
void Pass::onExprLiteralFloatPost(PassContext<ExprLiteralFloat> &ctx) {}
void Pass::onExprSymbolPost(PassContext<ExprSymbol> &ctx) {}
void Pass::onExprUnaryPost(PassContext<ExprUnary> &ctx) {}
void Pass::onExprBinaryPost(PassContext<ExprBinary> &ctx) {}
void Pass::onExprCallPost(PassContext<ExprCall> &ctx) {}
void Pass::onStmtPost(PassContext<Stmt> &ctx) {}
void Pass::onStmtEmptyPost(PassContext<StmtEmpty> &ctx) {}
void Pass::onStmtExprPost(PassContext<StmtExpr> &ctx) {}
void Pass::onStmtIfPost(PassContext<StmtIf> &ctx) {}
void Pass::onStmtWhilePost(PassContext<StmtWhile> &ctx) {}
void Pass::onStmtForPost(PassContext<StmtFor> &ctx) {}
void Pass::onStmtForEachPost(PassContext<StmtForEach> &ctx) {}
void Pass::onStmtBlockPost(PassContext<StmtBlock> &ctx) {}
void Pass::onDeclPost(PassContext<Decl> &ctx) {}
void Pass::onDeclVariablePost(PassContext<DeclVariable> &ctx) {}
void Pass::onDeclFunctionPost(PassContext<DeclFunction> &ctx) {}
void Pass::onDeclClassPost(PassContext<DeclClass> &ctx) {}
void Pass::onDeclNamespacePost(PassContext<DeclNamespace> &ctx) {}
void Pass::onImportPost(PassContext<Import> &ctx) {}

Pass::Pass(std::string name, std::initializer_list<std::string> dependencies) : name(name), dependencies(dependencies) {
	W_ASSERT_GT(name.size(), 0, "Cannot have pass with empty name.");
}

Pass::~Pass() {}

const std::string &Pass::getName() const {
	return name;
}

const std::vector<std::string> &Pass::getDependencies() const {
	return dependencies;
}

void Pass::run(PassContext<AST> &ctx) {
	onAST(ctx);

	AST::ID id = ctx.getOriginal()->getID();

	if (AST::isType(id)) {
		PassContext<Type> ctxType = ctx.branch<Type>();

		onType(ctxType);

		if (AST::isTypeAtomic(id)) {
			PassContext<TypeAtomic> ctxTypeAtomic = ctxType.branch<TypeAtomic>();

			onTypeAtomic(ctxTypeAtomic);

			ctxType.merge<TypeAtomic>(ctxTypeAtomic);
		} else if (AST::isTypeSymbol(id)) {
			PassContext<TypeSymbol> ctxTypeSymbol = ctxType.branch<TypeSymbol>();

			onTypeSymbol(ctxTypeSymbol);

			ctxType.merge<TypeSymbol>(ctxTypeSymbol);
		} else if (AST::isTypeUnary(id)) {
			PassContext<TypeUnary> ctxTypeUnary = ctxType.branch<TypeUnary>();

			onTypeUnary(ctxTypeUnary);

			ctxType.merge<TypeUnary>(ctxTypeUnary);
		} else if (AST::isTypeBinary(id)) {
			PassContext<TypeBinary> ctxTypeBinary = ctxType.branch<TypeBinary>();

			onTypeBinary(ctxTypeBinary);

			ctxType.merge<TypeBinary>(ctxTypeBinary);
		} else if (AST::isTypeFunction(id)) {
			PassContext<TypeFunction> ctxTypeFunction = ctxType.branch<TypeFunction>();

			onTypeFunction(ctxTypeFunction);

			ctxType.merge<TypeFunction>(ctxTypeFunction);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Type>(ctxType);
	} else if (AST::isExpr(id)) {
		PassContext<Expr> ctxExpr = ctx.branch<Expr>();

		onExpr(ctxExpr);

		if (AST::isExprLiteralInt(id)) {
			PassContext<ExprLiteralInt> ctxExprLiteralInt = ctxExpr.branch<ExprLiteralInt>();

			onExprLiteralInt(ctxExprLiteralInt);

			ctxExpr.merge<ExprLiteralInt>(ctxExprLiteralInt);
		} else if (AST::isExprLiteralFloat(id)) {
			PassContext<ExprLiteralFloat> ctxExprLiteralFloat = ctxExpr.branch<ExprLiteralFloat>();

			onExprLiteralFloat(ctxExprLiteralFloat);

			ctxExpr.merge<ExprLiteralFloat>(ctxExprLiteralFloat);
		} else if (AST::isExprSymbol(id)) {
			PassContext<ExprSymbol> ctxExprSymbol = ctxExpr.branch<ExprSymbol>();

			onExprSymbol(ctxExprSymbol);

			ctxExpr.merge<ExprSymbol>(ctxExprSymbol);
		} else if (AST::isExprUnary(id)) {
			PassContext<ExprUnary> ctxExprUnary = ctxExpr.branch<ExprUnary>();

			onExprUnary(ctxExprUnary);

			ctxExpr.merge<ExprUnary>(ctxExprUnary);
		} else if (AST::isExprBinary(id)) {
			PassContext<ExprBinary> ctxExprBinary = ctxExpr.branch<ExprBinary>();

			onExprBinary(ctxExprBinary);

			ctxExpr.merge<ExprBinary>(ctxExprBinary);
		} else if (AST::isExprCall(id)) {
			PassContext<ExprCall> ctxExprCall = ctxExpr.branch<ExprCall>();

			onExprCall(ctxExprCall);

			ctxExpr.merge<ExprCall>(ctxExprCall);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Expr>(ctxExpr);
	} else if (AST::isStmt(id)) {
		PassContext<Stmt> ctxStmt = ctx.branch<Stmt>();

		onStmt(ctxStmt);

		if (AST::isStmtEmpty(id)) {
			PassContext<StmtEmpty> ctxStmtEmpty = ctxStmt.branch<StmtEmpty>();

			onStmtEmpty(ctxStmtEmpty);

			ctxStmt.merge<StmtEmpty>(ctxStmtEmpty);
		} else if (AST::isStmtExpr(id)) {
			PassContext<StmtExpr> ctxStmtExpr = ctxStmt.branch<StmtExpr>();

			onStmtExpr(ctxStmtExpr);

			ctxStmt.merge<StmtExpr>(ctxStmtExpr);
		} else if (AST::isStmtIf(id)) {
			PassContext<StmtIf> ctxStmtIf = ctxStmt.branch<StmtIf>();

			onStmtIf(ctxStmtIf);

			ctxStmt.merge<StmtIf>(ctxStmtIf);
		} else if (AST::isStmtWhile(id)) {
			PassContext<StmtWhile> ctxStmtWhile = ctxStmt.branch<StmtWhile>();

			onStmtWhile(ctxStmtWhile);

			ctxStmt.merge<StmtWhile>(ctxStmtWhile);
		} else if (AST::isStmtFor(id)) {
			PassContext<StmtFor> ctxStmtFor = ctxStmt.branch<StmtFor>();

			onStmtFor(ctxStmtFor);

			ctxStmt.merge<StmtFor>(ctxStmtFor);
		} else if (AST::isStmtForEach(id)) {
			PassContext<StmtForEach> ctxStmtForEach = ctxStmt.branch<StmtForEach>();

			onStmtForEach(ctxStmtForEach);

			ctxStmt.merge<StmtForEach>(ctxStmtForEach);
		} else if (AST::isStmtBlock(id)) {
			PassContext<StmtBlock> ctxStmtBlock = ctxStmt.branch<StmtBlock>();

			onStmtBlock(ctxStmtBlock);

			ctxStmt.merge<StmtBlock>(ctxStmtBlock);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Stmt>(ctxStmt);
	} else if (AST::isDecl(id)) {
		PassContext<Decl> ctxDecl = ctx.branch<Decl>();

		onDecl(ctxDecl);

		if (AST::isDeclVariable(id)) {
			PassContext<DeclVariable> ctxDeclVariable = ctxDecl.branch<DeclVariable>();

			onDeclVariable(ctxDeclVariable);

			ctxDecl.merge<DeclVariable>(ctxDeclVariable);
		} else if (AST::isDeclFunction(id)) {
			PassContext<DeclFunction> ctxDeclFunction = ctxDecl.branch<DeclFunction>();

			onDeclFunction(ctxDeclFunction);

			ctxDecl.merge<DeclFunction>(ctxDeclFunction);
		} else if (AST::isDeclClass(id)) {
			PassContext<DeclClass> ctxDeclClass = ctxDecl.branch<DeclClass>();

			onDeclClass(ctxDeclClass);

			ctxDecl.merge<DeclClass>(ctxDeclClass);
		} else if (AST::isDeclNamespace(id)) {
			PassContext<DeclNamespace> ctxDeclNamespace = ctxDecl.branch<DeclNamespace>();

			onDeclNamespace(ctxDeclNamespace);

			ctxDecl.merge<DeclNamespace>(ctxDeclNamespace);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Decl>(ctxDecl);
	} else if (AST::isImport(id)) {
		PassContext<Import> ctxImport = ctx.branch<Import>();

		onImport(ctxImport);

		ctx.merge<Import>(ctxImport);
	} else {
		W_ASSERT_UNREACHABLE("Unsupported AST ID.");
	}
}

void Pass::runPost(PassContext<AST> &ctx) {
	onASTPost(ctx);

	AST::ID id = ctx.getOriginal()->getID();

	if (AST::isType(id)) {
		PassContext<Type> ctxType = ctx.branch<Type>();

		onTypePost(ctxType);

		if (AST::isTypeAtomic(id)) {
			PassContext<TypeAtomic> ctxTypeAtomic = ctxType.branch<TypeAtomic>();

			onTypeAtomicPost(ctxTypeAtomic);

			ctxType.merge<TypeAtomic>(ctxTypeAtomic);
		} else if (AST::isTypeSymbol(id)) {
			PassContext<TypeSymbol> ctxTypeSymbol = ctxType.branch<TypeSymbol>();

			onTypeSymbolPost(ctxTypeSymbol);

			ctxType.merge<TypeSymbol>(ctxTypeSymbol);
		} else if (AST::isTypeUnary(id)) {
			PassContext<TypeUnary> ctxTypeUnary = ctxType.branch<TypeUnary>();

			onTypeUnaryPost(ctxTypeUnary);

			ctxType.merge<TypeUnary>(ctxTypeUnary);
		} else if (AST::isTypeBinary(id)) {
			PassContext<TypeBinary> ctxTypeBinary = ctxType.branch<TypeBinary>();

			onTypeBinaryPost(ctxTypeBinary);

			ctxType.merge<TypeBinary>(ctxTypeBinary);
		} else if (AST::isTypeFunction(id)) {
			PassContext<TypeFunction> ctxTypeFunction = ctxType.branch<TypeFunction>();

			onTypeFunctionPost(ctxTypeFunction);

			ctxType.merge<TypeFunction>(ctxTypeFunction);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Type>(ctxType);
	} else if (AST::isExpr(id)) {
		PassContext<Expr> ctxExpr = ctx.branch<Expr>();

		onExprPost(ctxExpr);

		if (AST::isExprLiteralInt(id)) {
			PassContext<ExprLiteralInt> ctxExprLiteralInt = ctxExpr.branch<ExprLiteralInt>();

			onExprLiteralIntPost(ctxExprLiteralInt);

			ctxExpr.merge<ExprLiteralInt>(ctxExprLiteralInt);
		} else if (AST::isExprLiteralFloat(id)) {
			PassContext<ExprLiteralFloat> ctxExprLiteralFloat = ctxExpr.branch<ExprLiteralFloat>();

			onExprLiteralFloatPost(ctxExprLiteralFloat);

			ctxExpr.merge<ExprLiteralFloat>(ctxExprLiteralFloat);
		} else if (AST::isExprSymbol(id)) {
			PassContext<ExprSymbol> ctxExprSymbol = ctxExpr.branch<ExprSymbol>();

			onExprSymbolPost(ctxExprSymbol);

			ctxExpr.merge<ExprSymbol>(ctxExprSymbol);
		} else if (AST::isExprUnary(id)) {
			PassContext<ExprUnary> ctxExprUnary = ctxExpr.branch<ExprUnary>();

			onExprUnaryPost(ctxExprUnary);

			ctxExpr.merge<ExprUnary>(ctxExprUnary);
		} else if (AST::isExprBinary(id)) {
			PassContext<ExprBinary> ctxExprBinary = ctxExpr.branch<ExprBinary>();

			onExprBinaryPost(ctxExprBinary);

			ctxExpr.merge<ExprBinary>(ctxExprBinary);
		} else if (AST::isExprCall(id)) {
			PassContext<ExprCall> ctxExprCall = ctxExpr.branch<ExprCall>();

			onExprCallPost(ctxExprCall);

			ctxExpr.merge<ExprCall>(ctxExprCall);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Expr>(ctxExpr);
	} else if (AST::isStmt(id)) {
		PassContext<Stmt> ctxStmt = ctx.branch<Stmt>();

		onStmtPost(ctxStmt);

		if (AST::isStmtEmpty(id)) {
			PassContext<StmtEmpty> ctxStmtEmpty = ctxStmt.branch<StmtEmpty>();

			onStmtEmptyPost(ctxStmtEmpty);

			ctxStmt.merge<StmtEmpty>(ctxStmtEmpty);
		} else if (AST::isStmtExpr(id)) {
			PassContext<StmtExpr> ctxStmtExpr = ctxStmt.branch<StmtExpr>();

			onStmtExprPost(ctxStmtExpr);

			ctxStmt.merge<StmtExpr>(ctxStmtExpr);
		} else if (AST::isStmtIf(id)) {
			PassContext<StmtIf> ctxStmtIf = ctxStmt.branch<StmtIf>();

			onStmtIfPost(ctxStmtIf);

			ctxStmt.merge<StmtIf>(ctxStmtIf);
		} else if (AST::isStmtWhile(id)) {
			PassContext<StmtWhile> ctxStmtWhile = ctxStmt.branch<StmtWhile>();

			onStmtWhilePost(ctxStmtWhile);

			ctxStmt.merge<StmtWhile>(ctxStmtWhile);
		} else if (AST::isStmtFor(id)) {
			PassContext<StmtFor> ctxStmtFor = ctxStmt.branch<StmtFor>();

			onStmtForPost(ctxStmtFor);

			ctxStmt.merge<StmtFor>(ctxStmtFor);
		} else if (AST::isStmtForEach(id)) {
			PassContext<StmtForEach> ctxStmtForEach = ctxStmt.branch<StmtForEach>();

			onStmtForEachPost(ctxStmtForEach);

			ctxStmt.merge<StmtForEach>(ctxStmtForEach);
		} else if (AST::isStmtBlock(id)) {
			PassContext<StmtBlock> ctxStmtBlock = ctxStmt.branch<StmtBlock>();

			onStmtBlockPost(ctxStmtBlock);

			ctxStmt.merge<StmtBlock>(ctxStmtBlock);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Stmt>(ctxStmt);
	} else if (AST::isDecl(id)) {
		PassContext<Decl> ctxDecl = ctx.branch<Decl>();

		onDeclPost(ctxDecl);

		if (AST::isDeclVariable(id)) {
			PassContext<DeclVariable> ctxDeclVariable = ctxDecl.branch<DeclVariable>();

			onDeclVariablePost(ctxDeclVariable);

			ctxDecl.merge<DeclVariable>(ctxDeclVariable);
		} else if (AST::isDeclFunction(id)) {
			PassContext<DeclFunction> ctxDeclFunction = ctxDecl.branch<DeclFunction>();

			onDeclFunctionPost(ctxDeclFunction);

			ctxDecl.merge<DeclFunction>(ctxDeclFunction);
		} else if (AST::isDeclClass(id)) {
			PassContext<DeclClass> ctxDeclClass = ctxDecl.branch<DeclClass>();

			onDeclClassPost(ctxDeclClass);

			ctxDecl.merge<DeclClass>(ctxDeclClass);
		} else if (AST::isDeclNamespace(id)) {
			PassContext<DeclNamespace> ctxDeclNamespace = ctxDecl.branch<DeclNamespace>();

			onDeclNamespacePost(ctxDeclNamespace);

			ctxDecl.merge<DeclNamespace>(ctxDeclNamespace);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported AST ID.");
		}

		ctx.merge<Decl>(ctxDecl);
	} else if (AST::isImport(id)) {
		PassContext<Import> ctxImport = ctx.branch<Import>();

		onImportPost(ctxImport);

		ctx.merge<Import>(ctxImport);
	} else {
		W_ASSERT_UNREACHABLE("Unsupported AST ID.");
	}
}
}
