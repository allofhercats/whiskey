#ifndef __WHISKEY_AST_TypeLiteral_HPP
#define __WHISKEY_AST_TypeLiteral_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>

namespace whiskey {
template<typename ValueType>
class TypeLiteral : public Type {
private:
	ValueType value;

protected:
	bool onCompare(const AST &other) const;

	virtual bool onCompareTypeLiteral(const TypeLiteral &other) const;

public:
	TypeLiteral(AST::ID id, Range range, ValueType value);

	ValueType &getValue();
	const ValueType &getValue() const;
	void setValue(ValueType value);
};
}

#include <whiskey/AST/TypeLiteral.tpp>

#endif
