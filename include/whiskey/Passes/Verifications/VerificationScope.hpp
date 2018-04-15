#ifndef __WHISKEY_Passes_VerificationScope_HPP
#define __WHISKEY_Passes_VerificationScope_HPP

#include <whiskey/AST/Pass.hpp>

namespace whiskey {
class VerificationScope : public Pass {
protected:
	Node stripNonScopeDeclVariable(Node value);
	Node stripNonScopeDeclFunction(Node value);
	Node stripNonScopeDeclClass(Node value);
	Node stripNonScopeDeclNamespace(Node value);
	Node stripNonScopeUnit(Node value);

public:
	VerificationScope(std::string name, std::initializer_list<std::string> dependencies);
	virtual ~VerificationScope();
};
}

#endif
