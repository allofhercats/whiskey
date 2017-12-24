#ifndef __WHISKEY_AST_DeclClass_HPP
#define __WHISKEY_AST_DeclClass_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>
#include <whiskey/AST/Decl.hpp>

namespace whiskey {
class DeclClass : public Decl {
private:
	std::vector<Container<Type>> inherits;
	std::vector<Container<Decl>> members;

protected:
	virtual AST *onClone() const;
	
	bool onCompareDecl(const Decl &other) const;
	void onGetChildrenDecl(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareDeclClass(const DeclClass &other) const;
	virtual void onGetChildrenDeclClass(std::queue<ContainerRef<AST>> &children);

public:
	DeclClass(std::string name, std::vector<Container<Type>> inherits = {}, std::vector<Container<Decl>> members = {});
	DeclClass(Range range, std::string name, std::vector<Container<Type>> inherits = {}, std::vector<Container<Decl>> members = {});

	std::vector<Container<Type>> &getInherits();
	const std::vector<Container<Type>> &getInherits() const;

	std::vector<Container<Decl>> &getMembers();
	const std::vector<Container<Decl>> &getMembers() const;
};
}

#endif
