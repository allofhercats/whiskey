#ifndef __WHISKEY_AST_DeclVariable_HPP
#define __WHISKEY_AST_DeclVariable_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>
#include <whiskey/AST/Expr.hpp>
#include <whiskey/AST/Decl.hpp>

namespace whiskey {
class DeclVariable : public Decl {
private:
	Container<Type> type;
	Container<Expr> init;

protected:
	AST *onClone() const;
	bool onCompareDecl(const Decl &other) const;

	virtual bool onCompareDeclVariable(const DeclVariable &other) const;

public:
	DeclVariable(Container<Type> type, std::string name, Container<Expr> init = nullptr);
	DeclVariable(Range range, Container<Type> type, std::string name, Container<Expr> init = nullptr);

	Ref<Type> getType();
	CRef<Type> getType() const;
	void setType(Container<Type> value);

	Ref<Expr> getInit();
	CRef<Expr> getInit() const;
	void setInit(Container<Expr> value);
};
}

#endif
