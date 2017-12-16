#include "Module.inc"

#include <whiskey/AST/Type.hpp>

namespace whiskey {
Type::Type(AST::ID id, Range range) : AST(id, range) {}
}
