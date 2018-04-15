#include <whiskey/Passes/Verifications/VerificationScope.hpp>

#include <whiskey/AST/Node.hpp>

namespace whiskey {
Node VerificationScope::stripNonScopeDeclVariable(Node value) {
	W_ASSERT_EQ(value.getType(), NodeType::DeclVariable, "Node must be of expected type.");

	value.removeField(FieldTag::DeclVariable_Initial);
	return value;
}

Node VerificationScope::stripNonScopeDeclFunction(Node value) {
	W_ASSERT_EQ(value.getType(), NodeType::DeclFunction, "Node must be of expected type.");

	value.removeField(FieldTag::DeclFunction_Args);
	value.removeField(FieldTag::DeclFunction_Body);
	return value;
}

Node VerificationScope::stripNonScopeDeclClass(Node value) {
	W_ASSERT_EQ(value.getType(), NodeType::DeclClass, "Node must be of expected type.");

	value.removeField(FieldTag::DeclClass_Scope);
	value.removeField(FieldTag::DeclClass_Members);

	return value;
}

Node VerificationScope::stripNonScopeDeclNamespace(Node value) {
	W_ASSERT_EQ(value.getType(), NodeType::DeclNamespace, "Node must be of expected type.");

	value.removeField(FieldTag::DeclNamespace_Members);
	value.removeField(FieldTag::DeclNamespace_Scope);

	return value;
}

Node VerificationScope::stripNonScopeUnit(Node value) {
	W_ASSERT_EQ(value.getType(), NodeType::DeclNamespace, "Node must be of expected type.");

	value.removeField(FieldTag::DeclNamespace_Members);
	value.removeField(FieldTag::DeclNamespace_Scope);

	return value;
}

VerificationScope::VerificationScope(std::string name, std::initializer_list<std::string> dependencies) : Pass(name, dependencies) {}

VerificationScope::~VerificationScope() {}
}
