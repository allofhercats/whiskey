#ifndef __WHISKEY_Passes_Verification_HPP
#define __WHISKEY_Passes_Verification_HPP

#include <whiskey/Passes/Pass.hpp>

namespace whiskey {
class Verification : Pass {
protected:
	bool onRunPre(Node &node, MessageContext &msgs) final;
	bool onRunPost(Node &node, MessageContext &msgs) final;

	virtual bool onVerifyPre(const Node &node, MessageContext &msgs) = 0;
	virtual bool onVerifyPost(const Node &node, MessageContext &msgs) = 0;

public:
	Verification(std::string name, std::initializer_list<std::string> dependencies = {});
};
}

#endif
