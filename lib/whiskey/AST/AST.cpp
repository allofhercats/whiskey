#include "Module.inc"

#include <whiskey/AST/AST.hpp>

namespace whiskey {
bool AST::isType(ID id) {
  return isTypeAtomic(id) || isTypeSymbol(id) || isTypeUnary(id) ||
         isTypeBinary(id) || isTypeFunction(id);
}

bool AST::isTypeAtomic(ID id) {
  return id == AST::ID::TypeAtomicInt8 || id == AST::ID::TypeAtomicInt16 ||
         id == AST::ID::TypeAtomicInt32 || id == AST::ID::TypeAtomicInt64 ||
         id == AST::ID::TypeAtomicUInt8 || id == AST::ID::TypeAtomicUInt16 ||
         id == AST::ID::TypeAtomicUInt32 || id == AST::ID::TypeAtomicUInt64 ||
         id == AST::ID::TypeAtomicFloat32 || id == AST::ID::TypeAtomicFloat64 ||
         id == AST::ID::TypeAtomicReal;
}

bool AST::isTypeSymbol(ID id) {
  return id == AST::ID::TypeSymbol;
}

bool AST::isTypeUnary(ID id) {
  return id == AST::ID::TypeAccessUnary;
}

bool AST::isTypeBinary(ID id) {
  return id == AST::ID::TypeAccessBinary;
}

bool AST::isTypeFunction(ID id) {
  return id == AST::ID::TypeFunction;
}

bool AST::isExpr(ID id) {
  return isExprLiteralInt(id) || isExprLiteralFloat(id) || isExprSymbol(id) ||
         isExprUnary(id) || isExprBinary(id) || isExprCall(id);
}

bool AST::isExprLiteralInt(ID id) {
  return id == AST::ID::ExprLiteralInt;
}

bool AST::isExprLiteralFloat(ID id) {
  return id == AST::ID::ExprLiteralFloat;
}

bool AST::isExprSymbol(ID id) {
  return id == AST::ID::ExprSymbol;
}

bool AST::isExprUnary(ID id) {
  return id == AST::ID::ExprAccessUnary || id == AST::ID::ExprIncPre ||
         id == AST::ID::ExprIncPost || id == AST::ID::ExprDecPre ||
         id == AST::ID::ExprDecPost || id == AST::ID::ExprNegate ||
         id == AST::ID::ExprBitNot || id == AST::ID::ExprBoolNot;
}

bool AST::isExprBinary(ID id) {
  return id == AST::ID::ExprAccessBinary || id == AST::ID::ExprExp ||
         id == AST::ID::ExprMul || id == AST::ID::ExprDiv ||
         id == AST::ID::ExprDivInt || id == AST::ID::ExprDivReal ||
         id == AST::ID::ExprAdd || id == AST::ID::ExprSub ||
         id == AST::ID::ExprMod || id == AST::ID::ExprBitShR ||
         id == AST::ID::ExprBitShL || id == AST::ID::ExprBitAnd ||
         id == AST::ID::ExprBitOr || id == AST::ID::ExprBitXor ||
         id == AST::ID::ExprLT || id == AST::ID::ExprLE ||
         id == AST::ID::ExprGT || id == AST::ID::ExprGE ||
         id == AST::ID::ExprNE || id == AST::ID::ExprEQ ||
         id == AST::ID::ExprBoolAnd || id == AST::ID::ExprBoolOr ||
         id == AST::ID::ExprBoolImplies;
}

bool AST::isExprCall(ID id) {
  return id == AST::ID::ExprCall;
}

bool AST::isStmt(ID id) {
  return isStmtEmpty(id) || isStmtExpr(id) || isStmtIf(id) || isStmtWhile(id) ||
         isStmtFor(id) || isStmtForEach(id) || isStmtBlock(id);
}

bool AST::isStmtEmpty(ID id) {
  return id == AST::ID::StmtEmpty;
}

bool AST::isStmtExpr(ID id) {
  return id == AST::ID::StmtExpr || id == AST::ID::StmtReturn;
}

bool AST::isStmtIf(ID id) {
  return id == AST::ID::StmtIf;
}

bool AST::isStmtWhile(ID id) {
  return id == AST::ID::StmtWhile;
}

bool AST::isStmtFor(ID id) {
  return id == AST::ID::StmtFor;
}

bool AST::isStmtForEach(ID id) {
  return id == AST::ID::StmtForEach;
}

bool AST::isStmtBlock(ID id) {
  return id == AST::ID::StmtBlock;
}

bool AST::isDecl(ID id) {
  return isDeclVariable(id) || isDeclFunction(id) || isDeclClass(id) ||
         isDeclNamespace(id);
}

bool AST::isDeclVariable(ID id) {
  return id == AST::ID::DeclVariable;
}

bool AST::isDeclFunction(ID id) {
  return id == AST::ID::DeclFunction;
}

bool AST::isDeclClass(ID id) {
  return id == AST::ID::DeclClass;
}

bool AST::isDeclNamespace(ID id) {
  return id == AST::ID::DeclNamespace;
}

bool AST::isImport(ID id) {
  return id == AST::ID::Import;
}

AST::AST(AST::ID id, Range range) : id(id), range(range) {
}

AST::ID AST::getID() const {
  return id;
}

const Range &AST::getRange() const {
  return range;
}

void AST::setRange(Range value) {
  range = value;
}

bool AST::compare(const AST &other) const {
  if (id != other.id) {
    return false;
  } else {
    return onCompare(other);
  }
}

std::queue<ContainerRef<AST>> AST::getChildren() {
  std::queue<ContainerRef<AST>> rtn;
  onGetChildren(rtn);
  return rtn;
}
} // namespace whiskey
