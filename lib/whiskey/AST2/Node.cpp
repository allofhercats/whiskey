#include "Module.inc"

#include <whiskey/AST2/Node.hpp>

namespace whiskey {
int Node::getNFields(Node::Kind kind) {
	switch (kind) {
		case Node::Kind::TypeAtomicBool: return 0;
		case Node::Kind::TypeAtomicInt8: return 0;
		case Node::Kind::TypeAtomicInt16: return 0;
		case Node::Kind::TypeAtomicInt32: return 0;
		case Node::Kind::TypeAtomicInt64: return 0;
		case Node::Kind::TypeAtomicUInt8: return 0;
		case Node::Kind::TypeAtomicUInt16: return 0;
		case Node::Kind::TypeAtomicUInt32: return 0;
		case Node::Kind::TypeAtomicUInt64: return 0;
		case Node::Kind::TypeAtomicFloat32: return 0;
		case Node::Kind::TypeAtomicFloat64: return 0;
		case Node::Kind::TypeAtomicReal: return 0;
		case Node::Kind::TypeSymbol: return 2;
		case Node::Kind::TypeAccessUnary: return 1;
		case Node::Kind::TypeAccess: return 1;
		case Node::Kind::TypeGroup: return 1;
		case Node::Kind::TypeFunction: return 2;
		case Node::Kind::ExprLiteralInt: return 2;
		case Node::Kind::ExprLiteralReal: return 2;
		case Node::Kind::ExprSymbol: return 2;
		case Node::Kind::ExprAccessUnary: return 1;
		case Node::Kind::ExprAccess: return 1;
		case Node::Kind::ExprGroup: return 1;
		case Node::Kind::ExprAdd: return 1;
		case Node::Kind::ExprIncPre: return 1;
		case Node::Kind::ExprIncPost: return 1;
		case Node::Kind::ExprSub: return 2;
		case Node::Kind::ExprNeg: return 1;
		case Node::Kind::ExprDecPre: return 1;
		case Node::Kind::ExprDecPost: return 1;
		case Node::Kind::ExprMul: return 1;
		case Node::Kind::ExprExp: return 2;
		case Node::Kind::ExprDiv: return 2;
		case Node::Kind::ExprDivInt: return 2;
		case Node::Kind::ExprDivReal: return 2;
		case Node::Kind::ExprMod: return 2;
		case Node::Kind::ExprBitNot: return 1;
		case Node::Kind::ExprBitAnd: return 1;
		case Node::Kind::ExprBitOr: return 1;
		case Node::Kind::ExprBitXor: return 1;
		case Node::Kind::ExprBitShL: return 2;
		case Node::Kind::ExprBitShR: return 2;
		case Node::Kind::ExprBoolNot: return 1;
		case Node::Kind::ExprBoolAnd: return 1;
		case Node::Kind::ExprBoolOr: return 1;
		case Node::Kind::ExprBoolImplies: return 1;
		case Node::Kind::ExprAddAssign: return 2;
		case Node::Kind::ExprSubAssign: return 2;
		case Node::Kind::ExprMulAssign: return 2;
		case Node::Kind::ExprExpAssign: return 2;
		case Node::Kind::ExprDivAssign: return 2;
		case Node::Kind::ExprDivIntAssign: return 2;
		case Node::Kind::ExprDivRealAssign: return 2;
		case Node::Kind::ExprModAssign: return 2;
		case Node::Kind::ExprBitAndAssign: return 2;
		case Node::Kind::ExprBitOrAssign: return 2;
		case Node::Kind::ExprBitXorAssign: return 2;
		case Node::Kind::ExprBitShLAssign: return 2;
		case Node::Kind::ExprBitShRAssign: return 2;
		case Node::Kind::ExprAssign: return 2;
		case Node::Kind::StmtEmpty: return 0;
		case Node::Kind::StmtExpr: return 1;
		case Node::Kind::StmtDecl: return 1;
		case Node::Kind::StmtReturn: return 1;
		case Node::Kind::StmtContinue: return 1;
		case Node::Kind::StmtBreak: return 1;
		case Node::Kind::StmtIf: return 3;
		case Node::Kind::StmtWhile: return 2;
		case Node::Kind::StmtFor: return 4;
		case Node::Kind::StmtForEach: return 3;
		case Node::Kind::StmtBlock: return 1;
		case Node::Kind::DeclVariable: return 4;
		case Node::Kind::DeclFunction: return 5;
		case Node::Kind::DeclClass: return 4;
		case Node::Kind::DeclNamespace: return 2;
		case Node::Kind::Import: return 1;
		case Node::Kind::Unit: return 1;
	}
}

Node::Node(Node::Kind kind, std::initializer_list<Field *> fields, Range range) {
	this->range = range;
	this->kind = kind;
	if (fields.size() == 0) {
		this->fields = nullptr;
	} else {
		this->fields = new Field *[fields.size()];
		Field **dstIter = this->fields;
		std::initializer_list<Field *>::iterator srcIter = fields.begin();
		while (srcIter != fields.end()) {
			*dstIter = *srcIter;
			dstIter++;
			srcIter++;
		}
	}
	this->next = nullptr;
}

Node::~Node() {
	if (fields != nullptr) {
		for (int i = 0; i < getNFields(kind); i++) {
			delete fields[i];
		}
		delete[] fields;
	}
	delete next;
}

Node *Node::createTypeAtomicBool(Range range) {
	return new Node(Node::Kind::TypeAtomicBool, {}, range);
}

Node *Node::createTypeAtomicInt8(Range range) {
	return new Node(Node::Kind::TypeAtomicInt8, {}, range);
}

Node *Node::createTypeAtomicInt16(Range range) {
	return new Node(Node::Kind::TypeAtomicInt16, {}, range);
}

Node *Node::createTypeAtomicInt32(Range range) {
	return new Node(Node::Kind::TypeAtomicInt32, {}, range);
}

Node *Node::createTypeAtomicInt64(Range range) {
	return new Node(Node::Kind::TypeAtomicInt64, {}, range);
}

Node *Node::createTypeAtomicUInt8(Range range) {
	return new Node(Node::Kind::TypeAtomicUInt8, {}, range);
}

Node *Node::createTypeAtomicUInt16(Range range) {
	return new Node(Node::Kind::TypeAtomicUInt16, {}, range);
}

Node *Node::createTypeAtomicUInt32(Range range) {
	return new Node(Node::Kind::TypeAtomicUInt32, {}, range);
}

Node *Node::createTypeAtomicUInt64(Range range) {
	return new Node(Node::Kind::TypeAtomicUInt64, {}, range);
}

Node *Node::createTypeAtomicFloat32(Range range) {
	return new Node(Node::Kind::TypeAtomicFloat32, {}, range);
}

Node *Node::createTypeAtomicFloat64(Range range) {
	return new Node(Node::Kind::TypeAtomicFloat64, {}, range);
}

Node *Node::createTypeAtomicReal(Range range) {
	return new Node(Node::Kind::TypeAtomicReal, {}, range);
}

Node *Node::createTypeSymbol(Field *name, Range range) {
	return createTypeSymbol(name, {}, range);
}

Node *Node::createTypeSymbol(Field *name, std::initializer_list<Node *> templateEvalArgs, Range range) {
	return new Node(Node::Kind::TypeSymbol, {name, Field::createNode(templateEvalArgs)}, range);
}

Node *Node::createTypeAccessUnary(Node *arg, Range range) {
	return new Node(Node::Kind::TypeAccessUnary, {Field::createNode(arg)}, range);
}

Node *Node::createTypeAccess(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::TypeAccess, {Field::createNode(args)}, range);
}

Node *Node::createTypeGroup(Node *arg, Range range) {
	return new Node(Node::Kind::TypeGroup, {Field::createNode(arg)}, range);
}

Node *Node::createTypeFunction(Node *ret, std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::TypeFunction, {Field::createNode(ret), Field::createNode(args)}, range);
}

Node *Node::createExprLiteralInt(Node *type, Int value, Range range) {
	return new Node(Node::Kind::ExprLiteralInt, {Field::createNode(type), Field::createInt(value)}, range);
}

Node *Node::createExprLiteralReal(Node *type, Real value, Range range) {
	return new Node(Node::Kind::ExprLiteralReal, {Field::createNode(type), Field::createReal(value)}, range);
}

Node *Node::createExprSymbol(Field *name, Range range) {
	return createExprSymbol(name, {}, range);
}

Node *Node::createExprSymbol(Field *name, std::initializer_list<Node *> templateEvalArgs, Range range) {
	return new Node(Node::Kind::ExprSymbol, {name, Field::createNode(templateEvalArgs)}, range);
}

Node *Node::createExprAccessUnary(Node *arg, Range range) {
	return new Node(Node::Kind::ExprAccessUnary, {Field::createNode(arg)}, range);
}

Node *Node::createExprAccess(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprAccess, {Field::createNode(args)}, range);
}

Node *Node::createExprGroup(Node *arg, Range range) {
	return new Node(Node::Kind::ExprGroup, {Field::createNode(arg)}, range);
}

Node *Node::createExprAdd(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprAdd, {Field::createNode(args)}, range);
}

Node *Node::createExprIncPre(Node *arg, Range range) {
	return new Node(Node::Kind::ExprIncPre, {Field::createNode(arg)}, range);
}

Node *Node::createExprIncPost(Node *arg, Range range) {
	return new Node(Node::Kind::ExprIncPost, {Field::createNode(arg)}, range);
}

Node *Node::createExprSub(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprSub, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprNeg(Node *arg, Range range) {
	return new Node(Node::Kind::ExprNeg, {Field::createNode(arg)}, range);
}

Node *Node::createExprDecPre(Node *arg, Range range) {
	return new Node(Node::Kind::ExprDecPre, {Field::createNode(arg)}, range);
}

Node *Node::createExprDecPost(Node *arg, Range range) {
	return new Node(Node::Kind::ExprDecPost, {Field::createNode(arg)}, range);
}

Node *Node::createExprMul(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprMul, {Field::createNode(args)}, range);
}

Node *Node::createExprExp(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprExp, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprDiv(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprDiv, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprDivInt(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprDivInt, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprDivReal(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprDivReal, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprMod(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprMod, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBitNot(Node *arg, Range range) {
	return new Node(Node::Kind::ExprBitNot, {Field::createNode(arg)}, range);
}

Node *Node::createExprBitAnd(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprBitAnd, {Field::createNode(args)}, range);
}

Node *Node::createExprBitOr(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprBitOr, {Field::createNode(args)}, range);
}

Node *Node::createExprBitXor(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprBitXor, {Field::createNode(args)}, range);
}

Node *Node::createExprBitShL(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprBitShL, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBitShR(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprBitShR, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBoolNot(Node *arg, Range range) {
	return new Node(Node::Kind::ExprBoolNot, {Field::createNode(arg)}, range);
}

Node *Node::createExprBoolAnd(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprBoolAnd, {Field::createNode(args)}, range);
}

Node *Node::createExprBoolOr(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprBoolOr, {Field::createNode(args)}, range);
}

Node *Node::createExprBoolImplies(std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprBoolImplies, {Field::createNode(args)}, range);
}

Node *Node::createExprAddAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprAddAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprSubAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprSubAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprMulAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprMulAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprExpAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprExpAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprDivAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprDivAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprDivIntAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprDivIntAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprDivRealAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprDivRealAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprModAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprModAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBitAndAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprBitAndAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBitOrAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprBitOrAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBitXorAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprBitXorAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBitShLAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprBitShLAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprBitShRAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprBitShRAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createExprAssign(Node *lhs, Node *rhs, Range range) {
	return new Node(Node::Kind::ExprAssign, {Field::createNode(lhs), Field::createNode(rhs)}, range);
}

Node *Node::createStmtEmpty(Range range) {
	return new Node(Node::Kind::StmtEmpty, {}, range);
}

Node *Node::createStmtExpr(Node *expr, Range range) {
	return new Node(Node::Kind::StmtExpr, {Field::createNode(expr)}, range);
}

Node *Node::createStmtDecl(Node *decl, Range range) {
	return new Node(Node::Kind::StmtDecl, {Field::createNode(decl)}, range);
}

Node *Node::createStmtReturn(Node *arg, Range range) {
	return new Node(Node::Kind::StmtReturn, {Field::createNode(arg)}, range);
}

Node *Node::createStmtContinue(Field *name, Range range) {
	return new Node(Node::Kind::StmtContinue, {name}, range);
}

Node *Node::createStmtBreak(Field *name, Range range) {
	return new Node(Node::Kind::StmtBreak, {name}, range);
}

Node *Node::createStmtIf(Node *condition, Node *then, Range range) {
	return createStmtIf(condition, then, nullptr, range);
}

Node *Node::createStmtIf(Node *condition, Node *then, Node *_else, Range range) {
	return new Node(Node::Kind::StmtIf, {Field::createNode(condition), Field::createNode(then), Field::createNode(_else)}, range);
}

Node *Node::createStmtWhile(Node *condition, Node *body, Range range) {
	return new Node(Node::Kind::StmtWhile, {Field::createNode(condition), Field::createNode(body)}, range);
}

Node *Node::createStmtFor(std::initializer_list<Node *> decls, Node *condition, std::initializer_list<Node *> steps, Node *body, Range range) {
	return new Node(Node::Kind::StmtFor, {Field::createNode(decls), Field::createNode(condition), Field::createNode(steps), Field::createNode(body)}, range);
}

Node *Node::createStmtForEach(std::initializer_list<Node *> decls, std::initializer_list<Node *> sequences, Node *body, Range range) {
	return new Node(Node::Kind::StmtForEach, {Field::createNode(decls), Field::createNode(sequences), Field::createNode(body)}, range);
}

Node *Node::createStmtBlock(std::initializer_list<Node *> stmts, Range range) {
	return new Node(Node::Kind::StmtBlock, {Field::createNode(stmts)}, range);
}

Node *Node::createDeclVariable(Node *type, Field *name, Range range) {
	return createDeclVariable(type, name, {}, nullptr, range);
}

Node *Node::createDeclVariable(Node *type, Field *name, Node *initial, Range range) {
	return createDeclVariable(type, name, {}, initial, range);
}

Node *Node::createDeclVariable(Node *type, Field *name, std::initializer_list<Node *> templateDeclArgs, Range range) {
	return createDeclVariable(type, name, templateDeclArgs, nullptr, range);
}

Node *Node::createDeclVariable(Node *type, Field *name, std::initializer_list<Node *> templateDeclArgs, Node *initial, Range range) {
	return new Node(Node::Kind::DeclVariable, {Field::createNode(type), name, Field::createNode(templateDeclArgs), Field::createNode(initial)}, range);
}

Node *Node::createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> args, Range range) {
	return createDeclFunction(ret, name, {}, args, nullptr, range);
}

Node *Node::createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> templateDeclArgs, std::initializer_list<Node *> args, Range range) {
	return createDeclFunction(ret, name, templateDeclArgs, args, nullptr, range);
}

Node *Node::createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> args, Node *body, Range range) {
	return createDeclFunction(ret, name, {}, args, body, range);
}

Node *Node::createDeclFunction(Node *ret, Field *name, std::initializer_list<Node *> templateDeclArgs, std::initializer_list<Node *> args, Node *body, Range range) {
	return new Node(Node::Kind::DeclFunction, {Field::createNode(ret), name, Field::createNode(templateDeclArgs), Field::createNode(args), Field::createNode(body)}, range);
}

Node *Node::createDeclClass(Field *name, std::initializer_list<Node *> members, Range range) {
	return createDeclClass(name, {}, {}, members, range);
}

Node *Node::createDeclClass(Field *name, std::initializer_list<Node *> inherits, std::initializer_list<Node *> members, Range range) {
	return createDeclClass(name, {}, inherits, members, range);
}

Node *Node::createDeclClass(Field *name, std::initializer_list<Node *> templateDeclArgs, std::initializer_list<Node *> inherits, std::initializer_list<Node *> members, Range range) {
	return new Node(Node::Kind::DeclClass, {name, Field::createNode(templateDeclArgs), Field::createNode(inherits), Field::createNode(members)}, range);
}

Node *Node::createDeclNamespace(Field *name, std::initializer_list<Node *> members, Range range) {
	return new Node(Node::Kind::DeclNamespace, {name, Field::createNode(members)}, range);
}

Node *Node::createImport(Field *path, Range range) {
	return new Node(Node::Kind::Import, {path}, range);
}

Node *Node::createUnit(std::initializer_list<Node *> members) {
	return new Node(Node::Kind::Import, {Field::createNode(members)}, Range());
}

Node *Node::clone() const {
	Node *rtn = new Node(kind, {}, range);
	if (fields != nullptr) {
		int n = getNFields(kind);
		rtn->fields = new Field *[n];
		for (int i = 0; i < n; i++) {
			if (fields[i] == nullptr) {
				rtn->fields[i] = nullptr;
			} else {
				rtn->fields[i] = fields[i]->clone();
			}
		}
	}
	if (next != nullptr) {
		rtn->next = next->clone();
	} else {
		rtn->next = nullptr;
	}
	return rtn;
}

const Range &Node::getRange() const {
	return range;
}

void Node::setRange(Range value) {
	range = value;
}

Node::Kind Node::getKind() const {
	return kind;
}

int Node::getNFields() const {
	return getNFields(kind);
}

Field *Node::getField(int index) {
	if (fields == nullptr) {
		return nullptr;
	} else if (index < 0 || index >= getNFields(kind)) {
		return nullptr;
	} else {
		return fields[index];
	}
}

const Field *Node::getField(int index) const {
	if (fields == nullptr) {
		return nullptr;
	} else if (index < 0 || index >= getNFields(kind)) {
		return nullptr;
	} else {
		return fields[index];
	}
}

void Node::setField(int index, Field *value) {
	if (fields != nullptr && !(index < 0 || index >= getNFields(kind))) {
		fields[index] = value;
	}
}

Node *Node::getNext() {
	return next;
}

const Node *Node::getNext() const {
	return next;
}

void Node::setNext(Node *value) {
	next = value;
}

bool Node::compare(const Node *other) const {
	W_ASSERT_NONNULL(other, "Cannot compare node against null.");

	if (kind != other->kind) {
		return false;
	}

	for (int i = 0; i < getNFields(); i++) {
		if (fields[i] == nullptr) {
			if (other->fields[i] != nullptr) {
				return false;
			}
		} else {
			if (other->fields[i] == nullptr) {
				return false;
			} else {
				if (!fields[i]->compare(other->fields[i])) {
					return false;
				}
			}
		}
	}

	if (next == nullptr) {
		if (other->next != nullptr) {
			return false;
		}
	} else {
		if (other->next == nullptr) {
			return false;
		} else {
			if (!next->compare(other->next)) {
				return false;
			}
		}
	}

	return true;
}
}
