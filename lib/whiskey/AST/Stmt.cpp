#include "Module.inc"

#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
Stmt::Stmt(AST::ID id, Range range) : AST(id, range) {}
}
