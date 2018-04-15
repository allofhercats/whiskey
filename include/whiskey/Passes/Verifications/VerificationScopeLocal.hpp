#ifndef __WHISKEY_Passes_Verifications_VerificationScopeLocal_HPP
#define __WHISKEY_Passes_Verifications_VerificationScopeLocal_HPP

#include <whiskey/Passes/Verifications/VerificationScope.hpp>

namespace whiskey {
class VerificationScopeLocal : public VerificationScope {
protected:
	PassResult onRunPre(Node &node, MessageContext &msgs);
	PassResult onRunPost(Node &node, MessageContext &msgs);

public:
	VerificationScopeLocal();
};
}

#endif
