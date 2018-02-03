#ifndef __WHISKEY_AST_Node_HPP
#define __WHISKEY_AST_Node_HPP

#include <vector>

#include <whiskey/AST/Field.hpp>
#include <whiskey/Source/Token.hpp>

namespace whiskey {
class Node {
public:
  enum class Kind {
    TypeAtomicBool,
    TypeAtomicInt8,
    TypeAtomicInt16,
    TypeAtomicInt32,
    TypeAtomicInt64,
    TypeAtomicUInt8,
    TypeAtomicUInt16,
    TypeAtomicUInt32,
    TypeAtomicUInt64,
    TypeAtomicFloat32,
    TypeAtomicFloat64,
    TypeAtomicReal,
    TypeSymbol,
    TypeAccessUnary,
    TypeAccess,
    TypeGroup,
    TypeFunction,
    ExprLiteralUInt,
    ExprLiteralReal,
    ExprSymbol,
    ExprAccessUnary,
    ExprAccess,
    ExprGroup,
    ExprCall,
    ExprAdd,
    ExprIncPre,
    ExprIncPost,
    ExprSub,
    ExprNeg,
    ExprDecPre,
    ExprDecPost,
    ExprMul,
    ExprExp,
    ExprDiv,
    ExprDivInt,
    ExprDivReal,
    ExprMod,
    ExprBitNot,
    ExprBitAnd,
    ExprBitOr,
    ExprBitXor,
    ExprBitShL,
    ExprBitShR,
    ExprLT,
    ExprLE,
    ExprGT,
    ExprGE,
    ExprNE,
    ExprEQ,
    ExprBoolNot,
    ExprBoolAnd,
    ExprBoolOr,
    ExprBoolImplies,
    ExprAddAssign,
    ExprSubAssign,
    ExprMulAssign,
    ExprExpAssign,
    ExprDivAssign,
    ExprDivIntAssign,
    ExprDivRealAssign,
    ExprModAssign,
    ExprBitAndAssign,
    ExprBitOrAssign,
    ExprBitXorAssign,
    ExprBitShLAssign,
    ExprBitShRAssign,
    ExprAssign,
    StmtEmpty,
    StmtExpr,
    StmtDecl,
    StmtReturn,
    StmtContinue,
    StmtBreak,
    StmtIf,
    StmtWhile,
    StmtFor,
    StmtForEach,
    StmtBlock,
    DeclVariable,
    DeclFunction,
    DeclClass,
    DeclNamespace,
    Import,
    Unit
  };

  enum class FieldTag {
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
    StmtWhile_Condition,
    StmtWhile_Body,
    StmtFor_Decls,
    StmtFor_Condition,
    StmtFor_Steps,
    StmtFor_Body,
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

  class KindInfo {
  public:
    typedef uint32_t Flags;

    const static Flags maskCategory = 0x7;
    const static Flags valueCategoryType = 0x0;
    const static Flags valueCategoryExpr = 0x1;
    const static Flags valueCategoryStmt = 0x2;
    const static Flags valueCategoryDecl = 0x3;
    const static Flags valueCategoryOther = 0x4;

  private:
    const char *name;
    std::vector<Node::FieldTag> fieldTags;
    Flags flags;

  public:
    KindInfo(const char *name, std::vector<FieldTag> fieldTags, Flags flags);

    const char *getName() const;
    unsigned int getNFields() const;
    FieldTag getFieldTag(int index) const;

    bool isType() const;
    bool isExpr() const;
    bool isStmt() const;
    bool isDecl() const;
    bool isOther() const;
  };

  class FieldTagInfo {
  private:
    unsigned int index;
    const char *name;
    bool _isExpectingKind;
    Field::Kind expectedKind;
    bool _isExpectingList;

  public:
    FieldTagInfo(unsigned int index, const char *name);
    FieldTagInfo(unsigned int index,
                 const char *name,
                 Field::Kind expectedKind,
                 bool isExpectingList = false);

    unsigned int getIndex() const;
    const char *getName() const;
    bool isExpectingKind() const;
    Field::Kind getExpectedKind() const;
    bool isExpectingList() const;
  };

  static FieldTagInfo getFieldTagInfo(FieldTag value);

  static KindInfo getKindInfo(Kind value);

private:
  Token token;
  Kind kind;
  Field **fields;
  Node *next;

  Node(Kind kind, std::initializer_list<Field *> fields, Token token);

public:
  Node(const Node &) = delete;
  ~Node();

  static Node *createTypeAtomicBool(Token token = Token());
  static Node *createTypeAtomicInt8(Token token = Token());
  static Node *createTypeAtomicInt16(Token token = Token());
  static Node *createTypeAtomicInt32(Token token = Token());
  static Node *createTypeAtomicInt64(Token token = Token());
  static Node *createTypeAtomicUInt8(Token token = Token());
  static Node *createTypeAtomicUInt16(Token token = Token());
  static Node *createTypeAtomicUInt32(Token token = Token());
  static Node *createTypeAtomicUInt64(Token token = Token());
  static Node *createTypeAtomicFloat32(Token token = Token());
  static Node *createTypeAtomicFloat64(Token token = Token());
  static Node *createTypeAtomicReal(Token token = Token());
  static Node *createTypeSymbol(Field *name, Token token = Token());
  static Node *createTypeSymbol(Field *name,
                                std::initializer_list<Node *> templateEvalArgs,
                                Token token = Token());
  static Node *createTypeAccessUnary(Node *arg, Token token = Token());
  static Node *createTypeAccess(std::initializer_list<Node *> args,
                                Token token = Token());
  static Node *createTypeGroup(Node *arg, Token token = Token());
  static Node *createTypeFunction(Node *ret,
                                  std::initializer_list<Node *> args,
                                  Token token = Token());
  static Node *
  createExprLiteralUInt(Node *type, UInt64 value, Token token = Token());
  static Node *
  createExprLiteralReal(Node *type, Real value, Token token = Token());
  static Node *createExprSymbol(Field *name, Token token = Token());
  static Node *createExprSymbol(Field *name,
                                std::initializer_list<Node *> templateEvalArgs,
                                Token token = Token());
  static Node *createExprAccessUnary(Node *arg, Token token = Token());
  static Node *createExprAccess(std::initializer_list<Node *> args,
                                Token token = Token());
  static Node *createExprGroup(Node *arg, Token token = Token());
  static Node *createExprCall(Node *callee,
                              std::initializer_list<Node *> args,
                              Token token = Token());
  static Node *createExprAdd(std::initializer_list<Node *> args,
                             Token token = Token());
  static Node *createExprIncPre(Node *arg, Token token = Token());
  static Node *createExprIncPost(Node *arg, Token token = Token());
  static Node *createExprSub(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprNeg(Node *arg, Token token = Token());
  static Node *createExprDecPre(Node *arg, Token token = Token());
  static Node *createExprDecPost(Node *arg, Token token = Token());
  static Node *createExprMul(std::initializer_list<Node *> args,
                             Token token = Token());
  static Node *createExprExp(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprDiv(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprDivInt(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprDivReal(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprMod(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprBitNot(Node *arg, Token token = Token());
  static Node *createExprBitAnd(std::initializer_list<Node *> args,
                                Token token = Token());
  static Node *createExprBitOr(std::initializer_list<Node *> args,
                               Token token = Token());
  static Node *createExprBitXor(std::initializer_list<Node *> args,
                                Token token = Token());
  static Node *createExprBitShL(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprBitShR(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprLT(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprLE(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprGT(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprGE(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprNE(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprEQ(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprBoolNot(Node *arg, Token token = Token());
  static Node *createExprBoolAnd(std::initializer_list<Node *> args,
                                 Token token = Token());
  static Node *createExprBoolOr(std::initializer_list<Node *> args,
                                Token token = Token());
  static Node *createExprBoolImplies(std::initializer_list<Node *> args,
                                     Token token = Token());
  static Node *createExprAddAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprSubAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprMulAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprExpAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprDivAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *
  createExprDivIntAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *
  createExprDivRealAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprModAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *
  createExprBitAndAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *
  createExprBitOrAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *
  createExprBitXorAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *
  createExprBitShLAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *
  createExprBitShRAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *createExprAssign(Node *lhs, Node *rhs, Token token = Token());
  static Node *createStmtEmpty(Token token = Token());
  static Node *createStmtExpr(Node *expr, Token token = Token());
  static Node *createStmtDecl(Node *decl, Token token = Token());
  static Node *createStmtReturn(Node *arg, Token token = Token());
  static Node *createStmtContinue(Token token = Token());
  static Node *createStmtContinue(Field *name, Token token = Token());
  static Node *createStmtBreak(Token token = Token());
  static Node *createStmtBreak(Field *name, Token token = Token());
  static Node *createStmtIf(Node *condition, Node *then, Token token = Token());
  static Node *
  createStmtIf(Node *condition, Node *then, Node *_else, Token token = Token());
  static Node *createStmtWhile(Node *condition, Token token = Token());
  static Node *
  createStmtWhile(Node *condition, Node *body, Token token = Token());
  static Node *createStmtFor(std::initializer_list<Node *> decls,
                             Node *condition,
                             std::initializer_list<Node *> steps,
                             Token token = Token());
  static Node *createStmtFor(std::initializer_list<Node *> decls,
                             Node *condition,
                             std::initializer_list<Node *> steps,
                             Node *body,
                             Token token = Token());
  static Node *createStmtForEach(std::initializer_list<Node *> decls,
                                 std::initializer_list<Node *> sequences,
                                 Token token = Token());
  static Node *createStmtForEach(std::initializer_list<Node *> decls,
                                 std::initializer_list<Node *> sequences,
                                 Node *body,
                                 Token token = Token());
  static Node *createStmtBlock(Token token = Token());
  static Node *createStmtBlock(std::initializer_list<Node *> stmts,
                               Token token = Token());
  static Node *
  createDeclVariable(Node *type, Field *name, Token token = Token());
  static Node *createDeclVariable(Node *type,
                                  Field *name,
                                  Node *initial,
                                  Token token = Token());
  static Node *
  createDeclVariable(Node *type,
                     Field *name,
                     std::initializer_list<Node *> templateDeclArgs,
                     Token token = Token());
  static Node *
  createDeclVariable(Node *type,
                     Field *name,
                     std::initializer_list<Node *> templateDeclArgs,
                     Node *initial,
                     Token token = Token());
  static Node *createDeclFunction(Node *ret,
                                  Field *name,
                                  std::initializer_list<Node *> args,
                                  Token token = Token());
  static Node *
  createDeclFunction(Node *ret,
                     Field *name,
                     std::initializer_list<Node *> templateDeclArgs,
                     std::initializer_list<Node *> args,
                     Token token = Token());
  static Node *createDeclFunction(Node *ret,
                                  Field *name,
                                  std::initializer_list<Node *> args,
                                  Node *body,
                                  Token token = Token());
  static Node *
  createDeclFunction(Node *ret,
                     Field *name,
                     std::initializer_list<Node *> templateDeclArgs,
                     std::initializer_list<Node *> args,
                     Node *body,
                     Token token = Token());
  static Node *createDeclClass(Field *name, Token token = Token());
  static Node *createDeclClass(Field *name,
                               std::initializer_list<Node *> members,
                               Token token = Token());
  static Node *createDeclClass(Field *name,
                               std::initializer_list<Node *> inherits,
                               std::initializer_list<Node *> members,
                               Token token = Token());
  static Node *createDeclClass(Field *name,
                               std::initializer_list<Node *> templateDeclArgs,
                               std::initializer_list<Node *> inherits,
                               std::initializer_list<Node *> members,
                               Token token = Token());
  static Node *createDeclNamespace(Field *name, Token token = Token());
  static Node *createDeclNamespace(Field *name,
                                   std::initializer_list<Node *> members,
                                   Token token = Token());
  static Node *createImport(Field *path, Token token = Token());
  static Node *createUnit();
  static Node *createUnit(std::initializer_list<Node *> members);

  Node *clone() const;

  const Token &getToken() const;
  void setToken(Token value);

  Kind getKind() const;

  Field *getField(FieldTag tag);
  Field *getField(int index);
  const Field *getField(FieldTag tag) const;
  const Field *getField(int index) const;

  Node *getNext();
  const Node *getNext() const;
  void setNext(Node *value);

  bool compare(const Node *other) const;
};
} // namespace whiskey

#endif
