#ifndef __WHISKEY_AST_FieldTag_HPP
#define __WHISKEY_AST_FieldTag_HPP

#include <memory>
#include <string>
#include <vector>

namespace whiskey {
enum class FieldTag {
  List_Children,
  TypeSymbol_Name,
  TypeSymbol_TemplateEvalArgs,
  TypeAccessUnary_Arg,
  TypeAccess_Args,
  TypeGroup_Arg,
  TypeFunction_Return,
  TypeFunction_Args,
  ExprLiteralUInt_Type,
  ExprLiteralUInt_Value,
  ExprLiteralReal_Type,
  ExprLiteralReal_Value,
  ExprSymbol_Name,
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
  StmtWhile_Name,
  StmtWhile_Condition,
  StmtWhile_Body,
  StmtFor_Name,
  StmtFor_Decls,
  StmtFor_Condition,
  StmtFor_Steps,
  StmtFor_Body,
  StmtForEach_Name,
  StmtForEach_Decls,
  StmtForEach_Sequences,
  StmtForEach_Body,
  StmtBlock_Stmts,
  DeclVariable_Type,
  DeclVariable_Name,
  DeclVariable_TemplateDeclArgs,
  DeclVariable_Initial,
  DeclFunction_Return,
  DeclFunction_Name,
  DeclFunction_TemplateDeclArgs,
  DeclFunction_Args,
  DeclFunction_Body,
  DeclClass_Name,
  DeclClass_TemplateDeclArgs,
  DeclClass_Inherits,
  DeclClass_Members,
  DeclNamespace_Name,
  DeclNamespace_Members,
  Import_Path,
  Unit_Members
};

enum class FieldFormat {
  Int,
  UInt,
  Real,
  String,
  Node,
  NodeVector
};

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
