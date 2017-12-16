#ifndef __WHISKEY_AST_TypeBinary_HPP
#define __WHISKEY_AST_TypeBinary_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>

namespace whiskey {
class TypeBinary : public Type {
private:
	Container<Type> lhs;
	Container<Type> rhs;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareTypeBinary(const TypeBinary &other) const;

public:
	TypeBinary(AST::ID id, Container<Type> lhs, Container<Type> rhs);
	TypeBinary(AST::ID id, Range range, Container<Type> lhs, Container<Type> rhs);

	Ref<Type> getLHS();
	CRef<Type> getLHS() const;
	void setLHS(Container<Type> value);

	Ref<Type> getRHS();
	CRef<Type> getRHS() const;
	void setRHS(Container<Type> value);
};
}

#endif
