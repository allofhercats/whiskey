#include "Module.inc"

#include <whiskey/AST/StmtBlock.hpp>

namespace whiskey {
AST *StmtBlock::onClone() const {
	return new StmtBlock(getRange(), body);
}

bool StmtBlock::onCompareStmt(const Stmt &other) const {
	const StmtBlock &casted = static_cast<const StmtBlock &>(other);

	if (!AST::compare(body, casted.body)) {
		return false;
	}

	if (!onCompareStmtBlock(casted)) {
		return false;
	}

	return true;
}

void StmtBlock::onGetChildrenStmt(std::queue<ContainerRef<AST>> &children) {
	for (Container<Stmt> &i : body) {
		children.push(ContainerRef<AST>(i));
	}
	onGetChildrenStmtBlock(children);
}

bool StmtBlock::onCompareStmtBlock(const StmtBlock &other) const {
	return true;
}

void StmtBlock::onGetChildrenStmtBlock(std::queue<ContainerRef<AST>> &children) {}

StmtBlock::StmtBlock(std::vector<Container<Stmt>> body) : Stmt(AST::ID::StmtBlock, Range()), body(body) {}

StmtBlock::StmtBlock(Range range, std::vector<Container<Stmt>> body) : Stmt(AST::ID::StmtBlock, range), body(body) {}

std::vector<Container<Stmt>> &StmtBlock::getBody() {
	return body;
}

const std::vector<Container<Stmt>> &StmtBlock::getBody() const {
	return body;
}
}
