#ifndef __WHISKEY_AST_Scope_HPP
#define __WHISKEY_AST_Scope_HPP

#include <map>

#include <whiskey/AST/Node.hpp>

namespace whiskey {
class Scope {
public:
	typedef uint32_t ID;

private:
	std::map<std::string, ID> names;
	std::map<ID, Node> declarations;

public:
	static const ID none;

	Scope();
	Scope(const Scope &) = delete;

	ID getNDeclarations() const;

	ID declare(Node node);
	void undeclare(ID id);
	void redeclare(ID id, Node node);

	bool isDeclared(ID id) const;
	bool isDeclared(const std::string &name) const;
	ID getID(const std::string &name) const;
	const std::string &getName(ID id) const;
	const Node &getNode(ID id) const;

	void print(std::ostream &os, int indent) const;
};
}

#endif
