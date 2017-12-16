#include "Module.inc"

#include <whiskey/Printing/DebugPrinter.hpp>

namespace whiskey {
void DebugPrinter::onPrint(std::ostream &os, CRef<AST> ast, unsigned int indent) {
	switch (ast->getID()) {
		case AST::ID::TypeAtomicBool:
			os << "TypeAtomicBool";
			break;
		case AST::ID::TypeAtomicInt8:
			os << "TypeAtomicInt8";
			break;
		case AST::ID::TypeAtomicInt16:
			os << "TypeAtomicInt16";
			break;
		case AST::ID::TypeAtomicInt32:
			os << "TypeAtomicInt32";
			break;
		case AST::ID::TypeAtomicInt64:
			os << "TypeAtomicInt64";
			break;
		case AST::ID::TypeAtomicUInt8:
			os << "TypeAtomicUInt8";
			break;
		case AST::ID::TypeAtomicUInt16:
			os << "TypeAtomicUInt16";
			break;
		case AST::ID::TypeAtomicUInt32:
			os << "TypeAtomicUInt32";
			break;
		case AST::ID::TypeAtomicUInt64:
			os << "TypeAtomicUInt64";
			break;
		case AST::ID::TypeAtomicFloat32:
			os << "TypeAtomicFloat32";
			break;
		case AST::ID::TypeAtomicFloat64:
			os << "TypeAtomicFloat64";
			break;
		case AST::ID::TypeAtomicReal:
			os << "TypeAtomicReal";
			break;
		case AST::ID::TypeSymbol:
			os << "TypeSymbol ";
			printLiteralString(os, ast->as<TypeSymbol>()->getValue());
			printNewline(os, indent+1);
			printVectorHelper(os, ast->as<TypeSymbol>()->getTemplateEvalArgs(), indent+1);
			break;
		case AST::ID::TypeAccessUnary:
			os << "TypeAccessUnary";
			printNewline(os, indent+1);
			print(os, ast->as<TypeUnary>()->getArg()->as<AST>(), indent+1);
			break;
		case AST::ID::TypeAccessBinary:
			os << "TypeAccessBinary";
			printNewline(os, indent+1);
			print(os, ast->as<TypeBinary>()->getLHS()->as<AST>(), indent+1);
			printNewline(os, indent+1);
			print(os, ast->as<TypeBinary>()->getRHS()->as<AST>(), indent+1);
			break;
		case AST::ID::TypeFunction:
			os << "TypeFunction";
			printNewline(os, indent+1);
			print(os, ast->as<TypeFunction>()->getRet()->as<AST>(), indent+1);
			printNewline(os, indent+1);
			printVectorHelper(os, ast->as<TypeFunction>()->getArgs(), indent+1);
			break;
		case AST::ID::ExprLiteralInt:
			break;
		case AST::ID::ExprLiteralFloat:
			break;
		case AST::ID::ExprSymbol:
			break;
		case AST::ID::ExprCall:
			break;
		case AST::ID::ExprAccessUnary:
			break;
		case AST::ID::ExprAccessBinary:
			break;
		case AST::ID::ExprIncPre:
			break;
		case AST::ID::ExprIncPost:
			break;
		case AST::ID::ExprDecPre:
			break;
		case AST::ID::ExprDecPost:
			break;
		case AST::ID::ExprNegate:
			break;
		case AST::ID::ExprBitNot:
			break;
		case AST::ID::ExprExp:
			break;
		case AST::ID::ExprMul:
			break;
		case AST::ID::ExprDiv:
			break;
		case AST::ID::ExprDivInt:
			break;
		case AST::ID::ExprDivReal:
			break;
		case AST::ID::ExprAdd:
			break;
		case AST::ID::ExprSub:
			break;
		case AST::ID::ExprMod:
			break;
		case AST::ID::ExprBitShR:
			break;
		case AST::ID::ExprBitShL:
			break;
		case AST::ID::ExprBitAnd:
			break;
		case AST::ID::ExprBitOr:
			break;
		case AST::ID::ExprBitXor:
			break;
		case AST::ID::ExprLT:
			break;
		case AST::ID::ExprLE:
			break;
		case AST::ID::ExprGT:
			break;
		case AST::ID::ExprGE:
			break;
		case AST::ID::ExprNE:
			break;
		case AST::ID::ExprEQ:
			break;
		case AST::ID::ExprBoolNot:
			break;
		case AST::ID::ExprBoolAnd:
			break;
		case AST::ID::ExprBoolOr:
			break;
		case AST::ID::ExprBoolImplies:
			break;
		case AST::ID::ExprGroup:
			break;
		case AST::ID::StmtEmpty:
			break;
		case AST::ID::StmtExpr:
			break;
		case AST::ID::StmtExprReturn:
			break;
		case AST::ID::StmtIf:
			break;
		case AST::ID::StmtWhile:
			break;
		case AST::ID::StmtFor:
			break;
		case AST::ID::StmtForEach:
			break;
		case AST::ID::StmtBlock:
			break;
		case AST::ID::DeclVariable:
			break;
		case AST::ID::DeclFunction:
			break;
		case AST::ID::DeclClass:
			break;
		case AST::ID::DeclNamespace:
			break;
		case AST::ID::Import:
			break;
	}
}

DebugPrinter::DebugPrinter(unsigned int tabWidth) : Printer(tabWidth) {}
}
