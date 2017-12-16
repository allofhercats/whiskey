#ifndef __WHISKEY_AST_DeclNamespace_HPP
#define __WHISKEY_AST_DeclNamespace_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>
#include <whiskey/AST/Decl.hpp>

namespace whiskey {
class DeclNamespace : public Decl {
private:
	std::vector<Container<Decl>> members;

protected:
	AST *onClone() const;
	bool onCompareDecl(const Decl &other) const;

	virtual bool onCompareDeclNamespace(const DeclNamespace &other) const;

public:
	DeclNamespace(std::string name, std::vector<Container<Decl>> members = {});
	DeclNamespace(Range range, std::string name, std::vector<Container<Decl>> members = {});

	std::vector<Container<Decl>> &getMembers();
	const std::vector<Container<Decl>> &getMembers() const;
};
}

#endif
