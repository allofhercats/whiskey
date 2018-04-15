#ifndef __WHISKEY_Passes_Verifications_VerificationPreCodeGen_HPP
#define __WHISKEY_Passes_Verifications_VerificationPreCodeGen_HPP

#include <whiskey/AST/Pass.hpp>

namespace whiskey {
class VerificationPreCodeGen : Pass {
protected:
	PassResult onRunPre(Node &node, MessageContext &msgs);
	PassResult onRunPost(Node &node, MessageContext &msgs);

public:
	VerificationPreCodeGen();
};
}

#endif
