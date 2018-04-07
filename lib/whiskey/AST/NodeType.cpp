#include <whiskey/AST/NodeType.hpp>

namespace whiskey {
namespace {
NodeTypeInfo nodeTypeInfos[] {
	NodeTypeInfo("None", NodeTypeCategory::None, {}),
	NodeTypeInfo("List", NodeTypeCategory::Internal, {FieldTag::List_Children}),
	NodeTypeInfo("TypeVoid", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicBool", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicInt8", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicInt16", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicInt32", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicInt64", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicUInt8", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicUInt16", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicUInt32", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicUInt64", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicFloat32", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicFloat64", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeAtomicReal", NodeTypeCategory::Type, {}),
	NodeTypeInfo("TypeSymbol", NodeTypeCategory::Type, {FieldTag::TypeSymbol_TemplateEvalArgs}),
	NodeTypeInfo("TypeAccessUnary", NodeTypeCategory::Type, {FieldTag::TypeAccessUnary_Arg}),
	NodeTypeInfo("TypeAccess", NodeTypeCategory::Type, {FieldTag::TypeAccess_Args}),
	NodeTypeInfo("TypeGroup", NodeTypeCategory::Type, {FieldTag::TypeGroup_Arg}),
	NodeTypeInfo("TypeFunction", NodeTypeCategory::Expr, {FieldTag::TypeFunction_Return, FieldTag::TypeFunction_Args}),
	NodeTypeInfo("ExprLiteralBool", NodeTypeCategory::Expr, {FieldTag::ExprLiteralBool_Value}),
	NodeTypeInfo("ExprLiteralInt8", NodeTypeCategory::Expr, {FieldTag::ExprLiteralInt8_Value}),
	NodeTypeInfo("ExprLiteralInt16", NodeTypeCategory::Expr, {FieldTag::ExprLiteralInt16_Value}),
	NodeTypeInfo("ExprLiteralInt32", NodeTypeCategory::Expr, {FieldTag::ExprLiteralInt32_Value}),
	NodeTypeInfo("ExprLiteralInt64", NodeTypeCategory::Expr, {FieldTag::ExprLiteralInt64_Value}),
	NodeTypeInfo("ExprLiteralUInt8", NodeTypeCategory::Expr, {FieldTag::ExprLiteralUInt8_Value}),
	NodeTypeInfo("ExprLiteralUInt16", NodeTypeCategory::Expr, {FieldTag::ExprLiteralUInt16_Value}),
	NodeTypeInfo("ExprLiteralUInt32", NodeTypeCategory::Expr, {FieldTag::ExprLiteralUInt32_Value}),
	NodeTypeInfo("ExprLiteralUInt64", NodeTypeCategory::Expr, {FieldTag::ExprLiteralUInt64_Value}),
	NodeTypeInfo("ExprLiteralChar8", NodeTypeCategory::Expr, {FieldTag::ExprLiteralChar8_Value}),
	NodeTypeInfo("ExprLiteralChar16", NodeTypeCategory::Expr, {FieldTag::ExprLiteralChar16_Value}),
	NodeTypeInfo("ExprLiteralChar32", NodeTypeCategory::Expr, {FieldTag::ExprLiteralChar32_Value}),
	NodeTypeInfo("ExprLiteralFloat32", NodeTypeCategory::Expr, {FieldTag::ExprLiteralFloat32_Value}),
	NodeTypeInfo("ExprLiteralFloat64", NodeTypeCategory::Expr, {FieldTag::ExprLiteralFloat64_Value}),
	NodeTypeInfo("ExprLiteralReal", NodeTypeCategory::Expr, {FieldTag::ExprLiteralReal_Value}),
	NodeTypeInfo("ExprSymbol", NodeTypeCategory::Expr, {FieldTag::ExprSymbol_TemplateEvalArgs}),
	NodeTypeInfo("ExprAccessUnary", NodeTypeCategory::Expr, {FieldTag::ExprAccessUnary_Arg}),
	NodeTypeInfo("ExprAccess", NodeTypeCategory::Expr, {FieldTag::ExprAccess_Args}),
	NodeTypeInfo("ExprGroup", NodeTypeCategory::Expr, {FieldTag::ExprGroup_Arg}),
	NodeTypeInfo("ExprCall", NodeTypeCategory::Expr, {FieldTag::ExprCall_Callee, FieldTag::ExprCall_Args}),
	NodeTypeInfo("ExprAdd", NodeTypeCategory::Expr, {FieldTag::ExprAdd_Args}),
	NodeTypeInfo("ExprIncPre", NodeTypeCategory::Expr, {FieldTag::ExprIncPre_Arg}),
	NodeTypeInfo("ExprIncPost", NodeTypeCategory::Expr, {FieldTag::ExprIncPost_Arg}),
	NodeTypeInfo("ExprSub", NodeTypeCategory::Expr, {FieldTag::ExprSub_LHS, FieldTag::ExprSub_RHS}),
	NodeTypeInfo("ExprNeg", NodeTypeCategory::Expr, {FieldTag::ExprNeg_Arg}),
	NodeTypeInfo("ExprDecPre", NodeTypeCategory::Expr, {FieldTag::ExprDecPre_Arg}),
	NodeTypeInfo("ExprDecPost", NodeTypeCategory::Expr, {FieldTag::ExprDecPost_Arg}),
	NodeTypeInfo("ExprMul", NodeTypeCategory::Expr, {FieldTag::ExprMul_Args}),
	NodeTypeInfo("ExprExp", NodeTypeCategory::Expr, {FieldTag::ExprExp_LHS, FieldTag::ExprExp_RHS}),
	NodeTypeInfo("ExprDiv", NodeTypeCategory::Expr, {FieldTag::ExprDiv_LHS, FieldTag::ExprDiv_RHS}),
	NodeTypeInfo("ExprDivInt", NodeTypeCategory::Expr, {FieldTag::ExprDivInt_LHS, FieldTag::ExprDivInt_RHS}),
	NodeTypeInfo("ExprDivReal", NodeTypeCategory::Expr, {FieldTag::ExprDivReal_LHS, FieldTag::ExprDivReal_RHS}),
	NodeTypeInfo("ExprMod", NodeTypeCategory::Expr, {FieldTag::ExprMod_LHS, FieldTag::ExprMod_RHS}),
	NodeTypeInfo("ExprBitNot", NodeTypeCategory::Expr, {FieldTag::ExprBitNot_Arg}),
	NodeTypeInfo("ExprBitAnd", NodeTypeCategory::Expr, {FieldTag::ExprBitAnd_Args}),
	NodeTypeInfo("ExprBitOr", NodeTypeCategory::Expr, {FieldTag::ExprBitOr_Args}),
	NodeTypeInfo("ExprBitXor", NodeTypeCategory::Expr, {FieldTag::ExprBitXor_Args}),
	NodeTypeInfo("ExprBitShL", NodeTypeCategory::Expr, {FieldTag::ExprBitShL_LHS, FieldTag::ExprBitShL_RHS}),
	NodeTypeInfo("ExprBitShR", NodeTypeCategory::Expr, {FieldTag::ExprBitShR_LHS, FieldTag::ExprBitShR_RHS}),
	NodeTypeInfo("ExprLT", NodeTypeCategory::Expr, {FieldTag::ExprLT_LHS, FieldTag::ExprLT_RHS}),
	NodeTypeInfo("ExprLE", NodeTypeCategory::Expr, {FieldTag::ExprLE_LHS, FieldTag::ExprLE_RHS}),
	NodeTypeInfo("ExprGT", NodeTypeCategory::Expr, {FieldTag::ExprGT_LHS, FieldTag::ExprGT_RHS}),
	NodeTypeInfo("ExprGE", NodeTypeCategory::Expr, {FieldTag::ExprGE_LHS, FieldTag::ExprGE_RHS}),
	NodeTypeInfo("ExprNE", NodeTypeCategory::Expr, {FieldTag::ExprNE_LHS, FieldTag::ExprNE_RHS}),
	NodeTypeInfo("ExprEQ", NodeTypeCategory::Expr, {FieldTag::ExprEQ_LHS, FieldTag::ExprEQ_RHS}),
	NodeTypeInfo("ExprBoolNot", NodeTypeCategory::Expr, {FieldTag::ExprBoolNot_Arg}),
	NodeTypeInfo("ExprBoolAnd", NodeTypeCategory::Expr, {FieldTag::ExprBoolAnd_Args}),
	NodeTypeInfo("ExprBoolOr", NodeTypeCategory::Expr, {FieldTag::ExprBoolOr_Args}),
	NodeTypeInfo("ExprBoolImplies", NodeTypeCategory::Expr, {FieldTag::ExprBoolImplies_Args}),
	NodeTypeInfo("ExprAddAssign", NodeTypeCategory::Expr, {FieldTag::ExprAddAssign_LHS, FieldTag::ExprAddAssign_RHS}),
	NodeTypeInfo("ExprSubAssign", NodeTypeCategory::Expr, {FieldTag::ExprSubAssign_LHS, FieldTag::ExprSubAssign_RHS}),
	NodeTypeInfo("ExprMulAssign", NodeTypeCategory::Expr, {FieldTag::ExprMulAssign_LHS, FieldTag::ExprMulAssign_RHS}),
	NodeTypeInfo("ExprExpAssign", NodeTypeCategory::Expr, {FieldTag::ExprExpAssign_LHS, FieldTag::ExprExpAssign_RHS}),
	NodeTypeInfo("ExprDivAssign", NodeTypeCategory::Expr, {FieldTag::ExprDivAssign_LHS, FieldTag::ExprDivAssign_RHS}),
	NodeTypeInfo("ExprDivIntAssign", NodeTypeCategory::Expr, {FieldTag::ExprDivIntAssign_LHS, FieldTag::ExprDivIntAssign_RHS}),
	NodeTypeInfo("ExprDivRealAssign", NodeTypeCategory::Expr, {FieldTag::ExprDivRealAssign_LHS, FieldTag::ExprDivRealAssign_RHS}),
	NodeTypeInfo("ExprModAssign", NodeTypeCategory::Expr, {FieldTag::ExprModAssign_LHS, FieldTag::ExprModAssign_RHS}),
	NodeTypeInfo("ExprBitAndAssign", NodeTypeCategory::Expr, {FieldTag::ExprBitAndAssign_LHS, FieldTag::ExprBitAndAssign_RHS}),
	NodeTypeInfo("ExprBitOrAssign", NodeTypeCategory::Expr, {FieldTag::ExprBitOrAssign_LHS, FieldTag::ExprBitOrAssign_RHS}),
	NodeTypeInfo("ExprBitXorAssign", NodeTypeCategory::Expr, {FieldTag::ExprBitXorAssign_LHS, FieldTag::ExprBitXorAssign_RHS}),
	NodeTypeInfo("ExprBitShLAssign", NodeTypeCategory::Expr, {FieldTag::ExprBitShLAssign_LHS, FieldTag::ExprBitShLAssign_RHS}),
	NodeTypeInfo("ExprBitShRAssign", NodeTypeCategory::Expr, {FieldTag::ExprBitShRAssign_LHS, FieldTag::ExprBitShRAssign_RHS}),
	NodeTypeInfo("ExprAssign", NodeTypeCategory::Expr, {FieldTag::ExprAssign_LHS, FieldTag::ExprAssign_RHS}),
	NodeTypeInfo("StmtEmpty", NodeTypeCategory::Stmt, {}),
	NodeTypeInfo("StmtExpr", NodeTypeCategory::Stmt, {FieldTag::StmtExpr_Expr}),
	NodeTypeInfo("StmtDecl", NodeTypeCategory::Stmt, {FieldTag::StmtDecl_Decl}),
	NodeTypeInfo("StmtReturn", NodeTypeCategory::Stmt, {FieldTag::StmtReturn_Arg}),
	NodeTypeInfo("StmtContinue", NodeTypeCategory::Stmt, {FieldTag::StmtContinue_Name}),
	NodeTypeInfo("StmtBreak", NodeTypeCategory::Stmt, {FieldTag::StmtBreak_Name}),
	NodeTypeInfo("StmtIf", NodeTypeCategory::Stmt, {FieldTag::StmtIf_Condition, FieldTag::StmtIf_Then, FieldTag::StmtIf_Else}),
	NodeTypeInfo("StmtWhile", NodeTypeCategory::Stmt, {FieldTag::StmtWhile_Condition, FieldTag::StmtWhile_Body, FieldTag::StmtWhile_Name}),
	NodeTypeInfo("StmtFor", NodeTypeCategory::Stmt, {FieldTag::StmtFor_Decls, FieldTag::StmtFor_Condition, FieldTag::StmtFor_Steps, FieldTag::StmtFor_Body, FieldTag::StmtFor_Name}),
	NodeTypeInfo("StmtForEach", NodeTypeCategory::Stmt, {FieldTag::StmtForEach_Decl, FieldTag::StmtForEach_Sequence, FieldTag::StmtForEach_Body, FieldTag::StmtForEach_Name}),
	NodeTypeInfo("StmtBlock", NodeTypeCategory::Stmt, {FieldTag::StmtBlock_Stmts}),
	NodeTypeInfo("DeclVariable", NodeTypeCategory::Decl, {FieldTag::DeclVariable_Type, FieldTag::DeclVariable_TemplateDeclArgs, FieldTag::DeclVariable_Initial}),
	NodeTypeInfo("DeclFunction", NodeTypeCategory::Decl, {FieldTag::DeclFunction_Return, FieldTag::DeclFunction_TemplateDeclArgs, FieldTag::DeclFunction_Args, FieldTag::DeclFunction_Body}),
	NodeTypeInfo("DeclClass", NodeTypeCategory::Decl, {FieldTag::DeclClass_TemplateDeclArgs, FieldTag::DeclClass_Inherits, FieldTag::DeclClass_Members}),
	NodeTypeInfo("DeclNamespace", NodeTypeCategory::Decl, {FieldTag::DeclNamespace_Members}),
	NodeTypeInfo("Import", NodeTypeCategory::Import, {FieldTag::Import_Path}),
	NodeTypeInfo("Unit", NodeTypeCategory::Unit, {FieldTag::Unit_Members})
};
}

bool evalNodeType(const std::string &text, NodeType &value) {
	for (size_t i = 0; i < sizeof(nodeTypeInfos) / sizeof(NodeTypeInfo); ++i) {
		if (nodeTypeInfos[i].getName() == text) {
			value = static_cast<NodeType>(i);
			return true;
		}
	}

	return false;
}

bool evalFieldTag(NodeType nodeType, const std::string &text, FieldTag &value) {
	for (FieldTag j : nodeTypeInfos[static_cast<ssize_t>(nodeType)].getFields()) {
		if (FieldTagInfo::get(j).getName() == text) {
			value = j;
			return true;
		}
	}

	return false;
}

std::ostream &operator<<(std::ostream &os, NodeType value) {
	os << NodeTypeInfo::get(value).getName();
	return os;
}

std::ostream &operator<<(std::ostream &os, NodeTypeCategory value) {
	switch (value) {
		case NodeTypeCategory::None:
			os << "None";
			break;
		case NodeTypeCategory::Internal:
			os << "Internal";
			break;
		case NodeTypeCategory::Type:
			os << "Type";
			break;
		case NodeTypeCategory::Expr:
			os << "Expr";
			break;
		case NodeTypeCategory::Stmt:
			os << "Stmt";
			break;
		case NodeTypeCategory::Decl:
			os << "Decl";
			break;
		case NodeTypeCategory::Import:
			os << "Import";
			break;
		case NodeTypeCategory::Unit:
			os << "Unit";
			break;
	}

	return os;
}

const NodeTypeInfo &NodeTypeInfo::get(NodeType type) {
	return nodeTypeInfos[static_cast<int>(type)];
}

NodeTypeInfo::NodeTypeInfo(std::string name, NodeTypeCategory category, std::initializer_list<FieldTag> fields) : name(name), category(category), fields(fields) {}

const std::string &NodeTypeInfo::getName() const {
	return name;
}

NodeTypeCategory NodeTypeInfo::getCategory() const {
	return category;
}

const std::vector<FieldTag> &NodeTypeInfo::getFields() const {
	return fields;
}
}
