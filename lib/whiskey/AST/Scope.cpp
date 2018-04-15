#include <whiskey/AST/Scope.hpp>

namespace whiskey {
namespace {
std::string anEmptyString;
Node anEmptyNode;
}

const Scope::ID Scope::none = static_cast<Scope::ID>(-1);

Scope::Scope() {}

Scope::ID Scope::getNDeclarations() const {
	return static_cast<Scope::ID>(declarations.size());
}

Scope::ID Scope::declare(Node node) {
	W_ASSERT_GT(node.getToken().getText().size(), 0u, "Cannot declare node with empty name.");

	Scope::ID rtn = static_cast<Scope::ID>(declarations.size());
	names[node.getToken().getText()] = rtn;
	declarations[rtn] = node;
	return rtn;
}

void Scope::undeclare(Scope::ID id) {
	std::map<ID, Node>::iterator i = declarations.find(id);
	if (i != declarations.end()) {
		std::map<std::string, ID>::iterator j = names.find(i->second.getToken().getText());
		if (j != names.end()) {
			names.erase(j);
		}
		declarations.erase(i);
	}
}

void Scope::redeclare(Scope::ID id, Node node) {
	names[node.getToken().getText()] = id;
	declarations[id] = node;
}

bool Scope::isDeclared(Scope::ID id) const {
	return declarations.find(id) != declarations.end();
}

bool Scope::isDeclared(const std::string &name) const {
	return names.find(name) != names.end();
}

Scope::ID Scope::getID(const std::string &name) const {
	std::map<std::string, ID>::const_iterator i = names.find(name);
	if (i == names.end()) {
		return none;
	} else {
		return i->second;
	}
}

const std::string &Scope::getName(Scope::ID id) const {
	std::map<ID, Node>::const_iterator i = declarations.find(id);
	if (i == declarations.end()) {
		return anEmptyString;
	} else {
		return i->second.getToken().getText();
	}
}

const Node &Scope::getNode(Scope::ID id) const {
	std::map<ID, Node>::const_iterator i = declarations.find(id);
	if (i == declarations.end()) {
		return anEmptyNode;
	} else {
		return i->second;
	}
}

void Scope::print(std::ostream &os, int indent) const {
	for (const std::pair<ID, Node> &i : declarations) {
		os << '\n';
		for (int i = 0; i < indent+2; i++) {
			os << ' ';
		}
		os << "[" << std::dec << i.first << "] " << i.second.getToken().getText();
	}
}
}
