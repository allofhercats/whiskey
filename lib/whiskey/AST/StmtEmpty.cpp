#include "Module.inc"

#include <whiskey/AST/StmtEmpty.hpp>

namespace whiskey {
AST *StmtEmpty::onClone() const {
	return new StmtEmpty(getRange());
}

bool StmtEmpty::onCompare(const AST &other) const {
	return true;
}

StmtEmpty::StmtEmpty(Range range) : Stmt(AST::ID::StmtEmpty, range) {}
}
