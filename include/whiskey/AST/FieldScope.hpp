#ifndef __WHISKEY_AST_FieldScope_HPP
#define __WHISKEY_AST_FieldScope_HPP

#include <whiskey/AST/Scope.hpp>
#include <whiskey/AST/Field.hpp>

namespace whiskey {
class FieldScope : public Field {
private:
	std::unique_ptr<Scope> value;

protected:
	std::unique_ptr<Field> onClone() const;
	bool onCompare(const Field &other) const;
	void onPrint(std::ostream &os, int indent) const;

public:
	FieldScope();

	Scope &getValue();
	const Scope &getValue() const;
};
}

#endif
