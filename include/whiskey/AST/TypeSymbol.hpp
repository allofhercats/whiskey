#ifndef __WHISKEY_AST_TypeSymbol_HPP
#define __WHISKEY_AST_TypeSymbol_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/TypeLiteral.hpp>

namespace whiskey {
class TypeSymbol : public TypeLiteral<std::string> {
private:
	std::vector<Container<AST>> templateEvalArgs;

protected:
	virtual AST *onClone() const;

	bool onCompareTypeLiteral(const TypeLiteral<std::string> &other) const;
	void onGetChildrenTypeLiteral(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareTypeSymbol(const TypeSymbol &other) const;
	virtual void onGetChildrenTypeSymbol(std::queue<ContainerRef<AST>> &children);

public:
	TypeSymbol(std::string value, std::vector<Container<AST>> templateEvalArgs = {});
	TypeSymbol(Range range, std::string value, std::vector<Container<AST>> templateEvalArgs = {});

	std::vector<Container<AST>> &getTemplateEvalArgs();
	const std::vector<Container<AST>> &getTemplateEvalArgs() const;
};
}

#endif
