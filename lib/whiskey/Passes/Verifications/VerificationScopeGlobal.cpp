#include <whiskey/Passes/Verifications/VerificationScopeGlobal.hpp>

#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/Scope.hpp>

namespace whiskey {
PassResult VerificationScopeGlobal::onRunPre(Node &node, MessageContext &msgs) {
	if (node.getType() == NodeType::DeclFunction) {
		node.setFieldScope(FieldTag::DeclFunction_Scope);
		node.getFieldScope(FieldTag::DeclFunction_Scope).declare(stripNonScopeDeclFunction(node));
		for (const Node &i : node.getFieldNodeVector(FieldTag::DeclFunction_Args)) {
			if (i.getType() == NodeType::DeclVariable) {
				node.getFieldScope(FieldTag::DeclFunction_Scope).declare(stripNonScopeDeclVariable(i));
			}
		}

		return PassResult::Block;
	} else if (node.getType() == NodeType::DeclClass) {
		node.setFieldScope(FieldTag::DeclClass_Scope);
		node.getFieldScope(FieldTag::DeclClass_Scope).declare(stripNonScopeDeclClass(node));
		for (const Node &i : node.getFieldNodeVector(FieldTag::DeclClass_Members)) {
			if (i.getType() == NodeType::DeclVariable) {
				node.getFieldScope(FieldTag::DeclClass_Scope).declare(stripNonScopeDeclVariable(i));
			} else if (i.getType() == NodeType::DeclFunction) {
				node.getFieldScope(FieldTag::DeclClass_Scope).declare(stripNonScopeDeclFunction(i));
			} else if (i.getType() == NodeType::DeclClass) {
				node.getFieldScope(FieldTag::DeclClass_Scope).declare(stripNonScopeDeclClass(i));
			} else if (i.getType() == NodeType::DeclNamespace) {
				node.getFieldScope(FieldTag::DeclClass_Scope).declare(stripNonScopeDeclNamespace(i));
			}
		}

		return PassResult::Block;
	} else if (node.getType() == NodeType::DeclNamespace) {
		node.setFieldScope(FieldTag::DeclNamespace_Scope);
		node.getFieldScope(FieldTag::DeclNamespace_Scope).declare(stripNonScopeDeclNamespace(node));
		for (const Node &i : node.getFieldNodeVector(FieldTag::DeclClass_Members)) {
			if (i.getType() == NodeType::DeclVariable) {
				node.getFieldScope(FieldTag::DeclNamespace_Scope).declare(stripNonScopeDeclVariable(i));
			} else if (i.getType() == NodeType::DeclFunction) {
				node.getFieldScope(FieldTag::DeclNamespace_Scope).declare(stripNonScopeDeclFunction(i));
			} else if (i.getType() == NodeType::DeclClass) {
				node.getFieldScope(FieldTag::DeclNamespace_Scope).declare(stripNonScopeDeclClass(i));
			} else if (i.getType() == NodeType::DeclNamespace) {
				node.getFieldScope(FieldTag::DeclNamespace_Scope).declare(stripNonScopeDeclNamespace(i));
			}
		}

		return PassResult::Block;
	} else if (node.getType() == NodeType::Unit) {
		node.setFieldScope(FieldTag::Unit_Scope);
		node.getFieldScope(FieldTag::Unit_Scope).declare(stripNonScopeUnit(node));
		for (const Node &i : node.getFieldNodeVector(FieldTag::Unit_Members)) {
			if (i.getType() == NodeType::DeclVariable) {
				node.getFieldScope(FieldTag::Unit_Scope).declare(stripNonScopeDeclVariable(i));
			} else if (i.getType() == NodeType::DeclFunction) {
				node.getFieldScope(FieldTag::Unit_Scope).declare(stripNonScopeDeclFunction(i));
			} else if (i.getType() == NodeType::DeclClass) {
				node.getFieldScope(FieldTag::Unit_Scope).declare(stripNonScopeDeclClass(i));
			} else if (i.getType() == NodeType::DeclNamespace) {
				node.getFieldScope(FieldTag::Unit_Scope).declare(stripNonScopeDeclNamespace(i));
			}
		}

		return PassResult::Block;
	}

	return PassResult::Good;
}

PassResult VerificationScopeGlobal::onRunPost(Node &node, MessageContext &msgs) {
	return PassResult::Good;	
}

VerificationScopeGlobal::VerificationScopeGlobal() : VerificationScope("VerificationScopeGlobal", {}) {}
}
