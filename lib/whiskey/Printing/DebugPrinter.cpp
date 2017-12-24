#include "Module.inc"

#include <whiskey/Printing/DebugPrinter.hpp>

namespace whiskey {
void DebugPrinter::onPrint(std::ostream &os, CRef<AST> ast, unsigned int indent) {
	switch (ast->getID()) {
		case AST::ID::TypeAtomicBool:
			os << Color::greenLight << "TypeAtomicBool" << Color::reset;
			break;
		case AST::ID::TypeAtomicInt8:
			os << Color::greenLight << "TypeAtomicInt8" << Color::reset;
			break;
		case AST::ID::TypeAtomicInt16:
			os << Color::greenLight << "TypeAtomicInt16" << Color::reset;
			break;
		case AST::ID::TypeAtomicInt32:
			os << Color::greenLight << "TypeAtomicInt32" << Color::reset;
			break;
		case AST::ID::TypeAtomicInt64:
			os << Color::greenLight << "TypeAtomicInt64" << Color::reset;
			break;
		case AST::ID::TypeAtomicUInt8:
			os << Color::greenLight << "TypeAtomicUInt8" << Color::reset;
			break;
		case AST::ID::TypeAtomicUInt16:
			os << Color::greenLight << "TypeAtomicUInt16" << Color::reset;
			break;
		case AST::ID::TypeAtomicUInt32:
			os << Color::greenLight << "TypeAtomicUInt32" << Color::reset;
			break;
		case AST::ID::TypeAtomicUInt64:
			os << Color::greenLight << "TypeAtomicUInt64" << Color::reset;
			break;
		case AST::ID::TypeAtomicFloat32:
			os << Color::greenLight << "TypeAtomicFloat32" << Color::reset;
			break;
		case AST::ID::TypeAtomicFloat64:
			os << Color::greenLight << "TypeAtomicFloat64" << Color::reset;
			break;
		case AST::ID::TypeAtomicReal:
			os << Color::greenLight << "TypeAtomicReal" << Color::reset;
			break;
		case AST::ID::TypeSymbol:
			os << Color::greenLight << "TypeSymbol " << Color::yellowLight;
			printLiteralString(os, ast->as<TypeSymbol>()->getValue());
			os << Color::reset;
			if (!ast->as<TypeSymbol>()->getTemplateEvalArgs().empty()) {
				printVectorHelper(os, "templateEvalArgs", ast->as<TypeSymbol>()->getTemplateEvalArgs(), indent);
			}
			break;
		case AST::ID::TypeGroup:
			os << Color::greenLight << "TypeGroup" << Color::reset;
			printHelper(os, "arg", ast->as<TypeUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::TypeAccessUnary:
			os << Color::greenLight << "TypeAccessUnary" << Color::reset;
			printHelper(os, "arg", ast->as<TypeUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::TypeAccessBinary:
			os << Color::greenLight << "TypeAccessBinary" << Color::reset;
			printHelper(os, "lhs", ast->as<TypeBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<TypeBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::TypeFunction:
			os << Color::greenLight << "TypeFunction" << Color::reset;
			printHelper(os, "ret", ast->as<TypeFunction>()->getRet()->as<AST>(), indent);
			if (!ast->as<TypeFunction>()->getArgs().empty()) {
				printVectorHelper(os, "args", ast->as<TypeFunction>()->getArgs(), indent);
			}
			break;
		case AST::ID::ExprLiteralInt:
			os << Color::greenLight << "ExprLiteralInt " << Color::yellowLight << ast->as<ExprLiteralInt>()->getValue() << Color::reset;
			printHelper(os, "type", ast->as<ExprLiteralInt>()->getType()->as<AST>(), indent);
			break;
		case AST::ID::ExprLiteralFloat:
			os << Color::greenLight << "ExprLiteralFloat " << Color::yellowLight << ast->as<ExprLiteralFloat>()->getValue() << Color::reset;
			printHelper(os, "type", ast->as<ExprLiteralFloat>()->getType()->as<AST>(), indent);
			break;
		case AST::ID::ExprSymbol:
			os << Color::greenLight << "ExprSymbol " << Color::yellowLight;
			printLiteralString(os, ast->as<ExprSymbol>()->getValue());
			os << Color::reset;
			if (!ast->as<ExprSymbol>()->getTemplateEvalArgs().empty()) {
				printVectorHelper(os, "templateEvalArgs", ast->as<ExprSymbol>()->getTemplateEvalArgs(), indent);
			}
			break;
		case AST::ID::ExprCall:
			os << Color::greenLight << "ExprCall" << Color::reset;
			printHelper(os, "callee", ast->as<ExprCall>()->getCallee()->as<AST>(), indent);
			if (!ast->as<ExprCall>()->getArgs().empty()) {
				printVectorHelper(os, "args", ast->as<ExprCall>()->getArgs(), indent);
			}
			break;
		case AST::ID::ExprAccessUnary:
			os << Color::greenLight << "ExprAccessUnary" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprAccessBinary:
			os << Color::greenLight << "ExprAccessBinary" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprIncPre:
			os << Color::greenLight << "ExprIncPre" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprIncPost:
			os << Color::greenLight << "ExprIncPost" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprDecPre:
			os << Color::greenLight << "ExprDecPre" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprDecPost:
			os << Color::greenLight << "ExprDecPost" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprNegate:
			os << Color::greenLight << "ExprNegate" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitNot:
			os << Color::greenLight << "ExprBitNot" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprExp:
			os << Color::greenLight << "ExprExp" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprMul:
			os << Color::greenLight << "ExprMul" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprDiv:
			os << Color::greenLight << "ExprDiv" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprDivInt:
			os << Color::greenLight << "ExprDivInt" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprDivReal:
			os << Color::greenLight << "ExprDivReal" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprAdd:
			os << Color::greenLight << "ExprAdd" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprSub:
			os << Color::greenLight << "ExprSub" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprMod:
			os << Color::greenLight << "ExprMod" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitShR:
			os << Color::greenLight << "ExprBitShR" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitShL:
			os << Color::greenLight << "ExprBitShL" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitAnd:
			os << Color::greenLight << "ExprBitAnd" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitOr:
			os << Color::greenLight << "ExprBitOr" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitXor:
			os << Color::greenLight << "ExprBitXor" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprExpAssign:
			os << Color::greenLight << "ExprExpAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprMulAssign:
			os << Color::greenLight << "ExprMulAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprDivAssign:
			os << Color::greenLight << "ExprDivAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprDivIntAssign:
			os << Color::greenLight << "ExprDivIntAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprDivRealAssign:
			os << Color::greenLight << "ExprDivRealAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprAddAssign:
			os << Color::greenLight << "ExprAddAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprSubAssign:
			os << Color::greenLight << "ExprSubAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprModAssign:
			os << Color::greenLight << "ExprModAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitShRAssign:
			os << Color::greenLight << "ExprBitShRAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitShLAssign:
			os << Color::greenLight << "ExprBitShLAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitAndAssign:
			os << Color::greenLight << "ExprBitAndAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitOrAssign:
			os << Color::greenLight << "ExprBitOrAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBitXorAssign:
			os << Color::greenLight << "ExprBitXorAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprAssign:
			os << Color::greenLight << "ExprAssign" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprLT:
			os << Color::greenLight << "ExprLT" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprLE:
			os << Color::greenLight << "ExprLE" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprGT:
			os << Color::greenLight << "ExprGT" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprGE:
			os << Color::greenLight << "ExprGE" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprNE:
			os << Color::greenLight << "ExprNE" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprEQ:
			os << Color::greenLight << "ExprEQ" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBoolNot:
			os << Color::greenLight << "ExprBoolNot" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::ExprBoolAnd:
			os << Color::greenLight << "ExprBoolAnd" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBoolOr:
			os << Color::greenLight << "ExprBoolOr" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprBoolImplies:
			os << Color::greenLight << "ExprBoolImplies" << Color::reset;
			printHelper(os, "lhs", ast->as<ExprBinary>()->getLHS()->as<AST>(), indent);
			printHelper(os, "rhs", ast->as<ExprBinary>()->getRHS()->as<AST>(), indent);
			break;
		case AST::ID::ExprGroup:
			os << Color::greenLight << "ExprGroup" << Color::reset;
			printHelper(os, "arg", ast->as<ExprUnary>()->getArg()->as<AST>(), indent);
			break;
		case AST::ID::StmtEmpty:
			os << Color::greenLight << "StmtEmpty" << Color::reset;
			break;
		case AST::ID::StmtExpr:
			os << Color::greenLight << "StmtExpr" << Color::reset;
			printHelper(os, "value", ast->as<StmtExpr>()->getValue()->as<AST>(), indent);
			break;
		case AST::ID::StmtReturn:
			os << Color::greenLight << "StmtReturn" << Color::reset;
			printHelper(os, "value", ast->as<StmtExpr>()->getValue()->as<AST>(), indent);
			break;
		case AST::ID::StmtIf:
			os << Color::greenLight << "StmtIf" << Color::reset;
			printHelper(os, "condition", ast->as<StmtIf>()->getCondition()->as<AST>(), indent);
			printHelper(os, "thenClause", ast->as<StmtIf>()->getThenClause()->as<AST>(), indent);
			if (ast->as<StmtIf>()->getElseClause()) {
				printHelper(os, "elseClause", ast->as<StmtIf>()->getElseClause()->as<AST>(), indent);
			}
			break;
		case AST::ID::StmtWhile:
			os << Color::greenLight << "StmtWhile" << Color::reset;
			printHelper(os, "condition", ast->as<StmtWhile>()->getCondition()->as<AST>(), indent);
			if (ast->as<StmtWhile>()->getBodyClause()) {
				printHelper(os, "bodyClause", ast->as<StmtWhile>()->getBodyClause()->as<AST>(), indent);
			}
			break;
		case AST::ID::StmtFor:
			os << Color::greenLight << "StmtFor" << Color::reset;
			if (!ast->as<StmtFor>()->getDecls().empty()) {
				printVectorHelper(os, "decls", ast->as<StmtFor>()->getDecls(), indent);
			}
			if (ast->as<StmtFor>()->getCondition()) {
				printHelper(os, "condition", ast->as<StmtFor>()->getCondition()->as<AST>(), indent);
			}
			if (!ast->as<StmtFor>()->getSteps().empty()) {
				printVectorHelper(os, "steps", ast->as<StmtFor>()->getSteps(), indent);
			}
			if (ast->as<StmtFor>()->getBodyClause()) {
				printHelper(os, "bodyClause", ast->as<StmtFor>()->getBodyClause()->as<AST>(), indent);
			}
			break;
		case AST::ID::StmtForEach:
			os << Color::greenLight << "StmtForEach" << Color::reset;
			if (ast->as<StmtForEach>()->getValue()) {
				printHelper(os, "value", ast->as<StmtForEach>()->getValue()->as<AST>(), indent);
			}
			if (ast->as<StmtForEach>()->getSequence()) {
				printHelper(os, "sequence", ast->as<StmtForEach>()->getSequence()->as<AST>(), indent);
			}
			if (ast->as<StmtForEach>()->getBodyClause()) {
				printHelper(os, "bodyClause", ast->as<StmtForEach>()->getBodyClause()->as<AST>(), indent);
			}
			break;
		case AST::ID::StmtBlock:
			os << Color::greenLight << "StmtBlock" << Color::reset;
			if (!ast->as<StmtBlock>()->getBody().empty()) {
				printVectorHelper(os, "body", ast->as<StmtBlock>()->getBody(), indent);
			}
			break;
		case AST::ID::DeclVariable:
			os << Color::greenLight << "DeclVariable " << Color::yellowLight;
			printLiteralString(os, ast->as<DeclVariable>()->getName());
			os << Color::reset;
			if (!ast->as<DeclVariable>()->getTemplateDeclArgs().empty()) {
				printVectorHelper(os, "templateDeclArgs", ast->as<DeclVariable>()->getTemplateDeclArgs(), indent);
			}
			printHelper(os, "type", ast->as<DeclVariable>()->getType(), indent);
			if (ast->as<DeclVariable>()->getInit()) {
				printHelper(os, "init", ast->as<DeclVariable>()->getInit(), indent);
			}
			break;
		case AST::ID::DeclFunction:
			os << Color::greenLight << "DeclFunction " << Color::yellowLight;
			printLiteralString(os, ast->as<DeclFunction>()->getName());
			os << Color::reset;
			if (!ast->as<DeclFunction>()->getTemplateDeclArgs().empty()) {
				printVectorHelper(os, "templateDeclArgs", ast->as<DeclFunction>()->getTemplateDeclArgs(), indent);
			}
			printHelper(os, "ret", ast->as<DeclFunction>()->getRet(), indent);
			if (!ast->as<DeclFunction>()->getArgs().empty()) {
				printVectorHelper(os, "args", ast->as<DeclFunction>()->getArgs(), indent);
			}
			if (ast->as<DeclFunction>()->getBody()) {
				printHelper(os, "body", ast->as<DeclFunction>()->getBody(), indent);
			}
			break;
		case AST::ID::DeclClass:
			os << Color::greenLight << "DeclClass " << Color::yellowLight;
			printLiteralString(os, ast->as<DeclClass>()->getName());
			os << Color::reset;
			if (!ast->as<DeclClass>()->getTemplateDeclArgs().empty()) {
				printVectorHelper(os, "templateDeclArgs", ast->as<DeclClass>()->getTemplateDeclArgs(), indent);
			}
			if (!ast->as<DeclClass>()->getInherits().empty()) {
				printVectorHelper(os, "inherits", ast->as<DeclClass>()->getInherits(), indent);
			}
			if (!ast->as<DeclClass>()->getMembers().empty()) {
				printVectorHelper(os, "members", ast->as<DeclClass>()->getMembers(), indent);
			}
			break;
		case AST::ID::DeclNamespace:
			os << Color::greenLight << "DeclNamespace " << Color::yellowLight;
			printLiteralString(os, ast->as<DeclNamespace>()->getName());
			os << Color::reset;
			if (!ast->as<DeclNamespace>()->getTemplateDeclArgs().empty()) {
				printVectorHelper(os, "templateDeclArgs", ast->as<DeclNamespace>()->getTemplateDeclArgs(), indent);
			}
			if (!ast->as<DeclNamespace>()->getMembers().empty()) {
				printVectorHelper(os, "members", ast->as<DeclNamespace>()->getMembers(), indent);
			}
			break;
		case AST::ID::Import:
			os << Color::greenLight << "Import " << Color::yellowLight;
			printLiteralString(os, ast->as<Import>()->getPath());
			os << Color::reset;
			break;
	}
}

DebugPrinter::DebugPrinter(unsigned int tabWidth) : Printer(tabWidth) {}
}
