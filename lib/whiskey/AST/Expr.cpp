#include "Module.inc"

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
Expr::Expr(AST::ID id, Range range) : AST(id, range) {}
}
