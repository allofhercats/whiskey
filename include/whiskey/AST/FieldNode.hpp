#ifndef __WHISKEY_AST_FieldNode_HPP
#define __WHISKEY_AST_FieldNode_HPP

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/Node.hpp>

namespace whiskey {
class FieldNode : public Field {
private:
	Node value;

protected:
	std::unique_ptr<Field> onClone() const;
	bool onCompare(const Field &other) const;
	void onPrint(std::ostream &os, int indent) const;

public:
	FieldNode(Node value);

	Node &getValue();
	const Node &getValue() const;
  void setValue(Node value);
};
}

#endif
