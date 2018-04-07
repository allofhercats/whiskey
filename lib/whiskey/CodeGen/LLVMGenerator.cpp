#include <whiskey/CodeGen/LLVMGenerator.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wdeprecated"
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Verifier.h>
#pragma clang diagnostic pop

#include <whiskey/AST/Node.hpp>

namespace whiskey {
llvm::Type *LLVMGenerator::generateTypeFunction(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::TypeFunction, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::TypeFunction_Return), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::TypeFunction_Return).getFormat(), FieldFormat::Node, "Field of unexpected format.");
	W_ASSERT_TRUE(node.hasField(FieldTag::TypeFunction_Args), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::TypeFunction_Args).getFormat(), FieldFormat::NodeVector, "Field of unexpected format.");

	llvm::Type *result = generateType(node.getField(FieldTag::TypeFunction_Return).getNode());
	
	std::vector<llvm::Type *> args;
	for (const Node &i : node.getField(FieldTag::TypeFunction_Args).getNodeVector()) {
		args.push_back(generateType(i));
	}

	return llvm::FunctionType::get(result, args, false);
}

llvm::Value *LLVMGenerator::generateExprLiteralBool(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralBool, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralBool_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralBool_Value).getFormat(), FieldFormat::UInt, "Field of unexpected format.");
	W_ASSERT_LE(node.getField(FieldTag::ExprLiteralBool_Value).getUInt(), 1u, "Literal value out of range.");

	return llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvmCtx), node.getField(FieldTag::ExprLiteralBool_Value).getUInt(), false);
}

llvm::Value *LLVMGenerator::generateExprLiteralInt8(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralInt8, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralInt8_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralInt8_Value).getFormat(), FieldFormat::Int, "Field of unexpected format.");
	W_ASSERT_LE(node.getField(FieldTag::ExprLiteralInt8_Value).getInt(), SCHAR_MAX, "Literal value out of range.");
	W_ASSERT_GE(node.getField(FieldTag::ExprLiteralInt8_Value).getInt(), SCHAR_MIN, "Literal value out of range.");

	return llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralInt8_Value).getInt()), true);
}

llvm::Value *LLVMGenerator::generateExprLiteralInt16(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralInt16, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralInt16_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralInt16_Value).getFormat(), FieldFormat::Int, "Field of unexpected format.");
	W_ASSERT_LE(node.getField(FieldTag::ExprLiteralInt16_Value).getInt(), SHRT_MAX, "Literal value out of range.");
	W_ASSERT_GE(node.getField(FieldTag::ExprLiteralInt16_Value).getInt(), SHRT_MIN, "Literal value out of range.");

	return llvm::ConstantInt::get(llvm::Type::getInt16Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralInt16_Value).getInt()), true);
}

llvm::Value *LLVMGenerator::generateExprLiteralInt32(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralInt32, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralInt32_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralInt32_Value).getFormat(), FieldFormat::Int, "Field of unexpected format.");
	W_ASSERT_LE(node.getField(FieldTag::ExprLiteralInt32_Value).getInt(), INT_MAX, "Literal value out of range.");
	W_ASSERT_GE(node.getField(FieldTag::ExprLiteralInt32_Value).getInt(), INT_MIN, "Literal value out of range.");

	return llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralInt32_Value).getInt()), true);
}

llvm::Value *LLVMGenerator::generateExprLiteralInt64(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralInt64, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralInt64_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralInt64_Value).getFormat(), FieldFormat::Int, "Field of unexpected format.");

	return llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralInt64_Value).getInt()), true);
}

llvm::Value *LLVMGenerator::generateExprLiteralUInt8(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralUInt8, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralUInt8_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralUInt8_Value).getFormat(), FieldFormat::UInt, "Field of unexpected format.");
	W_ASSERT_LE(node.getField(FieldTag::ExprLiteralUInt8_Value).getUInt(), static_cast<uint64_t>(UCHAR_MAX), "Literal value out of range.");

	return llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralUInt8_Value).getUInt()), false);
}

llvm::Value *LLVMGenerator::generateExprLiteralUInt16(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralUInt16, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralUInt16_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralUInt16_Value).getFormat(), FieldFormat::UInt, "Field of unexpected format.");
	W_ASSERT_LE(node.getField(FieldTag::ExprLiteralUInt16_Value).getUInt(), static_cast<uint64_t>(USHRT_MAX), "Literal value out of range.");

	return llvm::ConstantInt::get(llvm::Type::getInt16Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralUInt16_Value).getUInt()), false);
}

llvm::Value *LLVMGenerator::generateExprLiteralUInt32(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralUInt32, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralUInt32_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralUInt32_Value).getFormat(), FieldFormat::UInt, "Field of unexpected format.");
	W_ASSERT_LE(node.getField(FieldTag::ExprLiteralUInt32_Value).getUInt(), static_cast<uint64_t>(UINT_MAX), "Literal value out of range.");

	return llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralUInt32_Value).getUInt()), false);
}

llvm::Value *LLVMGenerator::generateExprLiteralUInt64(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralUInt64, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralUInt64_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralUInt64_Value).getFormat(), FieldFormat::UInt, "Field of unexpected format.");

	return llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvmCtx), static_cast<uint64_t>(node.getField(FieldTag::ExprLiteralUInt64_Value).getUInt()), false);
}

llvm::Value *LLVMGenerator::generateExprLiteralFloat32(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralFloat32, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralFloat32_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralFloat32_Value).getFormat(), FieldFormat::Real, "Field of unexpected format.");

	return llvm::ConstantFP::get(llvm::Type::getFloatTy(llvmCtx), node.getField(FieldTag::ExprLiteralFloat32_Value).getReal());
}

llvm::Value *LLVMGenerator::generateExprLiteralFloat64(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralFloat64, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralFloat64_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralFloat64_Value).getFormat(), FieldFormat::Real, "Field of unexpected format.");

	return llvm::ConstantFP::get(llvm::Type::getDoubleTy(llvmCtx), node.getField(FieldTag::ExprLiteralFloat64_Value).getReal());
}

llvm::Value *LLVMGenerator::generateExprLiteralReal(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprLiteralReal, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprLiteralReal_Value), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprLiteralReal_Value).getFormat(), FieldFormat::Real, "Field of unexpected format.");

	return llvm::ConstantFP::get(llvm::Type::getFP128Ty(llvmCtx), node.getField(FieldTag::ExprLiteralReal_Value).getReal());
}

llvm::Value *LLVMGenerator::generateExprCall(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprCall, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprCall_Callee), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprCall_Callee).getFormat(), FieldFormat::Node, "Field of unexpected format.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprCall_Args), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprCall_Args).getFormat(), FieldFormat::NodeVector, "Field of unexpected format.");

	llvm::Value *callee = generateExpr(node.getField(FieldTag::ExprCall_Callee).getNode());

	std::vector<llvm::Value *> args;
	for (const Node &i : node.getField(FieldTag::ExprCall_Args).getNodeVector()) {
		args.push_back(generateExpr(i));
	}

	return llvmBuilder.CreateCall(callee, args);
}

llvm::Value *LLVMGenerator::generateExprAdd(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprAdd, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprAdd_Args), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprAdd_Args).getFormat(), FieldFormat::NodeVector, "Field of unexpected format.");
	W_ASSERT_GE(node.getField(FieldTag::ExprAdd_Args).getNodeVector().size(), 2u, "Not enough arguments to operator.");

	llvm::Value *rtn = generateExpr(node.getField(FieldTag::ExprAdd_Args).getNodeVector().front());
	
	std::vector<Node>::const_iterator i = node.getField(FieldTag::ExprAdd_Args).getNodeVector().cbegin();
	std::vector<Node>::const_iterator e = node.getField(FieldTag::ExprAdd_Args).getNodeVector().cend();
	++i;

	while (i != e) {
		llvm::Value *tmp = generateExpr(*i);
		if (rtn->getType()->isFloatingPointTy()) {
			rtn = llvmBuilder.CreateFAdd(rtn, tmp);
		} else {
			rtn = llvmBuilder.CreateAdd(rtn, tmp);
		}

		++i;
	}

	return rtn;
}

llvm::Value *LLVMGenerator::generateExprNeg(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprNeg, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprNeg_Arg), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprNeg_Arg).getFormat(), FieldFormat::Node, "Field of unexpected format.");
	
	llvm::Value *tmp = generateExpr(node.getField(FieldTag::ExprNeg_Arg).getNode());
	if (tmp->getType()->isFloatingPointTy()) {
		return llvmBuilder.CreateFNeg(tmp);
	} else {
		return llvmBuilder.CreateNeg(tmp);
	}
}

llvm::Value *LLVMGenerator::generateExprMul(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::ExprMul, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::ExprMul_Args), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::ExprMul_Args).getFormat(), FieldFormat::NodeVector, "Field of unexpected format.");
	W_ASSERT_GE(node.getField(FieldTag::ExprMul_Args).getNodeVector().size(), 2u, "Not enough arguments to operator.");

	llvm::Value *rtn = generateExpr(node.getField(FieldTag::ExprMul_Args).getNodeVector().front());

	std::vector<Node>::const_iterator i = node.getField(FieldTag::ExprMul_Args).getNodeVector().cbegin();
	std::vector<Node>::const_iterator e = node.getField(FieldTag::ExprMul_Args).getNodeVector().cend();
	++i;

	while (i != e) {
		llvm::Value *tmp = generateExpr(*i);
		if (rtn->getType()->isFloatingPointTy()) {
			rtn = llvmBuilder.CreateFMul(rtn, tmp);
		} else {
			rtn = llvmBuilder.CreateMul(rtn, tmp);
		}

		++i;
	}

	return rtn;
}

// llvm::Value *LLVMGenerator::generateExprDivInt(const Node &node) {
// 	if (node.getType() != NodeType::ExprNeg) {
// 		msgs.describe() << __FUNCTION__ << " can only generate ExprNeg nodes";
// 		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
// 		return nullptr;
// 	}

// 	if (!node.hasField(FieldTag::ExprNeg_Arg)) {
// 		msgs.describe() << "ExprNeg node is missing ExprNeg_Arg field";
// 		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
// 		return nullptr;
// 	}

// 	if (node.getField(FieldTag::ExprNeg_Arg).getFormat() != FieldFormat::Node) {
// 		msgs.describe() << "ExprNeg_Arg field does not contain node";
// 		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
// 		return nullptr;
// 	}

// 	llvm::Value *tmp = generateExpr(node.getField(FieldTag::ExprNeg_Arg).getNode());
// 	if (tmp == nullptr) {
// 		return nullptr;
// 	}

// 	if (!tmp->getType()->isIntegerTy() && !tmp->getType()->isFloatingPointTy()) {
// 		msgs.describe() << "operator - only applies to integer and floating point types";
// 		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
// 		return nullptr;
// 	}

// 	if (tmp->getType()->isFloatingPointTy()) {
// 		return llvmBuilder.CreateFNeg(tmp);
// 	} else {
// 		return llvmBuilder.CreateNeg(tmp);
// 	}
// }

void LLVMGenerator::generateStmtReturn(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::StmtReturn, "Can only generate node of given type.");

	if (!node.hasField(FieldTag::StmtReturn_Arg)) {
		llvmBuilder.CreateRetVoid();
	} else {
		W_ASSERT_EQ(node.getField(FieldTag::StmtReturn_Arg).getFormat(), FieldFormat::Node, "Field of unexpected format.");

		llvmBuilder.CreateRet(generateExpr(node.getField(FieldTag::StmtReturn_Arg).getNode()));
	}
}

void LLVMGenerator::generateStmtBlock(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::StmtBlock, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::StmtBlock_Stmts), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::StmtBlock_Stmts).getFormat(), FieldFormat::NodeVector, "Field of unexpected format.");

	for (const Node &i : node.getField(FieldTag::StmtBlock_Stmts).getNodeVector()) {
		generateStmt(i);
	}
}

LLVMGenerator::LLVMGenerator() : llvmBuilder(llvmCtx) {
	llvmModule = std::make_unique<llvm::Module>("jeffrey", llvmCtx);
}

llvm::Type *LLVMGenerator::generateType(const Node &node) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch (node.getType()) {
		case NodeType::TypeVoid:
			return llvm::Type::getVoidTy(llvmCtx);
		case NodeType::TypeAtomicBool:
			return llvm::Type::getInt1Ty(llvmCtx);
		case NodeType::TypeAtomicInt8:
			return llvm::Type::getInt8Ty(llvmCtx);
		case NodeType::TypeAtomicInt16:
			return llvm::Type::getInt16Ty(llvmCtx);
		case NodeType::TypeAtomicInt32:
			return llvm::Type::getInt32Ty(llvmCtx);
		case NodeType::TypeAtomicInt64:
			return llvm::Type::getInt64Ty(llvmCtx);
		case NodeType::TypeAtomicUInt8:
			return llvm::Type::getInt8Ty(llvmCtx);
		case NodeType::TypeAtomicUInt16:
			return llvm::Type::getInt16Ty(llvmCtx);
		case NodeType::TypeAtomicUInt32:
			return llvm::Type::getInt32Ty(llvmCtx);
		case NodeType::TypeAtomicUInt64:
			return llvm::Type::getInt64Ty(llvmCtx);
		case NodeType::TypeAtomicFloat32:
			return llvm::Type::getFloatTy(llvmCtx);
		case NodeType::TypeAtomicFloat64:
			return llvm::Type::getDoubleTy(llvmCtx);
		case NodeType::TypeAtomicReal:
			return llvm::Type::getFP128Ty(llvmCtx);
		case NodeType::TypeFunction:
			return generateTypeFunction(node);
		default:
			W_ASSERT_UNREACHABLE("Unsupported type node.");
	}
#pragma clang diagnostic pop
}

llvm::Value *LLVMGenerator::generateExpr(const Node &node) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch (node.getType()) {
		case NodeType::ExprLiteralBool:
			return generateExprLiteralBool(node);
		case NodeType::ExprLiteralInt8:
			return generateExprLiteralInt8(node);
		case NodeType::ExprLiteralInt16:
			return generateExprLiteralInt16(node);
		case NodeType::ExprLiteralInt32:
			return generateExprLiteralInt32(node);
		case NodeType::ExprLiteralInt64:
			return generateExprLiteralInt64(node);
		case NodeType::ExprLiteralUInt8:
			return generateExprLiteralUInt8(node);
		case NodeType::ExprLiteralUInt16:
			return generateExprLiteralUInt16(node);
		case NodeType::ExprLiteralUInt32:
			return generateExprLiteralUInt32(node);
		case NodeType::ExprLiteralUInt64:
			return generateExprLiteralUInt64(node);
		case NodeType::ExprLiteralFloat32:
			return generateExprLiteralFloat32(node);
		case NodeType::ExprLiteralFloat64:
			return generateExprLiteralFloat64(node);
		case NodeType::ExprLiteralReal:
			return generateExprLiteralReal(node);
		case NodeType::ExprCall:
			return generateExprCall(node);
		case NodeType::ExprAdd:
			return generateExprAdd(node);
		case NodeType::ExprNeg:
			return generateExprNeg(node);
		case NodeType::ExprMul:
			return generateExprMul(node);
		default:
			W_ASSERT_UNREACHABLE("Unsupported expression node.");
	}
#pragma clang diagnostic pop
}

void LLVMGenerator::generateStmt(const Node &node) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch (node.getType()) {
		case NodeType::StmtReturn:
			generateStmtReturn(node);
			break;
		case NodeType::StmtBlock:
			generateStmtBlock(node);
			break;
		default:
			W_ASSERT_UNREACHABLE("Unsupported statement node.");
	}
#pragma clang diagnostic pop
}

llvm::Function *LLVMGenerator::generateDeclFunction(const Node &node) {
	W_ASSERT_EQ(node.getType(), NodeType::DeclFunction, "Can only generate node of given type.");
	W_ASSERT_TRUE(node.hasField(FieldTag::DeclFunction_Return), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::DeclFunction_Return).getFormat(), FieldFormat::Node, "Field of unexpected format.");
	W_ASSERT_FALSE(node.hasField(FieldTag::DeclFunction_TemplateDeclArgs) && !node.getField(FieldTag::DeclFunction_TemplateDeclArgs).getNodeVector().empty(), "Unsupported template arguments.");
	W_ASSERT_TRUE(node.hasField(FieldTag::DeclFunction_Args), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::DeclFunction_Args).getFormat(), FieldFormat::NodeVector, "Field of unexpected format.");
	W_ASSERT_TRUE(node.hasField(FieldTag::DeclFunction_Body), "Required field missing.");
	W_ASSERT_EQ(node.getField(FieldTag::DeclFunction_Body).getFormat(), FieldFormat::Node, "Field of unexpected format.");
	W_ASSERT_FALSE(node.getToken().getText().empty(), "Function requires non-empty name.");
	
	llvm::Type *ret = generateType(node.getField(FieldTag::DeclFunction_Return).getNode());
	std::vector<llvm::Type *> args;
	for (const Node &i : node.getField(FieldTag::DeclFunction_Args).getNodeVector()) {
		W_ASSERT_EQ(i.getType(), NodeType::DeclVariable, "Function arguments must be of type '" << NodeType::DeclVariable << "'.");
		
		args.push_back(generateType(i.getField(FieldTag::DeclVariable_Type).getNode()));
	}

	llvm::FunctionType *proto = llvm::FunctionType::get(ret, args, false);

	llvm::Function *func = llvm::Function::Create(proto, llvm::Function::ExternalLinkage, node.getToken().getText(), llvmModule.get());

	auto fi = func->arg_begin();
	auto fe = func->arg_end();
	auto ni = node.getField(FieldTag::DeclFunction_Args).getNodeVector().cbegin();
	auto ne = node.getField(FieldTag::DeclFunction_Args).getNodeVector().cend();

	while (fi != fe && ni != ne) {
		W_ASSERT_FALSE(ni->getToken().getText().empty(), "Function argument names must be non-empty.");
		fi->setName(ni->getToken().getText());
		++fi;
		++ni;
	}

	llvm::BasicBlock *bb = llvm::BasicBlock::Create(llvmCtx, "entry", func);
	llvmBuilder.SetInsertPoint(bb);

	generateStmtBlock(node.getField(FieldTag::DeclFunction_Body).getNode());

	if (llvm::verifyFunction(*func, &llvm::errs())) {
		llvm::errs().flush();
		func->eraseFromParent();
		W_ASSERT_UNREACHABLE("Unable to verify function.");
	}

	return func;
}
}
