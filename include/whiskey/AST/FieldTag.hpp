#ifndef __WHISKEY_AST_FieldTag_HPP
#define __WHISKEY_AST_FieldTag_HPP

#include <memory>
#include <string>
#include <vector>

namespace whiskey {
enum class FieldTag {
  List_Children,
  TypeSymbol_TemplateEvalArgs,
  TypeAccessUnary_Arg,
  TypeAccess_Args,
  TypeGroup_Arg,
  TypeFunction_Return,
  TypeFunction_Args,
  ExprLiteralBool_Value,
  ExprLiteralInt8_Value,
  ExprLiteralInt16_Value,
  ExprLiteralInt32_Value,
  ExprLiteralInt64_Value,
  ExprLiteralUInt8_Value,
  ExprLiteralUInt16_Value,
  ExprLiteralUInt32_Value,
  ExprLiteralUInt64_Value,
  ExprLiteralChar8_Value,
  ExprLiteralChar16_Value,
  ExprLiteralChar32_Value,
  ExprLiteralFloat32_Value,
  ExprLiteralFloat64_Value,
  ExprLiteralReal_Value,
  ExprSymbol_TemplateEvalArgs,
  ExprAccessUnary_Arg,
  ExprAccess_Args,
  ExprGroup_Arg,
  ExprCall_Callee,
  ExprCall_Args,
  ExprAdd_Args,
  ExprIncPre_Arg,
  ExprIncPost_Arg,
  ExprSub_LHS,
  ExprSub_RHS,
  ExprNeg_Arg,
  ExprDecPre_Arg,
  ExprDecPost_Arg,
  ExprMul_Args,
  ExprExp_LHS,
  ExprExp_RHS,
  ExprDiv_LHS,
  ExprDiv_RHS,
  ExprDivInt_LHS,
  ExprDivInt_RHS,
  ExprDivReal_LHS,
  ExprDivReal_RHS,
  ExprMod_LHS,
  ExprMod_RHS,
  ExprBitNot_Arg,
  ExprBitAnd_Args,
  ExprBitOr_Args,
  ExprBitXor_Args,
  ExprBitShL_LHS,
  ExprBitShL_RHS,
  ExprBitShR_LHS,
  ExprBitShR_RHS,
  ExprLT_LHS,
  ExprLT_RHS,
  ExprLE_LHS,
  ExprLE_RHS,
  ExprGT_LHS,
  ExprGT_RHS,
  ExprGE_LHS,
  ExprGE_RHS,
  ExprNE_LHS,
  ExprNE_RHS,
  ExprEQ_LHS,
  ExprEQ_RHS,
  ExprBoolNot_Arg,
  ExprBoolAnd_Args,
  ExprBoolOr_Args,
  ExprBoolImplies_Args,
  ExprAddAssign_LHS,
  ExprAddAssign_RHS,
  ExprSubAssign_LHS,
  ExprSubAssign_RHS,
  ExprMulAssign_LHS,
  ExprMulAssign_RHS,
  ExprExpAssign_LHS,
  ExprExpAssign_RHS,
  ExprDivAssign_LHS,
  ExprDivAssign_RHS,
  ExprDivIntAssign_LHS,
  ExprDivIntAssign_RHS,
  ExprDivRealAssign_LHS,
  ExprDivRealAssign_RHS,
  ExprModAssign_LHS,
  ExprModAssign_RHS,
  ExprBitAndAssign_LHS,
  ExprBitAndAssign_RHS,
  ExprBitOrAssign_LHS,
  ExprBitOrAssign_RHS,
  ExprBitXorAssign_LHS,
  ExprBitXorAssign_RHS,
  ExprBitShLAssign_LHS,
  ExprBitShLAssign_RHS,
  ExprBitShRAssign_LHS,
  ExprBitShRAssign_RHS,
  ExprAssign_LHS,
  ExprAssign_RHS,
  StmtExpr_Expr,
  StmtDecl_Decl,
  StmtReturn_Arg,
  StmtContinue_Name,
  StmtBreak_Name,
  StmtIf_Condition,
  StmtIf_Then,
  StmtIf_Else,
  StmtWhile_Condition,
  StmtWhile_Body,
  StmtWhile_Name,
  StmtFor_Decls,
  StmtFor_Condition,
  StmtFor_Steps,
  StmtFor_Body,
  StmtFor_Name,
  StmtForEach_Decl,
  StmtForEach_Sequence,
  StmtForEach_Body,
  StmtForEach_Name,
  StmtBlock_Stmts,
  StmtBlock_Scope,
  DeclVariable_Type,
  DeclVariable_TemplateDeclArgs,
  DeclVariable_Initial,
  DeclFunction_Return,
  DeclFunction_TemplateDeclArgs,
  DeclFunction_Args,
  DeclFunction_Body,
  DeclFunction_Scope,
  DeclClass_TemplateDeclArgs,
  DeclClass_Inherits,
  DeclClass_Members,
  DeclClass_Scope,
  DeclNamespace_Members,
  DeclNamespace_Scope,
  Import_Path,
  Unit_Members,
  Unit_Scope
};

std::ostream &operator<<(std::ostream &os, FieldTag value);

enum class FieldFormat {
  Int,
  UInt,
  Real,
  String,
  Node,
  NodeVector,
  Scope
};

std::ostream &operator<<(std::ostream &os, FieldFormat value);

class Field;

class FieldTagInfo {
private:
  std::string name;
  std::vector<std::unique_ptr<Field>>::size_type index;

public:
  static const FieldTagInfo &get(FieldTag fieldTag);

  FieldTagInfo(std::string name, std::vector<std::unique_ptr<Field>>::size_type index);

  const std::string &getName() const;
  std::vector<std::unique_ptr<Field>>::size_type getIndex() const;
};
}

#endif
