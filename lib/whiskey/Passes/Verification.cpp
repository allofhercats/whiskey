#include <whiskey/Passes/Verification.hpp>

namespace whiskey {
bool Verification::onRunPre(Node &node, MessageContext &msgs) {
	return onVerifyPre(node, msgs);
}

bool Verification::onRunPost(Node &node, MessageContext &msgs) {
	return onVerifyPost(node, msgs);
}

Verification::Verification(std::string name, std::initializer_list<std::string> dependencies) : Pass(name, dependencies) {}
}
