#ifndef __WHISKEY_AST_ExprSymbol_HPP
#define __WHISKEY_AST_ExprSymbol_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
class ExprSymbol : public Expr {
private:
	std::string value;
	std::vector<Container<AST>> templateEvalArgs;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareExprSymbol(const ExprSymbol &other) const;

public:
	ExprSymbol(std::string value);
	ExprSymbol(Range range, std::string value);

	const std::string &getValue() const;
	void setValue(std::string value);

	std::vector<Container<AST>> &getTemplateEvalArgs();
	const std::vector<Container<AST>> &getTemplateEvalArgs() const;
};
}

#endif
