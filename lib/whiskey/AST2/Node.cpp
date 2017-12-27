#include "Module.inc"

#include <whiskey/AST2/Node.hpp>

namespace whiskey {
Node::KindInfo::KindInfo(const char *name, std::vector<Node::FieldTag> fieldTags) : name(name), fieldTags(fieldTags) {}

const char *Node::KindInfo::getName() const {
	return name;
}

unsigned int Node::KindInfo::getNFields() const {
	return fieldTags.size();
}

Node::FieldTag Node::KindInfo::getFieldTag(int index) const {
	return fieldTags[index];
}

Node::KindInfo Node::getKindInfo(Node::Kind value) {
	switch (value) {
		case Node::Kind::TypeAtomicBool: return KindInfo("TypeAtomicBool", {});
		case Node::Kind::TypeAtomicInt8: return KindInfo("TypeAtomicInt8", {});
		case Node::Kind::TypeAtomicInt16: return KindInfo("TypeAtomicInt16", {});
		case Node::Kind::TypeAtomicInt32: return KindInfo("TypeAtomicInt32", {});
		case Node::Kind::TypeAtomicInt64: return KindInfo("TypeAtomicInt64", {});
		case Node::Kind::TypeAtomicUInt8: return KindInfo("TypeAtomicUInt8", {});
		case Node::Kind::TypeAtomicUInt16: return KindInfo("TypeAtomicUInt16", {});
		case Node::Kind::TypeAtomicUInt32: return KindInfo("TypeAtomicUInt32", {});
		case Node::Kind::TypeAtomicUInt64: return KindInfo("TypeAtomicUInt64", {});
		case Node::Kind::TypeAtomicFloat32: return KindInfo("TypeAtomicFloat32", {});
		case Node::Kind::TypeAtomicFloat64: return KindInfo("TypeAtomicFloat64", {});
		case Node::Kind::TypeAtomicReal: return KindInfo("TypeAtomicReal", {});
		case Node::Kind::TypeSymbol: return KindInfo("TypeSymbol", {
			Node::FieldTag::TypeSymbol_Name,
			Node::FieldTag::TypeSymbol_TemplateEvalArgs
		});
		case Node::Kind::TypeAccessUnary: return KindInfo("TypeAccessUnary", {
			Node::FieldTag::TypeAccessUnary_Arg
		});
		case Node::Kind::TypeAccess: return KindInfo("TypeAccess", {
			Node::FieldTag::TypeAccess_Args
		});
		case Node::Kind::TypeGroup: return KindInfo("TypeGroup", {
			Node::FieldTag::TypeGroup_Arg
		});
		case Node::Kind::TypeFunction: return KindInfo("TypeFunction", {
			Node::FieldTag::TypeFunction_Return,
			Node::FieldTag::TypeFunction_Args
		});
		case Node::Kind::ExprLiteralInt: return KindInfo("ExprLiteralInt", {
			Node::FieldTag::ExprLiteralInt_Type,
			Node::FieldTag::ExprLiteralInt_Value
		});
		case Node::Kind::ExprLiteralReal: return KindInfo("ExprLiteralReal", {
			Node::FieldTag::ExprLiteralReal_Type,
			Node::FieldTag::ExprLiteralReal_Value
		});
		case Node::Kind::ExprSymbol: return KindInfo("ExprSymbol", {
			Node::FieldTag::ExprSymbol_Name,
			Node::FieldTag::ExprSymbol_TemplateEvalArgs
		});
		case Node::Kind::ExprAccessUnary: return KindInfo("ExprAccessUnary", {
			Node::FieldTag::ExprAccessUnary_Arg
		});
		case Node::Kind::ExprAccess: return KindInfo("ExprAccess", {
			Node::FieldTag::ExprAccess_Args
		});
		case Node::Kind::ExprGroup: return KindInfo("ExprGroup", {
			Node::FieldTag::ExprGroup_Arg
		});
		case Node::Kind::ExprCall: return KindInfo("ExprCall", {
			Node::FieldTag::ExprCall_Callee,
			Node::FieldTag::ExprCall_Args
		});
		case Node::Kind::ExprAdd: return KindInfo("ExprAdd", {
			Node::FieldTag::ExprAdd_Args
		});
		case Node::Kind::ExprIncPre: return KindInfo("ExprIncPre", {
			Node::FieldTag::ExprIncPre_Arg
		});
		case Node::Kind::ExprIncPost: return KindInfo("ExprIncPost", {
			Node::FieldTag::ExprIncPost_Arg
		});
		case Node::Kind::ExprSub: return KindInfo("ExprSub", {
			Node::FieldTag::ExprSub_LHS,
			Node::FieldTag::ExprSub_RHS
		});
		case Node::Kind::ExprNeg: return KindInfo("ExprNeg", {
			Node::FieldTag::ExprNeg_Arg
		});
		case Node::Kind::ExprDecPre: return KindInfo("ExprDecPre", {
			Node::FieldTag::ExprDecPre_Arg
		});
		case Node::Kind::ExprDecPost: return KindInfo("ExprDecPost", {
			Node::FieldTag::ExprDecPost_Arg
		});
		case Node::Kind::ExprMul: return KindInfo("ExprMul", {
			Node::FieldTag::ExprMul_Args
		});
		case Node::Kind::ExprExp: return KindInfo("ExprExp", {
			Node::FieldTag::ExprExp_LHS,
			Node::FieldTag::ExprExp_RHS
		});
		case Node::Kind::ExprDiv: return KindInfo("ExprDiv", {
			Node::FieldTag::ExprDiv_LHS,
			Node::FieldTag::ExprDiv_RHS
		});
		case Node::Kind::ExprDivInt: return KindInfo("ExprDivInt", {
			Node::FieldTag::ExprDivInt_LHS,
			Node::FieldTag::ExprDivInt_RHS
		});
		case Node::Kind::ExprDivReal: return KindInfo("ExprDivReal", {
			Node::FieldTag::ExprDivReal_LHS,
			Node::FieldTag::ExprDivReal_RHS
		});
		case Node::Kind::ExprMod: return KindInfo("ExprMod", {
			Node::FieldTag::ExprMod_LHS,
			Node::FieldTag::ExprMod_RHS
		});
		case Node::Kind::ExprBitNot: return KindInfo("ExprBitNot", {
			Node::FieldTag::ExprBitNot_Arg
		});
		case Node::Kind::ExprBitAnd: return KindInfo("ExprBitAnd", {
			Node::FieldTag::ExprBitAnd_Args
		});
		case Node::Kind::ExprBitOr: return KindInfo("ExprBitOr", {
			Node::FieldTag::ExprBitOr_Args
		});
		case Node::Kind::ExprBitXor: return KindInfo("ExprBitXor", {
			Node::FieldTag::ExprBitXor_Args
		});
		case Node::Kind::ExprBitShL: return KindInfo("ExprBitShL", {
			Node::FieldTag::ExprBitShL_LHS,
			Node::FieldTag::ExprBitShL_RHS
		});
		case Node::Kind::ExprBitShR: return KindInfo("ExprBitShR", {
			Node::FieldTag::ExprBitShR_LHS,
			Node::FieldTag::ExprBitShR_RHS
		});
		case Node::Kind::ExprLT: return KindInfo("ExprLT", {
			Node::FieldTag::ExprLT_LHS,
			Node::FieldTag::ExprLT_RHS
		});
		case Node::Kind::ExprLE: return KindInfo("ExprLE", {
			Node::FieldTag::ExprLE_LHS,
			Node::FieldTag::ExprLE_RHS
		});
		case Node::Kind::ExprGT: return KindInfo("ExprGT", {
			Node::FieldTag::ExprGT_LHS,
			Node::FieldTag::ExprGT_RHS
		});
		case Node::Kind::ExprGE: return KindInfo("ExprGE", {
			Node::FieldTag::ExprGE_LHS,
			Node::FieldTag::ExprGE_RHS
		});
		case Node::Kind::ExprNE: return KindInfo("ExprNE", {
			Node::FieldTag::ExprNE_LHS,
			Node::FieldTag::ExprNE_RHS
		});
		case Node::Kind::ExprEQ: return KindInfo("ExprEQ", {
			Node::FieldTag::ExprEQ_LHS,
			Node::FieldTag::ExprEQ_RHS
		});
		case Node::Kind::ExprBoolNot: return KindInfo("ExprBoolNot", {
			Node::FieldTag::ExprBoolNot_Arg
		});
		case Node::Kind::ExprBoolAnd: return KindInfo("ExprBoolAnd", {
			Node::FieldTag::ExprBoolAnd_Args
		});
		case Node::Kind::ExprBoolOr: return KindInfo("ExprBoolOr", {
			Node::FieldTag::ExprBoolOr_Args
		});
		case Node::Kind::ExprBoolImplies: return KindInfo("ExprBoolImplies", {
			Node::FieldTag::ExprBoolImplies_Args
		});
		case Node::Kind::ExprAddAssign: return KindInfo("ExprAddAssign", {
			Node::FieldTag::ExprAddAssign_LHS,
			Node::FieldTag::ExprAddAssign_RHS
		});
		case Node::Kind::ExprSubAssign: return KindInfo("ExprSubAssign", {
			Node::FieldTag::ExprSubAssign_LHS,
			Node::FieldTag::ExprSubAssign_RHS
		});
		case Node::Kind::ExprMulAssign: return KindInfo("ExprMulAssign", {
			Node::FieldTag::ExprMulAssign_LHS,
			Node::FieldTag::ExprMulAssign_RHS
		});
		case Node::Kind::ExprExpAssign: return KindInfo("ExprExpAssign", {
			Node::FieldTag::ExprExpAssign_LHS,
			Node::FieldTag::ExprExpAssign_RHS
		});
		case Node::Kind::ExprDivAssign: return KindInfo("ExprDivAssign", {
			Node::FieldTag::ExprDivAssign_LHS,
			Node::FieldTag::ExprDivAssign_RHS
		});
		case Node::Kind::ExprDivIntAssign: return KindInfo("ExprDivIntAssign", {
			Node::FieldTag::ExprDivIntAssign_LHS,
			Node::FieldTag::ExprDivIntAssign_RHS
		});
		case Node::Kind::ExprDivRealAssign: return KindInfo("ExprDivRealAssign", {
			Node::FieldTag::ExprDivRealAssign_LHS,
			Node::FieldTag::ExprDivRealAssign_RHS
		});
		case Node::Kind::ExprModAssign: return KindInfo("ExprModAssign", {
			Node::FieldTag::ExprModAssign_LHS,
			Node::FieldTag::ExprModAssign_RHS
		});
		case Node::Kind::ExprBitAndAssign: return KindInfo("ExprBitAndAssign", {
			Node::FieldTag::ExprBitAndAssign_LHS,
			Node::FieldTag::ExprBitAndAssign_RHS
		});
		case Node::Kind::ExprBitOrAssign: return KindInfo("ExprBitOrAssign", {
			Node::FieldTag::ExprBitOrAssign_LHS,
			Node::FieldTag::ExprBitOrAssign_RHS
		});
		case Node::Kind::ExprBitXorAssign: return KindInfo("ExprBitXorAssign", {
			Node::FieldTag::ExprBitXorAssign_LHS,
			Node::FieldTag::ExprBitXorAssign_RHS
		});
		case Node::Kind::ExprBitShLAssign: return KindInfo("ExprBitShLAssign", {
			Node::FieldTag::ExprBitShLAssign_LHS,
			Node::FieldTag::ExprBitShLAssign_RHS
		});
		case Node::Kind::ExprBitShRAssign: return KindInfo("ExprBitShRAssign", {
			Node::FieldTag::ExprBitShRAssign_LHS,
			Node::FieldTag::ExprBitShRAssign_RHS
		});
		case Node::Kind::ExprAssign: return KindInfo("ExprAssign", {
			Node::FieldTag::ExprAssign_LHS,
			Node::FieldTag::ExprAssign_RHS
		});
		case Node::Kind::StmtEmpty: return KindInfo("StmtEmpty", {});
		case Node::Kind::StmtExpr: return KindInfo("StmtExpr", {
			Node::FieldTag::StmtExpr_Expr
		});
		case Node::Kind::StmtDecl: return KindInfo("StmtDecl", {
			Node::FieldTag::StmtDecl_Decl
		});
		case Node::Kind::StmtReturn: return KindInfo("StmtReturn", {
			Node::FieldTag::StmtReturn_Arg
		});
		case Node::Kind::StmtContinue: return KindInfo("StmtContinue", {
			Node::FieldTag::StmtContinue_Name
		});
		case Node::Kind::StmtBreak: return KindInfo("StmtBreak", {
			Node::FieldTag::StmtBreak_Name
		});
		case Node::Kind::StmtIf: return KindInfo("StmtIf", {
			Node::FieldTag::StmtIf_Condition,
			Node::FieldTag::StmtIf_Then,
			Node::FieldTag::StmtIf_Else
		});
		case Node::Kind::StmtWhile: return KindInfo("StmtWhile", {
			Node::FieldTag::StmtWhile_Condition,
			Node::FieldTag::StmtWhile_Body
		});
		case Node::Kind::StmtFor: return KindInfo("StmtFor", {
			Node::FieldTag::StmtFor_Decls,
			Node::FieldTag::StmtFor_Condition,
			Node::FieldTag::StmtFor_Steps,
			Node::FieldTag::StmtFor_Body
		});
		case Node::Kind::StmtForEach: return KindInfo("StmtForEach", {
			Node::FieldTag::StmtForEach_Decls,
			Node::FieldTag::StmtForEach_Sequences,
			Node::FieldTag::StmtForEach_Body
		});
		case Node::Kind::StmtBlock: return KindInfo("StmtBlock", {
			Node::FieldTag::StmtBlock_Stmts
		});
		case Node::Kind::DeclVariable: return KindInfo("DeclVariable", {
			Node::FieldTag::DeclVariable_Type,
			Node::FieldTag::DeclVariable_Name,
			Node::FieldTag::DeclVariable_TemplateDeclArgs,
			Node::FieldTag::DeclVariable_Initial
		});
		case Node::Kind::DeclFunction: return KindInfo("DeclFunction", {
			Node::FieldTag::DeclFunction_Return,
			Node::FieldTag::DeclFunction_Name,
			Node::FieldTag::DeclFunction_TemplateDeclArgs,
			Node::FieldTag::DeclFunction_Args,
			Node::FieldTag::DeclFunction_Body
		});
		case Node::Kind::DeclClass: return KindInfo("DeclClass", {
			Node::FieldTag::DeclClass_Name,
			Node::FieldTag::DeclClass_TemplateDeclArgs,
			Node::FieldTag::DeclClass_Inherits,
			Node::FieldTag::DeclClass_Members
		});
		case Node::Kind::DeclNamespace: return KindInfo("DeclNamespace", {
			Node::FieldTag::DeclNamespace_Name,
			Node::FieldTag::DeclNamespace_Members
		});
		case Node::Kind::Import: return KindInfo("Import", {
			Node::FieldTag::Import_Path
		});
		case Node::Kind::Unit: return KindInfo("Unit", {
			Node::FieldTag::Unit_Members
		});
	}
}

Node::FieldTagInfo::FieldTagInfo(unsigned int index, const char *name) : index(index), name(name), _isExpectingKind(false), expectedKind(Field::Kind::Node), _isExpectingList(false) {}

Node::FieldTagInfo::FieldTagInfo(unsigned int index, const char *name, Field::Kind expectedKind, bool isExpectingList) : index(index), name(name), _isExpectingKind(true), expectedKind(expectedKind), _isExpectingList(isExpectingList) {}

unsigned int Node::FieldTagInfo::getIndex() const {
	return index;
}

const char *Node::FieldTagInfo::getName() const {
	return name;
}

bool Node::FieldTagInfo::isExpectingKind() const {
	return _isExpectingKind;
}

Field::Kind Node::FieldTagInfo::getExpectedKind() const {
	return expectedKind;
}

bool Node::FieldTagInfo::isExpectingList() const {
	return _isExpectingList;
}

Node::FieldTagInfo Node::getFieldTagInfo(Node::FieldTag value) {
	switch (value) {
		case Node::FieldTag::TypeSymbol_Name: return FieldTagInfo(0, "TypeSymbol_Name");
		case Node::FieldTag::TypeSymbol_TemplateEvalArgs: return FieldTagInfo(1, "TypeSymbol_TemplateEvalArgs", Field::Kind::Node, true);
		case Node::FieldTag::TypeAccessUnary_Arg: return FieldTagInfo(0, "TypeAccessUnary_Arg", Field::Kind::Node);
		case Node::FieldTag::TypeAccess_Args: return FieldTagInfo(0, "TypeAccess_Args", Field::Kind::Node, true);
		case Node::FieldTag::TypeGroup_Arg: return FieldTagInfo(0, "TypeGroup_Arg", Field::Kind::Node);
		case Node::FieldTag::TypeFunction_Return: return FieldTagInfo(0, "TypeFunction_Return", Field::Kind::Node);
		case Node::FieldTag::TypeFunction_Args: return FieldTagInfo(1, "TypeFunction_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprLiteralInt_Type: return FieldTagInfo(0, "ExprLiteralInt_Type", Field::Kind::Node);
		case Node::FieldTag::ExprLiteralInt_Value: return FieldTagInfo(1, "ExprLiteralInt_Value");
		case Node::FieldTag::ExprLiteralReal_Type: return FieldTagInfo(0, "ExprLiteralReal_Type", Field::Kind::Node);
		case Node::FieldTag::ExprLiteralReal_Value: return FieldTagInfo(1, "ExprLiteralReal_Value");
		case Node::FieldTag::ExprSymbol_Name: return FieldTagInfo(0, "ExprSymbol_Name");
		case Node::FieldTag::ExprSymbol_TemplateEvalArgs: return FieldTagInfo(1, "ExprSymbol_TemplateEvalArgs", Field::Kind::Node, true);
		case Node::FieldTag::ExprAccessUnary_Arg: return FieldTagInfo(0, "ExprAccessUnary_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprAccess_Args: return FieldTagInfo(0, "ExprAccess_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprGroup_Arg: return FieldTagInfo(0, "ExprGroup_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprCall_Callee: return FieldTagInfo(0, "ExprCall_Callee", Field::Kind::Node);
		case Node::FieldTag::ExprCall_Args: return FieldTagInfo(1, "ExprCall_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprAdd_Args: return FieldTagInfo(0, "ExprAdd_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprIncPre_Arg: return FieldTagInfo(0, "ExprIncPre_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprIncPost_Arg: return FieldTagInfo(0, "ExprIncPost_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprSub_LHS: return FieldTagInfo(0, "ExprSub_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprSub_RHS: return FieldTagInfo(1, "ExprSub_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprNeg_Arg: return FieldTagInfo(0, "ExprNeg_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprDecPre_Arg: return FieldTagInfo(0, "ExprDecPre_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprDecPost_Arg: return FieldTagInfo(0, "ExprDecPost_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprMul_Args: return FieldTagInfo(0, "ExprMul_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprExp_LHS: return FieldTagInfo(0, "ExprExp_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprExp_RHS: return FieldTagInfo(1, "ExprExp_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprDiv_LHS: return FieldTagInfo(0, "ExprDiv_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprDiv_RHS: return FieldTagInfo(1, "ExprDiv_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivInt_LHS: return FieldTagInfo(0, "ExprDivInt_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivInt_RHS: return FieldTagInfo(1, "ExprDivInt_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivReal_LHS: return FieldTagInfo(0, "ExprDivReal_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivReal_RHS: return FieldTagInfo(1, "ExprDivReal_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprMod_LHS: return FieldTagInfo(0, "ExprMod_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprMod_RHS: return FieldTagInfo(1, "ExprMod_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitNot_Arg: return FieldTagInfo(0, "ExprBitNot_Arg", Field::Kind::Node, true);
		case Node::FieldTag::ExprBitAnd_Args: return FieldTagInfo(0, "ExprBitAnd_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprBitOr_Args: return FieldTagInfo(0, "ExprBitOr_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprBitXor_Args: return FieldTagInfo(0, "ExprBitXor_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprBitShL_LHS: return FieldTagInfo(0, "ExprBitShL_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitShL_RHS: return FieldTagInfo(1, "ExprBitShL_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitShR_LHS: return FieldTagInfo(0, "ExprBitShR_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitShR_RHS: return FieldTagInfo(1, "ExprBitShR_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprLT_LHS: return FieldTagInfo(0, "ExprLT_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprLT_RHS: return FieldTagInfo(1, "ExprLT_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprLE_LHS: return FieldTagInfo(0, "ExprLE_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprLE_RHS: return FieldTagInfo(1, "ExprLE_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprGT_LHS: return FieldTagInfo(0, "ExprGT_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprGT_RHS: return FieldTagInfo(1, "ExprGT_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprGE_LHS: return FieldTagInfo(0, "ExprGE_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprGE_RHS: return FieldTagInfo(1, "ExprGE_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprNE_LHS: return FieldTagInfo(0, "ExprNE_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprNE_RHS: return FieldTagInfo(1, "ExprNE_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprEQ_LHS: return FieldTagInfo(0, "ExprEQ_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprEQ_RHS: return FieldTagInfo(1, "ExprEQ_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBoolNot_Arg: return FieldTagInfo(0, "ExprBoolNot_Arg", Field::Kind::Node);
		case Node::FieldTag::ExprBoolAnd_Args: return FieldTagInfo(0, "ExprBoolAnd_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprBoolOr_Args: return FieldTagInfo(0, "ExprBoolOr_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprBoolImplies_Args: return FieldTagInfo(0, "ExprBoolImplies_Args", Field::Kind::Node, true);
		case Node::FieldTag::ExprAddAssign_LHS: return FieldTagInfo(0, "ExprAddAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprAddAssign_RHS: return FieldTagInfo(1, "ExprAddAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprSubAssign_LHS: return FieldTagInfo(0, "ExprSubAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprSubAssign_RHS: return FieldTagInfo(1, "ExprSubAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprMulAssign_LHS: return FieldTagInfo(0, "ExprMulAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprMulAssign_RHS: return FieldTagInfo(1, "ExprMulAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprExpAssign_LHS: return FieldTagInfo(0, "ExprExpAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprExpAssign_RHS: return FieldTagInfo(1, "ExprExpAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivAssign_LHS: return FieldTagInfo(0, "ExprDivAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivAssign_RHS: return FieldTagInfo(1, "ExprDivAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivIntAssign_LHS: return FieldTagInfo(0, "ExprDivIntAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivIntAssign_RHS: return FieldTagInfo(1, "ExprDivIntAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivRealAssign_LHS: return FieldTagInfo(0, "ExprDivRealAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprDivRealAssign_RHS: return FieldTagInfo(1, "ExprDivRealAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprModAssign_LHS: return FieldTagInfo(0, "ExprModAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprModAssign_RHS: return FieldTagInfo(1, "ExprModAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitAndAssign_LHS: return FieldTagInfo(0, "ExprBitAndAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitAndAssign_RHS: return FieldTagInfo(1, "ExprBitAndAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitOrAssign_LHS: return FieldTagInfo(0, "ExprBitOrAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitOrAssign_RHS: return FieldTagInfo(1, "ExprBitOrAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitXorAssign_LHS: return FieldTagInfo(0, "ExprBitXorAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitXorAssign_RHS: return FieldTagInfo(1, "ExprBitXorAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitShLAssign_LHS: return FieldTagInfo(0, "ExprBitShLAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitShLAssign_RHS: return FieldTagInfo(1, "ExprBitShLAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitShRAssign_LHS: return FieldTagInfo(0, "ExprBitShRAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprBitShRAssign_RHS: return FieldTagInfo(1, "ExprBitShRAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::ExprAssign_LHS: return FieldTagInfo(0, "ExprAssign_LHS", Field::Kind::Node);
		case Node::FieldTag::ExprAssign_RHS: return FieldTagInfo(1, "ExprAssign_RHS", Field::Kind::Node);
		case Node::FieldTag::StmtExpr_Expr: return FieldTagInfo(0, "StmtExpr_Expr", Field::Kind::Node);
		case Node::FieldTag::StmtDecl_Decl: return FieldTagInfo(0, "StmtDecl_Decl", Field::Kind::Node);
		case Node::FieldTag::StmtReturn_Arg: return FieldTagInfo(0, "StmtReturn_Arg", Field::Kind::Node);
		case Node::FieldTag::StmtContinue_Name: return FieldTagInfo(0, "StmtContinue_Name", Field::Kind::Node);
		case Node::FieldTag::StmtBreak_Name: return FieldTagInfo(0, "StmtBreak_Name", Field::Kind::Node);
		case Node::FieldTag::StmtIf_Condition: return FieldTagInfo(0, "StmtIf_Condition", Field::Kind::Node);
		case Node::FieldTag::StmtIf_Then: return FieldTagInfo(1, "StmtIf_Then", Field::Kind::Node);
		case Node::FieldTag::StmtIf_Else: return FieldTagInfo(2, "StmtIf_Else", Field::Kind::Node);
		case Node::FieldTag::StmtWhile_Condition: return FieldTagInfo(0, "StmtWhile_Condition", Field::Kind::Node);
		case Node::FieldTag::StmtWhile_Body: return FieldTagInfo(1, "StmtWhile_Body", Field::Kind::Node);
		case Node::FieldTag::StmtFor_Decls: return FieldTagInfo(0, "StmtFor_Decls", Field::Kind::Node, true);
		case Node::FieldTag::StmtFor_Condition: return FieldTagInfo(1, "StmtFor_Condition", Field::Kind::Node);
		case Node::FieldTag::StmtFor_Steps: return FieldTagInfo(2, "StmtFor_Steps", Field::Kind::Node, true);
		case Node::FieldTag::StmtFor_Body: return FieldTagInfo(3, "StmtFor_Body", Field::Kind::Node);
		case Node::FieldTag::StmtForEach_Decls: return FieldTagInfo(0, "StmtForEach_Decls", Field::Kind::Node, true);
		case Node::FieldTag::StmtForEach_Sequences: return FieldTagInfo(1, "StmtForEach_Sequences", Field::Kind::Node, true);
		case Node::FieldTag::StmtForEach_Body: return FieldTagInfo(2, "StmtForEach_Body", Field::Kind::Node);
		case Node::FieldTag::StmtBlock_Stmts: return FieldTagInfo(0, "StmtBlock_Stmts", Field::Kind::Node, true);
		case Node::FieldTag::DeclVariable_Type: return FieldTagInfo(0, "DeclVariable_Type", Field::Kind::Node);
		case Node::FieldTag::DeclVariable_Name: return FieldTagInfo(1, "DeclVariable_Name");
		case Node::FieldTag::DeclVariable_TemplateDeclArgs: return FieldTagInfo(2, "DeclVariable_TemplateDeclArgs", Field::Kind::Node, true);
		case Node::FieldTag::DeclVariable_Initial: return FieldTagInfo(3, "DeclVariable_Initial", Field::Kind::Node);
		case Node::FieldTag::DeclFunction_Return: return FieldTagInfo(0, "DeclFunction_Return", Field::Kind::Node);
		case Node::FieldTag::DeclFunction_Name: return FieldTagInfo(1, "DeclFunction_Name");
		case Node::FieldTag::DeclFunction_TemplateDeclArgs: return FieldTagInfo(2, "DeclFunction_TemplateDeclArgs", Field::Kind::Node, true);
		case Node::FieldTag::DeclFunction_Args: return FieldTagInfo(3, "DeclFunction_Args", Field::Kind::Node, true);
		case Node::FieldTag::DeclFunction_Body: return FieldTagInfo(4, "DeclFunction_Body", Field::Kind::Node);
		case Node::FieldTag::DeclClass_Name: return FieldTagInfo(0, "DeclClass_Name");
		case Node::FieldTag::DeclClass_TemplateDeclArgs: return FieldTagInfo(1, "DeclClass_TemplateDeclArgs", Field::Kind::Node, true);
		case Node::FieldTag::DeclClass_Inherits: return FieldTagInfo(2, "DeclClass_Inherits", Field::Kind::Node, true);
		case Node::FieldTag::DeclClass_Members: return FieldTagInfo(3, "DeclClass_Members", Field::Kind::Node, true);
		case Node::FieldTag::DeclNamespace_Name: return FieldTagInfo(0, "DeclNamespace_Name");
		case Node::FieldTag::DeclNamespace_Members: return FieldTagInfo(1, "DeclNamespace_Members", Field::Kind::Node, true);
		case Node::FieldTag::Import_Path: return FieldTagInfo(0, "Import_Path");
		case Node::FieldTag::Unit_Members: return FieldTagInfo(0, "Unit_Members", Field::Kind::Node, true);
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
		for (int i = 0; i < getKindInfo(kind).getNFields(); i++) {
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

Node *Node::createExprCall(Node *callee, std::initializer_list<Node *> args, Range range) {
	return new Node(Node::Kind::ExprCall, {Field::createNode(callee), Field::createNode(args)}, range);
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

Node *Node::createStmtWhile(Node *condition, Range range) {
	return createStmtWhile(condition, nullptr, range);
}

Node *Node::createStmtWhile(Node *condition, Node *body, Range range) {
	return new Node(Node::Kind::StmtWhile, {Field::createNode(condition), Field::createNode(body)}, range);
}

Node *Node::createStmtFor(std::initializer_list<Node *> decls, Node *condition, std::initializer_list<Node *> steps, Range range) {
	return createStmtFor(decls, condition, steps, nullptr, range);
}

Node *Node::createStmtFor(std::initializer_list<Node *> decls, Node *condition, std::initializer_list<Node *> steps, Node *body, Range range) {
	return new Node(Node::Kind::StmtFor, {Field::createNode(decls), Field::createNode(condition), Field::createNode(steps), Field::createNode(body)}, range);
}

Node *Node::createStmtForEach(std::initializer_list<Node *> decls, std::initializer_list<Node *> sequences, Range range) {
	return createStmtForEach(decls, sequences, nullptr, range);
}

Node *Node::createStmtForEach(std::initializer_list<Node *> decls, std::initializer_list<Node *> sequences, Node *body, Range range) {
	return new Node(Node::Kind::StmtForEach, {Field::createNode(decls), Field::createNode(sequences), Field::createNode(body)}, range);
}

Node *Node::createStmtBlock(Range range) {
	return createStmtBlock({}, range);
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

Node *Node::createDeclClass(Field *name, Range range) {
	return createDeclClass(name, {}, {}, {}, range);
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

Node *Node::createDeclNamespace(Field *name, Range range) {
	return createDeclNamespace(name, {}, range);
}

Node *Node::createDeclNamespace(Field *name, std::initializer_list<Node *> members, Range range) {
	return new Node(Node::Kind::DeclNamespace, {name, Field::createNode(members)}, range);
}

Node *Node::createImport(Field *path, Range range) {
	return new Node(Node::Kind::Import, {path}, range);
}

Node *Node::createUnit() {
	return createUnit({});
}

Node *Node::createUnit(std::initializer_list<Node *> members) {
	return new Node(Node::Kind::Import, {Field::createNode(members)}, Range());
}

Node *Node::clone() const {
	Node *rtn = new Node(kind, {}, range);
	if (fields != nullptr) {
		int n = getKindInfo(kind).getNFields();
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

Field *Node::getField(FieldTag tag) {
	if (fields == nullptr) {
		return nullptr;
	} else {
		unsigned int index = getFieldTagInfo(tag).getIndex();
		return fields[index];
	}
}

Field *Node::getField(int index) {
	if (fields == nullptr) {
		return nullptr;
	} else if (index < 0 || index >= getKindInfo(kind).getNFields()) {
		return nullptr;
	} else {
		return fields[index];
	}
}

const Field *Node::getField(FieldTag tag) const {
	if (fields == nullptr) {
		return nullptr;
	} else {
		unsigned int index = getFieldTagInfo(tag).getIndex();
		return fields[index];
	}
}

const Field *Node::getField(int index) const {
	if (fields == nullptr) {
		return nullptr;
	} else if (index < 0 || index >= getKindInfo(kind).getNFields()) {
		return nullptr;
	} else {
		return fields[index];
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

	for (int i = 0; i < getKindInfo(kind).getNFields(); i++) {
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
