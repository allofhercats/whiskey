#ifndef __WHISKEY_AST_FieldNodeVector_HPP
#define __WHISKEY_AST_FieldNodeVector_HPP

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/Node.hpp>

namespace whiskey {
class FieldNodeVector : public Field {
private:
	std::vector<Node> value;

protected:
	bool onCompare(const Field &other) const;
	void onPrint(std::ostream &os, int indent) const;

public:
	FieldNodeVector(std::vector<Node> value = {});

	std::vector<Node> &getValue();
	const std::vector<Node> &getValue() const;
};
}

#endif
