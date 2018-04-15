#include <whiskey/CodeGen/Generator.hpp>

#include <whiskey/AST/Node.hpp>

namespace whiskey {
Generator::Generator() {}

Generator::~Generator() {}

void Generator::generateUnit(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::Unit, "Unit node must be of type 'Unit'.");
	W_ASSERT_TRUE(node.hasField(FieldTag::Unit_Members), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::Unit_Members).getFormat(), FieldFormat::NodeVector, "Field of unexpected format.");

	onGenerateUnit(node);
}
}
