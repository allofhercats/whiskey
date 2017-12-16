#include "Module.inc"

#include <whiskey/Parsing/ParserResult.hpp>

namespace whiskey {
ParserResult::ParserResult() : good(false) {}

ParserResult::ParserResult(Container<AST> ast) : ast(ast), good(true) {}

Ref<AST> ParserResult::getAST() {
	return ast;
}

CRef<AST> ParserResult::getAST() const {
	return ast;
}

void ParserResult::setAST(Container<AST> value) {
	ast = value;
}

bool ParserResult::isGood() const {
	return good;
}

void ParserResult::setGood(bool value) {
	good = value;
}
}
