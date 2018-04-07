#ifndef __WHISKEY_Passes_Verifications_VerificationPreCodeGen_HPP
#define __WHISKEY_Passes_Verifications_VerificationPreCodeGen_HPP

#include <whiskey/AST/NodeType.hpp>
#include <whiskey/AST/FieldTag.hpp>
#include <whiskey/Passes/Verification.hpp>

namespace whiskey {
class VerificationPreCodeGen : Verification {
protected:
	bool onVerifyPre(const Node &node, MessageContext &msgs);
	bool onVerifyPost(const Node &node, MessageContext &msgs);

public:
	VerificationPreCodeGen();
};
}

#endif
