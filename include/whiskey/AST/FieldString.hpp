#ifndef __WHISKEY_AST_FieldString_HPP
#define __WHISKEY_AST_FieldString_HPP

#include <whiskey/AST/Field.hpp>

namespace whiskey {
class FieldString : public Field {
private:
	std::string value;

protected:
	std::unique_ptr<Field> onClone() const;
	void onPrintAsLiteral(std::ostream &os) const;
  bool onCompare(const Field &other) const;
  void onPrint(std::ostream &os, int indent) const;

public:
	FieldString(std::string value);

	std::string &getValue();
	const std::string &getValue() const;
  void setValue(std::string value);
};
}

#endif
