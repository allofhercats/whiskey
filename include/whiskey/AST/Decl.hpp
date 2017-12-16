#ifndef __WHISKEY_AST_Decl_HPP
#define __WHISKEY_AST_Decl_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class DeclVariable;

class Decl : public AST {
private:
	std::string name;
	std::vector<Container<DeclVariable>> templateDeclArgs;

protected:
	bool onCompare(const AST &other) const;

	virtual bool onCompareDecl(const Decl &other) const = 0;

public:
	Decl(AST::ID id, Range range, std::string name);

	const std::string &getName() const;
	void setName(std::string value);

	std::vector<Container<DeclVariable>> &getTemplateDeclArgs();
	const std::vector<Container<DeclVariable>> &getTemplateDeclArgs() const;
};
}

#endif
