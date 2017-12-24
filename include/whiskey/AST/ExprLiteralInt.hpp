#ifndef __WHISKEY_AST_ExprLiteralInt_HPP
#define __WHISKEY_AST_ExprLiteralInt_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/ExprLiteral.hpp>

namespace whiskey {
class ExprLiteralInt : public ExprLiteral<int64_t> {
protected:
	virtual AST *onClone() const;

public:
	ExprLiteralInt(Container<Type> type, int64_t value);
	ExprLiteralInt(Range range, Container<Type> type, int64_t value);
};
}

#endif
