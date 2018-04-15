#ifndef __WHISKEY_Passes_Verifications_VerificationASTForm_HPP
#define __WHISKEY_Passes_Verifications_VerificationASTForm_HPP

#include <whiskey/AST/Pass.hpp>

namespace whiskey {
class VerificationASTForm : Pass {
protected:
	PassResult onRunPre(Node &node, MessageContext &msgs);
	PassResult onRunPost(Node &node, MessageContext &msgs);

public:
	VerificationASTForm();
};
}

#endif
