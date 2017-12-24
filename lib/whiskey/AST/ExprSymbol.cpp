#include "Module.inc"

#include <whiskey/AST/ExprSymbol.hpp>

namespace whiskey {
AST *ExprSymbol::onClone() const {
	ExprSymbol *rtn = new ExprSymbol(getRange(), value);
	rtn->templateEvalArgs = templateEvalArgs;
	return rtn;
}

bool ExprSymbol::onCompareExpr(const Expr &other) const {
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

void ExprSymbol::onGetChildrenExpr(std::queue<ContainerRef<AST>> &children) {
	for (Container<AST> &i : templateEvalArgs) {
		children.push(ContainerRef<AST>(i));
	}
	onGetChildrenExprSymbol(children);
}

bool ExprSymbol::onCompareExprSymbol(const ExprSymbol &other) const {
	return true;
}

void ExprSymbol::onGetChildrenExprSymbol(std::queue<ContainerRef<AST>> &children) {}

ExprSymbol::ExprSymbol(std::string value, std::vector<Container<AST>> templateEvalArgs) : Expr(AST::ID::ExprSymbol, Range()), value(value), templateEvalArgs(templateEvalArgs) {}

ExprSymbol::ExprSymbol(Range range, std::string value, std::vector<Container<AST>> templateEvalArgs) : Expr(AST::ID::ExprSymbol, range), value(value), templateEvalArgs(templateEvalArgs) {}

const std::string &ExprSymbol::getValue() const {
	return value;
}

void ExprSymbol::setValue(std::string value) {
	this->value = value;
}

std::vector<Container<AST>> &ExprSymbol::getTemplateEvalArgs() {
	return templateEvalArgs;
}

const std::vector<Container<AST>> &ExprSymbol::getTemplateEvalArgs() const {
	return templateEvalArgs;
}
}
