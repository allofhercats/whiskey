#ifndef __WHISKEY_Passes_VerificationScopeGlobal_HPP
#define __WHISKEY_Passes_VerificationScopeGlobal_HPP

#include <whiskey/Passes/Verifications/VerificationScope.hpp>

namespace whiskey {
class VerificationScopeGlobal : public VerificationScope {
protected:
	PassResult onRunPre(Node &node, MessageContext &msgs);
	PassResult onRunPost(Node &node, MessageContext &msgs);

public:
	VerificationScopeGlobal();
};
}

#endif
