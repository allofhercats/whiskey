#ifndef __WHISKEY_AST_Expr_HPP
#define __WHISKEY_AST_Expr_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Expr : public AST {
public:
	Expr(AST::ID id, Range range);
};
}

#endif
