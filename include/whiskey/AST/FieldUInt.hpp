#ifndef __WHISKEY_AST_FieldUInt_HPP
#define __WHISKEY_AST_FieldUInt_HPP

#include <whiskey/AST/Field.hpp>

namespace whiskey {
class FieldUInt : public Field {
private:
	UInt64 value;

protected:
	void onPrintAsLiteral(std::ostream &os) const;
  bool onCompare(const Field &other) const;
  void onPrint(std::ostream &os, int indent) const;

public:
	FieldUInt(UInt64 value);

	UInt64 &getValue();
	const UInt64 &getValue() const;
  void setValue(UInt64 value);
};
}

#endif
