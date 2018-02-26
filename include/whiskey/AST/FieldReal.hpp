#ifndef __WHISKEY_AST_FieldReal_HPP
#define __WHISKEY_AST_FieldReal_HPP

#include <whiskey/AST/Field.hpp>

namespace whiskey {
class FieldReal : public Field {
private:
	Real value;

protected:
	void onPrintAsLiteral(std::ostream &os) const;
  bool onCompare(const Field &other) const;
  void onPrint(std::ostream &os, int indent) const;

public:
	FieldReal(Real value);

	Real getValue() const;
  void setValue(Real value);
};
}

#endif
