#include "Module.inc"

#include <whiskey/AST/ExprSymbol.hpp>

namespace whiskey {
AST *ExprSymbol::onClone() const {
	ExprSymbol *rtn = new ExprSymbol(getRange(), value);
	rtn->templateEvalArgs = templateEvalArgs;
	return rtn;
}

bool ExprSymbol::onCompare(const AST &other) const {
	const ExprSymbol &casted = static_cast<const ExprSymbol &>(other);

	if (value != casted.value) {
		return false;
	}

	if (!AST::compare(templateEvalArgs, casted.templateEvalArgs)) {
		return false;
	}

	if (!onCompareExprSymbol(casted)) {
		return false;
	}

	return true;
}

bool ExprSymbol::onCompareExprSymbol(const ExprSymbol &other) const {
	return true;
}

ExprSymbol::ExprSymbol(std::string value) : Expr(AST::ID::ExprSymbol, Range()), value(value) {}

ExprSymbol::ExprSymbol(Range range, std::string value) : Expr(AST::ID::ExprSymbol, range), value(value) {}

std::vector<Container<AST>> &ExprSymbol::getTemplateEvalArgs() {
	return templateEvalArgs;
}

const std::vector<Container<AST>> &ExprSymbol::getTemplateEvalArgs() const {
	return templateEvalArgs;
}
}
