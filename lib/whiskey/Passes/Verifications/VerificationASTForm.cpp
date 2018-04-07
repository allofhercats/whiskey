#include <whiskey/Passes/Verifications/VerificationASTForm.hpp>

#include <limits.h>

#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/Requires.hpp>

namespace whiskey {
bool VerificationASTForm::onVerifyPre(const Node &node, MessageContext &msgs) {
	if (node.getType() == NodeType::TypeSymbol) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::TypeSymbol_TemplateEvalArgs, {
			NodeTypeCategory::Type,
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::TypeAccessUnary) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::TypeAccessUnary_Arg, {
			NodeTypeCategory::Type
		});
	} else if (node.getType() == NodeType::TypeAccess) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::TypeAccess_Args, {
			NodeTypeCategory::Type
		});
	} else if (node.getType() == NodeType::TypeGroup) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::TypeGroup_Arg, {
			NodeTypeCategory::Type
		});
	} else if (node.getType() == NodeType::TypeFunction) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::TypeFunction_Return, {
			NodeTypeCategory::Type
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::TypeFunction_Args, {
			NodeTypeCategory::Type
		});
	} else if (node.getType() == NodeType::ExprLiteralBool) {
		requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralBool_Value, {
			FieldFormat::UInt
		});
	} else if (node.getType() == NodeType::ExprLiteralInt8) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralInt8_Value, {
			FieldFormat::Int
		})) {
			if (node.getField(FieldTag::ExprLiteralInt8_Value).getInt() < SCHAR_MIN || node.getField(FieldTag::ExprLiteralInt8_Value).getInt() > SCHAR_MAX) {
				msgs.describe() << "literal value must be in range " << SCHAR_MIN << " through " << SCHAR_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralInt16) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralInt16_Value, {
			FieldFormat::Int
		})) {
			if (node.getField(FieldTag::ExprLiteralInt16_Value).getInt() < SHRT_MIN || node.getField(FieldTag::ExprLiteralInt16_Value).getInt() > SHRT_MAX) {
				msgs.describe() << "literal value must be in range " << SHRT_MIN << " through " << SHRT_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralInt32) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralInt32_Value, {
			FieldFormat::Int
		})) {
			if (node.getField(FieldTag::ExprLiteralInt32_Value).getInt() < INT_MIN || node.getField(FieldTag::ExprLiteralInt32_Value).getInt() > INT_MAX) {
				msgs.describe() << "literal value must be in range " << INT_MIN << " through " << INT_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralInt64) {
		requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralInt64_Value, {
			FieldFormat::Int
		});
	} else if (node.getType() == NodeType::ExprLiteralUInt8) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralUInt8_Value, {
			FieldFormat::UInt
		})) {
			if (node.getField(FieldTag::ExprLiteralUInt8_Value).getUInt() > CHAR_MAX) {
				msgs.describe() << "literal value must be no more than " << CHAR_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralUInt16) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralUInt16_Value, {
			FieldFormat::UInt
		})) {
			if (node.getField(FieldTag::ExprLiteralUInt16_Value).getUInt() > USHRT_MAX) {
				msgs.describe() << "literal value must be no more than " << USHRT_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralUInt32) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralUInt32_Value, {
			FieldFormat::UInt
		})) {
			if (node.getField(FieldTag::ExprLiteralUInt32_Value).getUInt() > UINT_MAX) {
				msgs.describe() << "literal value must be no more than " << UINT_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralUInt64) {
		requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralUInt64_Value, {
			FieldFormat::UInt
		});
	} else if (node.getType() == NodeType::ExprLiteralChar8) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralChar8_Value, {
			FieldFormat::UInt
		})) {
			if (node.getField(FieldTag::ExprLiteralChar8_Value).getUInt() > CHAR_MAX) {
				msgs.describe() << "literal value must be no more than " << CHAR_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralChar16) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralChar16_Value, {
			FieldFormat::UInt
		})) {
			if (node.getField(FieldTag::ExprLiteralChar16_Value).getUInt() > USHRT_MAX) {
				msgs.describe() << "literal value must be no more than " << USHRT_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralChar32) {
		if (requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralChar32_Value, {
			FieldFormat::UInt
		})) {
			if (node.getField(FieldTag::ExprLiteralChar32_Value).getUInt() > UINT_MAX) {
				msgs.describe() << "literal value must be no more than " << UINT_MAX;
				msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
			}
		}
	} else if (node.getType() == NodeType::ExprLiteralFloat32) {
		requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralFloat32_Value, {
			FieldFormat::Real
		});
	} else if (node.getType() == NodeType::ExprLiteralFloat64) {
		requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralFloat64_Value, {
			FieldFormat::Real
		});
	} else if (node.getType() == NodeType::ExprLiteralReal) {
		requireFieldWithFormat(node, msgs, FieldTag::ExprLiteralReal_Value, {
			FieldFormat::Real
		});
	} else if (node.getType() == NodeType::ExprSymbol) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprSymbol_TemplateEvalArgs, {
			NodeTypeCategory::Type,
			NodeTypeCategory::Expr
		});
	}  else if (node.getType() == NodeType::ExprAccessUnary) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprAccessUnary_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprAccess) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprAccess_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprGroup) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprGroup_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprCall) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprCall_Callee, {
			NodeTypeCategory::Expr
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprCall_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprAccessUnary) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprAccessUnary_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprAccess) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprAccess_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprGroup) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprGroup_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprAdd) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprAdd_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprIncPre) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprIncPre_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprIncPost) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprIncPost_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprSub) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprSub_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprSub_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprNeg) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprNeg_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDecPre) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDecPre_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDecPost) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDecPost_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprMul) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprMul_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprExp) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprExp_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprExp_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDiv) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDiv_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDiv_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDivInt) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivInt_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivInt_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDivReal) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivReal_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivReal_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprMod) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprMod_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprMod_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitNot) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitNot_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitAnd) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprBitAnd_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitOr) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprBitOr_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitXor) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprBitXor_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitShL) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShL_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShL_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitShR) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShR_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShR_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprLT) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprLT_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprLT_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprLE) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprLE_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprLE_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprGT) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprGT_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprGT_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprGE) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprGE_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprGE_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprNE) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprNE_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprNE_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprEQ) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprEQ_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprEQ_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBoolNot) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBoolNot_Arg, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBoolAnd) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprBoolAnd_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBoolOr) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprBoolOr_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBoolImplies) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::ExprBoolImplies_Args, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprAddAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprAddAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprAddAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprSubAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprSubAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprSubAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprMulAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprMulAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprMulAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprExpAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprExpAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprExpAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDivAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDivIntAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivIntAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivIntAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprDivRealAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivRealAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprDivRealAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprModAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprModAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprModAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitAndAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitAndAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitAndAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitOrAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitOrAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitOrAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitXorAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitXorAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitXorAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitShLAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShLAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShLAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprBitShRAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShRAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprBitShRAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::ExprAssign) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprAssign_LHS, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::ExprAssign_RHS, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::StmtExpr) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtExpr_Expr, {
			NodeTypeCategory::Expr
		});
	} else if (node.getType() == NodeType::StmtDecl) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtDecl_Decl, {
			NodeTypeCategory::Decl
		});
	} else if (node.getType() == NodeType::StmtReturn) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtDecl_Decl, {
			NodeTypeCategory::Decl
		}, true);
	} else if (node.getType() == NodeType::StmtContinue) {
		requireFieldWithFormat(node, msgs, FieldTag::StmtContinue_Name, {
			FieldFormat::String
		}, true);
	} else if (node.getType() == NodeType::StmtBreak) {
		requireFieldWithFormat(node, msgs, FieldTag::StmtBreak_Name, {
			FieldFormat::String
		}, true);
	} else if (node.getType() == NodeType::StmtIf) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtIf_Condition, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtIf_Then, {
			NodeTypeCategory::Stmt
		}, true);
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtIf_Else, {
			NodeTypeCategory::Stmt
		}, true);
	} else if (node.getType() == NodeType::StmtWhile) {
		requireFieldWithFormat(node, msgs, FieldTag::StmtWhile_Name, {
			FieldFormat::String
		}, true);
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtWhile_Condition, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtWhile_Body, {
			NodeTypeCategory::Stmt
		}, true);
	} else if (node.getType() == NodeType::StmtFor) {
		requireFieldWithFormat(node, msgs, FieldTag::StmtFor_Name, {
			FieldFormat::String
		}, true);
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::StmtFor_Decls, {
			NodeTypeCategory::Decl
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtFor_Condition, {
			NodeTypeCategory::Expr
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::StmtFor_Steps, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtFor_Body, {
			NodeTypeCategory::Stmt
		}, true);
	} else if (node.getType() == NodeType::StmtForEach) {
		requireFieldWithFormat(node, msgs, FieldTag::StmtForEach_Name, {
			FieldFormat::String
		}, true);
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtForEach_Decl, {
			NodeTypeCategory::Decl
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtForEach_Sequence, {
			NodeTypeCategory::Expr
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::StmtForEach_Body, {
			NodeTypeCategory::Stmt
		}, true);
	} else if (node.getType() == NodeType::StmtBlock) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::StmtBlock_Stmts, {
			NodeTypeCategory::Stmt
		});
	} else if (node.getType() == NodeType::DeclVariable) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::DeclVariable_Type, {
			NodeTypeCategory::Type
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::DeclVariable_TemplateDeclArgs, {
			NodeTypeCategory::Decl
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::DeclVariable_Initial, {
			NodeTypeCategory::Expr
		}, true);
	} else if (node.getType() == NodeType::DeclFunction) {
		requireNodeFieldWithCategory(node, msgs, FieldTag::DeclFunction_Return, {
			NodeTypeCategory::Type
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::DeclFunction_TemplateDeclArgs, {
			NodeTypeCategory::Decl
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::DeclFunction_Args, {
			NodeTypeCategory::Decl
		});
		requireNodeFieldWithCategory(node, msgs, FieldTag::DeclFunction_Body, {
			NodeTypeCategory::Stmt,
			NodeTypeCategory::Expr
		}, true);
	} else if (node.getType() == NodeType::DeclClass) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::DeclClass_TemplateDeclArgs, {
			NodeTypeCategory::Decl
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::DeclClass_Inherits, {
			NodeTypeCategory::Type
		});
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::DeclClass_Members, {
			NodeTypeCategory::Decl
		});
	} else if (node.getType() == NodeType::DeclNamespace) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::DeclNamespace_Members, {
			NodeTypeCategory::Decl
		});
	} else if (node.getType() == NodeType::Import) {
		requireFieldWithFormat(node, msgs, FieldTag::Import_Path, {
			FieldFormat::String
		});
	} else if (node.getType() == NodeType::Unit) {
		requireNodeVectorFieldWithCategory(node, msgs, FieldTag::Unit_Members, {
			NodeTypeCategory::Decl,
			NodeTypeCategory::Import
		});
	} else {
		W_ASSERT_UNREACHABLE("Unsupported node type " << node.getType() << ".");
	}

	return true;
}

bool VerificationASTForm::onVerifyPost(const Node &node, MessageContext &msgs) {
	return true;
}

VerificationASTForm::VerificationASTForm() : Verification("VerificationASTForm") {}
}
