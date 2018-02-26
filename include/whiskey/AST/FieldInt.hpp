#ifndef __WHISKEY_AST_FieldInt_HPP
#define __WHISKEY_AST_FieldInt_HPP

#include <whiskey/AST/Field.hpp>

namespace whiskey {
class FieldInt : public Field {
private:
	Int64 value;

protected:
	void onPrintAsLiteral(std::ostream &os) const;
  bool onCompare(const Field &other) const;
  void onPrint(std::ostream &os, int indent) const;

public:
	FieldInt(Int64 value);

	Int64 getValue() const;
  void setValue(Int64 value);
};
}

#endif
