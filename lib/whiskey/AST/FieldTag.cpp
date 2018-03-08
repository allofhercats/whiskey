#include <whiskey/AST/FieldTag.hpp>

namespace whiskey {
namespace {
FieldTagInfo fieldTagInfos[] {
  FieldTagInfo("Children", 0), // List_Children
	FieldTagInfo("TemplateEvalArgs", 0), // TypeSymbol_TemplateEvalArgs
  FieldTagInfo("Arg", 0), // TypeAccessUnary_Arg
  FieldTagInfo("Args", 0), // TypeAccess_Args
  FieldTagInfo("Arg", 0), // TypeGroup_Arg
  FieldTagInfo("Return", 0), // TypeFunction_Return
  FieldTagInfo("Args", 1), // TypeFunction_Args
  FieldTagInfo("Value", 0), // ExprLiteralBool_Value
  FieldTagInfo("Value", 0), // ExprLiteralInt8_Value
  FieldTagInfo("Value", 0), // ExprLiteralInt16_Value
  FieldTagInfo("Value", 0), // ExprLiteralInt32_Value
  FieldTagInfo("Value", 0), // ExprLiteralInt64_Value
  FieldTagInfo("Value", 0), // ExprLiteralUInt8_Value
  FieldTagInfo("Value", 0), // ExprLiteralUInt16_Value
  FieldTagInfo("Value", 0), // ExprLiteralUInt32_Value
  FieldTagInfo("Value", 0), // ExprLiteralUInt64_Value
  FieldTagInfo("Value", 0), // ExprLiteralChar8_Value
  FieldTagInfo("Value", 0), // ExprLiteralChar16_Value
  FieldTagInfo("Value", 0), // ExprLiteralChar32_Value
  FieldTagInfo("Value", 0), // ExprLiteralFloat32_Value
  FieldTagInfo("Value", 0), // ExprLiteralFloat64_Value
  FieldTagInfo("Value", 0), // ExprLiteralReal_Value
  FieldTagInfo("TemplateEvalArgs", 1), // ExprSymbol_TemplateEvalArgs
  FieldTagInfo("Arg", 0), // ExprAccessUnary_Arg
  FieldTagInfo("Args", 0), // ExprAccess_Args
  FieldTagInfo("Arg", 0), // ExprGroup_Arg
  FieldTagInfo("Callee", 0), // ExprCall_Callee
  FieldTagInfo("Args", 1), // ExprCall_Args
  FieldTagInfo("Args", 0), // ExprAdd_Args
  FieldTagInfo("Arg", 0), // ExprIncPre_Arg
  FieldTagInfo("Arg", 0), // ExprIncPost_Arg
  FieldTagInfo("LHS", 0), // ExprSub_LHS
  FieldTagInfo("RHS", 1), // ExprSub_RHS
  FieldTagInfo("Arg", 0), // ExprNeg_Arg
  FieldTagInfo("Arg", 0), // ExprDecPre_Arg
  FieldTagInfo("Arg", 0), // ExprDecPost_Arg
  FieldTagInfo("Args", 0), // ExprMul_Args
  FieldTagInfo("LHS", 0), // ExprExp_LHS
  FieldTagInfo("RHS", 1), // ExprExp_RHS
  FieldTagInfo("LHS", 0), // ExprDiv_LHS
  FieldTagInfo("RHS", 1), // ExprDiv_RHS
  FieldTagInfo("LHS", 0), // ExprDivInt_LHS
  FieldTagInfo("RHS", 1), // ExprDivInt_RHS
  FieldTagInfo("LHS", 0), // ExprDivReal_LHS
  FieldTagInfo("RHS", 1), // ExprDivReal_RHS
  FieldTagInfo("LHS", 0), // ExprMod_LHS
  FieldTagInfo("RHS", 1), // ExprMod_RHS
  FieldTagInfo("Arg", 0), // ExprBitNot_Arg
  FieldTagInfo("Args", 0), // ExprBitAnd_Args
  FieldTagInfo("Args", 0), // ExprBitOr_Args
  FieldTagInfo("Args", 0), // ExprBitXor_Args
  FieldTagInfo("LHS", 0), // ExprBitShL_LHS
  FieldTagInfo("RHS", 1), // ExprBitShL_RHS
  FieldTagInfo("LHS", 0), // ExprBitShR_LHS
  FieldTagInfo("RHS", 1), // ExprBitShR_RHS
  FieldTagInfo("LHS", 0), // ExprLT_LHS
  FieldTagInfo("RHS", 1), // ExprLT_RHS
  FieldTagInfo("LHS", 0), // ExprLE_LHS
  FieldTagInfo("RHS", 1), // ExprLE_RHS
  FieldTagInfo("LHS", 0), // ExprGT_LHS
  FieldTagInfo("RHS", 1), // ExprGT_RHS
  FieldTagInfo("LHS", 0), // ExprGE_LHS
  FieldTagInfo("RHS", 1), // ExprGE_RHS
  FieldTagInfo("LHS", 0), // ExprNE_LHS
  FieldTagInfo("RHS", 1), // ExprNE_RHS
  FieldTagInfo("LHS", 0), // ExprEQ_LHS
  FieldTagInfo("RHS", 1), // ExprEQ_RHS
  FieldTagInfo("Arg", 0), // ExprBoolNot_Arg
  FieldTagInfo("Args", 0), // ExprBoolAnd_Args
  FieldTagInfo("Args", 0), // ExprBoolOr_Args
  FieldTagInfo("Args", 0), // ExprBoolImplies_Args
  FieldTagInfo("LHS", 0), // ExprAddAssign_LHS
  FieldTagInfo("RHS", 1), // ExprAddAssign_RHS
  FieldTagInfo("LHS", 0), // ExprSubAssign_LHS
  FieldTagInfo("RHS", 1), // ExprSubAssign_RHS
  FieldTagInfo("LHS", 0), // ExprMulAssign_LHS
  FieldTagInfo("RHS", 1), // ExprMulAssign_RHS
  FieldTagInfo("LHS", 0), // ExprExpAssign_LHS
  FieldTagInfo("RHS", 1), // ExprExpAssign_RHS
  FieldTagInfo("LHS", 0), // ExprDivAssign_LHS
  FieldTagInfo("RHS", 1), // ExprDivAssign_RHS
  FieldTagInfo("LHS", 0), // ExprDivIntAssign_LHS
  FieldTagInfo("RHS", 1), // ExprDivIntAssign_RHS
  FieldTagInfo("LHS", 0), // ExprDivRealAssign_LHS
  FieldTagInfo("RHS", 1), // ExprDivRealAssign_RHS
  FieldTagInfo("LHS", 0), // ExprModAssign_LHS
  FieldTagInfo("RHS", 1), // ExprModAssign_RHS
  FieldTagInfo("LHS", 0), // ExprBitAndAssign_LHS
  FieldTagInfo("RHS", 1), // ExprBitAndAssign_RHS
  FieldTagInfo("LHS", 0), // ExprBitOrAssign_LHS
  FieldTagInfo("RHS", 1), // ExprBitOrAssign_RHS
  FieldTagInfo("LHS", 0), // ExprBitXorAssign_LHS
  FieldTagInfo("RHS", 1), // ExprBitXorAssign_RHS
  FieldTagInfo("LHS", 0), // ExprBitShLAssign_LHS
  FieldTagInfo("RHS", 1), // ExprBitShLAssign_RHS
  FieldTagInfo("LHS", 0), // ExprBitShRAssign_LHS
  FieldTagInfo("RHS", 1), // ExprBitShRAssign_RHS
  FieldTagInfo("LHS", 0), // ExprAssign_LHS
  FieldTagInfo("RHS", 1), // ExprAssign_RHS
  FieldTagInfo("Expr", 0), // StmtExpr_Expr
  FieldTagInfo("Decl", 0), // StmtDecl_Decl
  FieldTagInfo("Arg", 0), // StmtReturn_Arg
  FieldTagInfo("Name", 0), // StmtContinue_Name
  FieldTagInfo("Name", 0), // StmtBreak_Name
  FieldTagInfo("Condition", 0), // StmtIf_Condition
  FieldTagInfo("Then", 1), // StmtIf_Then
  FieldTagInfo("Else", 2), // StmtIf_Else
  FieldTagInfo("Condition", 0), // StmtWhile_Condition
  FieldTagInfo("Body", 1), // StmtWhile_Body
  FieldTagInfo("Name", 2), // StmtWhile_Name
  FieldTagInfo("Decls", 0), // StmtFor_Decls
  FieldTagInfo("Condition", 1), // StmtFor_Condition
  FieldTagInfo("Steps", 2), // StmtFor_Steps
  FieldTagInfo("Body", 3), // StmtFor_Body
  FieldTagInfo("Name", 4), // StmtFor_Name
  FieldTagInfo("Decl", 0), // StmtForEach_Decl
  FieldTagInfo("Sequence", 1), // StmtForEach_Sequence
  FieldTagInfo("Body", 2), // StmtForEach_Body
  FieldTagInfo("Name", 3), // StmtForEach_Name
  FieldTagInfo("Stmts", 0), // StmtBlock_Stmts
  FieldTagInfo("Type", 0), // DeclVariable_Type
  FieldTagInfo("TemplateDeclArgs", 2), // DeclVariable_TemplateDeclArgs
  FieldTagInfo("Initial", 3), // DeclVariable_Initial
  FieldTagInfo("Return", 0), // DeclFunction_Return
  FieldTagInfo("TemplateDeclArgs", 2), // DeclFunction_TemplateDeclArgs
  FieldTagInfo("Args", 3), // DeclFunction_Args
  FieldTagInfo("Body", 4), // DeclFunction_Body
  FieldTagInfo("TemplateDeclArgs", 1), // DeclClass_TemplateDeclArgs
  FieldTagInfo("Inherits", 2), // DeclClass_Inherits
  FieldTagInfo("Members", 3), // DeclClass_Members
  FieldTagInfo("Members", 1), // DeclNamespace_Members
  FieldTagInfo("Path", 0), // Import_Path
  FieldTagInfo("Members", 0) // Unit_Members
};
}

const FieldTagInfo &FieldTagInfo::get(FieldTag fieldTag) {
	return fieldTagInfos[static_cast<int>(fieldTag)];
}

FieldTagInfo::FieldTagInfo(std::string name, std::vector<std::unique_ptr<Field>>::size_type index) : name(name), index(index) {}

const std::string &FieldTagInfo::getName() const {
	return name;
}

std::vector<std::unique_ptr<Field>>::size_type FieldTagInfo::getIndex() const {
	return index;
}
}
