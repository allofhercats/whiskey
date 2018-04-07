#ifndef __WHISKEY_AST_Predicates_HPP
#define __WHISKEY_AST_Predicates_HPP

#include <whiskey/AST/NodeType.hpp>

namespace whiskey {
enum class Arity {
	Unary,
	Binary,
	NAry
};

bool isAtomicType(NodeType type);
bool isLiteralExpr(NodeType type);
bool isOpExpr(NodeType type);
Arity getExprArity(NodeType type);
}

#endif
