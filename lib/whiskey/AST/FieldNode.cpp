#include <whiskey/AST/FieldNode.hpp>

#include <whiskey/Core/Literals.hpp>

namespace whiskey {
bool FieldNode::onCompare(const Field &other) const {
	return value == static_cast<const FieldNode &>(other).value;
}

void FieldNode::onPrint(std::ostream &os, int indent) const {
	value.print(os, indent);
}

FieldNode::FieldNode(Node value) : Field(FieldFormat::Node), value(value) {}

Node &FieldNode::getValue() {
	return value;
}

const Node &FieldNode::getValue() const {
	return value;
}

void FieldNode::setValue(Node value) {
	this->value = value;
}
}
