#include <whiskey/Passes/Verifications/VerificationPreCodeGen.hpp>

#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/Requires.hpp>
#include <whiskey/AST/Predicates.hpp>

namespace whiskey {
bool VerificationPreCodeGen::onVerifyPre(const Node &node, MessageContext &msgs) {
	if (node.getType() == NodeType::TypeVoid) {
		// do nothing
	} else if (isAtomicType(node.getType())) {
		// do nothing
	} else if (node.getType() == NodeType::TypeFunction) {
		if (node.getField(FieldTag::TypeFunction_Return).getNode().getType() == NodeType::TypeFunction) {
			msgs.describe() << "cannot return function type without pointer wrapping";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}

		for (const Node &i : node.getField(FieldTag::TypeFunction_Args).getNodeVector()) {
			if (i.getType() == NodeType::TypeVoid) {
				msgs.describe() << "cannot take void type as argument";
				msgs.emit(i.getToken(), Message::Severity::InternalCompilerError);
			} else if (i.getType() == NodeType::TypeFunction) {
				msgs.describe() << "cannot take function type as argument without pointer wrapping";
				msgs.emit(i.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (isLiteralExpr(node.getType())) {
		// do nothing
	} else if (node.getType() == NodeType::ExprAdd) {
		if (node.getField(FieldTag::ExprAdd_Args).getNodeVector().size() >= 2) {
			msgs.describe() << "in node of type '" << node.getType() << "', node vector field '" << FieldTag::ExprAdd_Args << "' must have at least 2 elements";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::ExprNeg) {
		// do nothing
	} else if (node.getType() == NodeType::ExprMul) {
		if (node.getField(FieldTag::ExprMul_Args).getNodeVector().size() >= 2) {
			msgs.describe() << "in node of type '" << node.getType() << "', node vector field '" << FieldTag::ExprMul_Args << "' must have at least 2 elements";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::ExprDivInt) {
		// do nothing
	} else if (node.getType() == NodeType::ExprDivReal) {
		// do nothing
	} else if (node.getType() == NodeType::ExprMod) {
		// do nothing
	} else if (node.getType() == NodeType::ExprBitNot) {
		// do nothing
	} else if (node.getType() == NodeType::ExprBitAnd) {
		if (node.getField(FieldTag::ExprBitAnd_Args).getNodeVector().size() >= 2) {
			msgs.describe() << "in node of type '" << node.getType() << "', node vector field '" << FieldTag::ExprBitAnd_Args << "' must have at least 2 elements";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::ExprBitOr) {
		if (node.getField(FieldTag::ExprBitOr_Args).getNodeVector().size() >= 2) {
			msgs.describe() << "in node of type '" << node.getType() << "', node vector field '" << FieldTag::ExprBitOr_Args << "' must have at least 2 elements";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::ExprBitXor) {
		if (node.getField(FieldTag::ExprBitXor_Args).getNodeVector().size() >= 2) {
			msgs.describe() << "in node of type '" << node.getType() << "', node vector field '" << FieldTag::ExprBitXor_Args << "' must have at least 2 elements";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::ExprBitShL) {
		// do nothing
	} else if (node.getType() == NodeType::ExprBitShR) {
		// do nothing
	} else if (node.getType() == NodeType::ExprLT) {
		// do nothing
	} else if (node.getType() == NodeType::ExprLE) {
		// do nothing
	} else if (node.getType() == NodeType::ExprGT) {
		// do nothing
	} else if (node.getType() == NodeType::ExprGE) {
		// do nothing
	} else if (node.getType() == NodeType::ExprNE) {
		// do nothing
	} else if (node.getType() == NodeType::ExprEQ) {
		// do nothing
	} else if (node.getType() == NodeType::ExprBoolNot) {
		// do nothing
	} else if (node.getType() == NodeType::ExprBoolAnd) {
		if (node.getField(FieldTag::ExprBoolAnd_Args).getNodeVector().size() >= 2) {
			msgs.describe() << "in node of type '" << node.getType() << "', node vector field '" << FieldTag::ExprBoolAnd_Args << "' must have at least 2 elements";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::ExprBoolOr) {
		if (node.getField(FieldTag::ExprBoolOr_Args).getNodeVector().size() >= 2) {
			msgs.describe() << "in node of type '" << node.getType() << "', node vector field '" << FieldTag::ExprBoolOr_Args << "' must have at least 2 elements";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::ExprAssign) {
		// do nothing
	} else if (node.getType() == NodeType::StmtExpr) {
		// do nothing
	} else if (node.getType() == NodeType::StmtReturn) {
		// do nothing
	} else if (node.getType() == NodeType::StmtBlock) {
		// do nothing
	} else if (node.getType() == NodeType::DeclVariable) {
		if (node.getField(FieldTag::DeclVariable_Type).getNode().getType() == NodeType::TypeVoid) {
			msgs.describe() << "variable cannot have void type";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		} else if (node.getField(FieldTag::DeclVariable_Type).getNode().getType() == NodeType::TypeFunction) {
			msgs.describe() << "variable cannot have function type without pointer wrapping";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}

		if (!node.getField(FieldTag::DeclVariable_TemplateDeclArgs).getNodeVector().empty()) {
			msgs.describe() << "variable cannot have template arguments";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}

		if (node.getToken().getText().empty()) {
			msgs.describe() << "variable must have non-empty name";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}

		if (node.hasField(FieldTag::DeclVariable_Initial)) {
			msgs.describe() << "variable cannot have initial value";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else if (node.getType() == NodeType::DeclFunction) {
		if (node.getField(FieldTag::DeclFunction_Return).getNode().getType() == NodeType::TypeFunction) {
			msgs.describe() << "cannot return function type without pointer wrapping";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}

		if (node.getField(FieldTag::DeclFunction_Body).getNode().getType() != NodeType::StmtBlock) {
			msgs.describe() << "function must have statement block body";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}

		if (!node.getField(FieldTag::DeclFunction_TemplateDeclArgs).getNodeVector().empty()) {
			msgs.describe() << "function cannot have template arguments";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}

		if (node.getToken().getText().empty()) {
			msgs.describe() << "function must have non-empty name";
			msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		}
	} else {
		msgs.describe() << "node type '" << node.getType() << "' is not supported by code generation";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
	}

	return true;
}

bool VerificationPreCodeGen::onVerifyPost(const Node &node, MessageContext &msgs) {
	return true;
}

VerificationPreCodeGen::VerificationPreCodeGen() : Verification("VerificationPreCodeGen", {"VerificationASTForm"}) {}
}
