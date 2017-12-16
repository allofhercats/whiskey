#ifndef __WHISKEY_AST_Type_HPP
#define __WHISKEY_AST_Type_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Type : public AST {
public:
	Type(AST::ID id, Range range);
};
}

#endif
