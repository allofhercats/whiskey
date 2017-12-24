#ifndef __WHISKEY_AST_ExprLiteralFloat_HPP
#define __WHISKEY_AST_ExprLiteralFloat_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/ExprLiteral.hpp>

namespace whiskey {
class ExprLiteralFloat : public ExprLiteral<long double> {
protected:
	virtual AST *onClone() const;

public:
	ExprLiteralFloat(Container<Type> type, long double value);
	ExprLiteralFloat(Range range, Container<Type> type, long double value);
};
}

#endif
