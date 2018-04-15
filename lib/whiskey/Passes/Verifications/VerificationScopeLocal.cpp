#include <whiskey/Passes/Verifications/VerificationScopeLocal.hpp>

#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/Scope.hpp>

namespace whiskey {
PassResult VerificationScopeLocal::onRunPre(Node &node, MessageContext &msgs) {
	return PassResult::Good;
}

PassResult VerificationScopeLocal::onRunPost(Node &node, MessageContext &msgs) {
	return PassResult::Good;	
}

VerificationScopeLocal::VerificationScopeLocal() : VerificationScope("VerificationScopeLocal", {"VerificationASTForm"}) {}
}
