#ifndef __WHISKEY_AST_Stmt_HPP
#define __WHISKEY_AST_Stmt_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Stmt : public AST {
public:
	Stmt(AST::ID id, Range range);
};
}

#endif
