#include <whiskey/AST/FieldNodeVector.hpp>

#include <whiskey/Core/Literals.hpp>

namespace whiskey {
bool FieldNodeVector::onCompare(const Field &other) const {
	return value == static_cast<const FieldNodeVector &>(other).value;
}

void FieldNodeVector::onPrint(std::ostream &os, int indent) const {
	int n = 0;
	for (const Node &i : value) {
		if (n > 0) {
			os << '\n';
			for (int j = 0; j < indent+2; j++) {
				os << ' ';
			}
		}

		os << "[" << (n++) << "] ";
		i.print(os, indent+2);
	}
}

FieldNodeVector::FieldNodeVector(std::vector<Node> value) : Field(FieldFormat::NodeVector), value(value) {}

std::vector<Node> &FieldNodeVector::getValue() {
	return value;
}

const std::vector<Node> &FieldNodeVector::getValue() const {
	return value;
}
}
