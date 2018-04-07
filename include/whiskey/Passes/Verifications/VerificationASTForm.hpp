#ifndef __WHISKEY_Passes_Verifications_VerificationASTForm_HPP
#define __WHISKEY_Passes_Verifications_VerificationASTForm_HPP

#include <whiskey/AST/NodeType.hpp>
#include <whiskey/AST/FieldTag.hpp>
#include <whiskey/Passes/Verification.hpp>

namespace whiskey {
class VerificationASTForm : Verification {
protected:
	bool onVerifyPre(const Node &node, MessageContext &msgs);
	bool onVerifyPost(const Node &node, MessageContext &msgs);

public:
	VerificationASTForm();
};
}

#endif
