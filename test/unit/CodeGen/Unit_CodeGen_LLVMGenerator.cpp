#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/CodeGen/LLVMGenerator.hpp>

using namespace whiskey;

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeVoid) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeVoid);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isVoidTy());
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicBool) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicBool);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 1);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicInt8) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicInt8);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 8);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicInt16) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicInt16);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 16);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicInt32) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicInt32);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 32);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicInt64) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicInt64);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 64);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicUInt8) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicUInt8);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 8);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicUInt16) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicUInt16);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 16);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicUInt32) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicUInt32);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 32);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicUInt64) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicUInt64);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isIntegerTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 64);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicFloat32) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicFloat32);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isFloatingPointTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 32);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicFloat64) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicFloat64);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isFloatingPointTy());
	ASSERT_EQ(ir->getPrimitiveSizeInBits(), 64);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeAtomicReal) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeAtomicReal);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isFloatingPointTy());
	ASSERT_GE(ir->getPrimitiveSizeInBits(), 64);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeFunction_Void) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldNode(FieldTag::TypeFunction_Return, Node(NodeType::TypeVoid));
	ast.setFieldNodeVector(FieldTag::TypeFunction_Args);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isFunctionTy());
	const llvm::FunctionType *ft = static_cast<const llvm::FunctionType *>(ir);

	ASSERT_TRUE(ft->getReturnType()->isVoidTy());
	ASSERT_EQ(ft->getNumParams(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeFunction_Int32) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldNode(FieldTag::TypeFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNodeVector(FieldTag::TypeFunction_Args);

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isFunctionTy());
	const llvm::FunctionType *ft = static_cast<const llvm::FunctionType *>(ir);

	ASSERT_TRUE(ft->getReturnType()->isIntegerTy());
	ASSERT_EQ(ft->getReturnType()->getPrimitiveSizeInBits(), 32);
	ASSERT_EQ(ft->getNumParams(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeFunction_Int32Float32) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldNode(FieldTag::TypeFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNodeVector(FieldTag::TypeFunction_Args, {
		Node(NodeType::TypeAtomicFloat32)
	});

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isFunctionTy());
	const llvm::FunctionType *ft = static_cast<const llvm::FunctionType *>(ir);

	ASSERT_TRUE(ft->getReturnType()->isIntegerTy());
	ASSERT_EQ(ft->getReturnType()->getPrimitiveSizeInBits(), 32);
	ASSERT_EQ(ft->getNumParams(), 1);
	ASSERT_TRUE(ft->params()[0]->isFloatingPointTy());
	ASSERT_EQ(ft->params()[0]->getPrimitiveSizeInBits(), 32);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_TypeFunction_Int32Float32Float64) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldNode(FieldTag::TypeFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNodeVector(FieldTag::TypeFunction_Args, {
		Node(NodeType::TypeAtomicFloat32),
		Node(NodeType::TypeAtomicFloat64)
	});

	const llvm::Type *ir = gen.generateType(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->isFunctionTy());
	const llvm::FunctionType *ft = static_cast<const llvm::FunctionType *>(ir);

	ASSERT_TRUE(ft->getReturnType()->isIntegerTy());
	ASSERT_EQ(ft->getReturnType()->getPrimitiveSizeInBits(), 32);
	ASSERT_EQ(ft->getNumParams(), 2);
	ASSERT_TRUE(ft->params()[0]->isFloatingPointTy());
	ASSERT_EQ(ft->params()[0]->getPrimitiveSizeInBits(), 32);
	ASSERT_TRUE(ft->params()[1]->isFloatingPointTy());
	ASSERT_EQ(ft->params()[1]->getPrimitiveSizeInBits(), 64);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_TypeFunction_ArgsBadForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldNode(FieldTag::TypeFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNode(FieldTag::TypeFunction_Args, Node(NodeType::TypeAtomicFloat32));

	ASSERT_DEATH({
			gen.generateType(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_TypeFunction_ArgsMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldNode(FieldTag::TypeFunction_Return, Node(NodeType::TypeAtomicInt32));

	ASSERT_DEATH({
			gen.generateType(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_TypeFunction_ReturnBadForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldString(FieldTag::TypeFunction_Return, "int32");
	ast.setFieldNodeVector(FieldTag::TypeFunction_Args);

	ASSERT_DEATH({
			gen.generateType(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_TypeFunction_ReturnMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeFunction);
	ast.setFieldNodeVector(FieldTag::TypeFunction_Args);

	ASSERT_DEATH({
			gen.generateType(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_TypeGroup) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::TypeGroup);
	ast.setFieldNode(FieldTag::TypeGroup_Arg, Node(NodeType::TypeVoid));

	ASSERT_DEATH({
			gen.generateType(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralBool_True) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralBool);
	ast.setFieldUInt(FieldTag::ExprLiteralBool_Value, 1);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 1);

	ASSERT_EQ(ci->getZExtValue(), 1);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralBool_False) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralBool);
	ast.setFieldUInt(FieldTag::ExprLiteralBool_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 1);

	ASSERT_EQ(ci->getZExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralBool_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralBool);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralBool_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralBool);
	ast.setFieldInt(FieldTag::ExprLiteralBool_Value, 1);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralBool_OverflowMax) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralBool);
	ast.setFieldUInt(FieldTag::ExprLiteralBool_Value, 2);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt8_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldInt(FieldTag::ExprLiteralInt8_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getSExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt8_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getSExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt8_MinusFive) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldInt(FieldTag::ExprLiteralInt8_Value, -5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getSExtValue(), -5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt8_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldInt(FieldTag::ExprLiteralInt8_Value, 0x7f);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getSExtValue(), 0x7f);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt8_Min) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldInt(FieldTag::ExprLiteralInt8_Value, -0x80);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getSExtValue(), -0x80);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt8_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt8_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldUInt(FieldTag::ExprLiteralInt8_Value, 1);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt8_OverflowMax) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldInt(FieldTag::ExprLiteralInt8_Value, 0x80);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt8_OverflowMin) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt8);
	ast.setFieldInt(FieldTag::ExprLiteralInt8_Value, -0x81);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt16_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldInt(FieldTag::ExprLiteralInt16_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getSExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt16_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldInt(FieldTag::ExprLiteralInt16_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getSExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt16_MinusFive) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldInt(FieldTag::ExprLiteralInt16_Value, -5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getSExtValue(), -5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt16_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldInt(FieldTag::ExprLiteralInt16_Value, 0x7fff);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getSExtValue(), 0x7fff);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt16_Min) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldInt(FieldTag::ExprLiteralInt16_Value, -0x8000);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getSExtValue(), -0x8000);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt16_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt16_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldUInt(FieldTag::ExprLiteralInt16_Value, 1);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt16_OverflowMax) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldInt(FieldTag::ExprLiteralInt16_Value, 0x8000);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt16_OverflowMin) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt16);
	ast.setFieldInt(FieldTag::ExprLiteralInt16_Value, -0x8001);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt32_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldInt(FieldTag::ExprLiteralInt32_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getSExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt32_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldInt(FieldTag::ExprLiteralInt32_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getSExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt32_MinusFive) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldInt(FieldTag::ExprLiteralInt32_Value, -5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getSExtValue(), -5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt32_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldInt(FieldTag::ExprLiteralInt32_Value, 0x7fffffff);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getSExtValue(), 0x7fffffff);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt32_Min) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldInt(FieldTag::ExprLiteralInt32_Value, -0x80000000L);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getSExtValue(), -0x80000000L);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt32_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt32_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldUInt(FieldTag::ExprLiteralInt32_Value, 1);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt32_OverflowMax) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldInt(FieldTag::ExprLiteralInt32_Value, 0x80000000L);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt32_OverflowMin) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt32);
	ast.setFieldInt(FieldTag::ExprLiteralInt32_Value, -0x80000001L);

	ASSERT_DEATH({
			gen.generateExpr(ast);
		}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt64_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt64);
	ast.setFieldInt(FieldTag::ExprLiteralInt64_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getSExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt64_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt64);
	ast.setFieldInt(FieldTag::ExprLiteralInt64_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getSExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt64_MinusFive) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt64);
	ast.setFieldInt(FieldTag::ExprLiteralInt64_Value, -5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getSExtValue(), -5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt64_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt64);
	ast.setFieldInt(FieldTag::ExprLiteralInt64_Value, 0x7fffffffffffffff);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getSExtValue(), 0x7fffffffffffffff);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralInt64_Min) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt64);
	ast.setFieldInt(FieldTag::ExprLiteralInt64_Value, static_cast<int64_t>(-0x8000000000000000L));

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getSExtValue(), -0x8000000000000000L);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt64_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt64);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralInt64_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralInt64);
	ast.setFieldUInt(FieldTag::ExprLiteralInt64_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt8_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt8);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt8_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getZExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt8_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt8);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt8_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getZExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt8_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt8);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt8_Value, 0xff);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 8);

	ASSERT_EQ(ci->getZExtValue(), 0xff);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt8_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt8);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt8_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt8);
	ast.setFieldInt(FieldTag::ExprLiteralUInt8_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt8_OverflowMax) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt8);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt8_Value, 0x100);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt16_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt16);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt16_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getZExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt16_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt16);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt16_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getZExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt16_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt16);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt16_Value, 0xffff);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 16);

	ASSERT_EQ(ci->getZExtValue(), 0xffff);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt16_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt16);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt16_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt16);
	ast.setFieldInt(FieldTag::ExprLiteralUInt16_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt16_OverflowMax) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt16);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt16_Value, 0x10000);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt32_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt32);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt32_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getZExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt32_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt32);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt32_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getZExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt32_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt32);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt32_Value, 0xffffffff);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_EQ(ci->getZExtValue(), 0xffffffff);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt32_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt32);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt32_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt32);
	ast.setFieldInt(FieldTag::ExprLiteralUInt32_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt32_OverflowMax) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt32);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt32_Value, 0x100000000);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt64_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt64);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt64_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getZExtValue(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt64_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt64);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt64_Value, 5);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getZExtValue(), 5);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralUInt64_Max) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt64);
	ast.setFieldUInt(FieldTag::ExprLiteralUInt64_Value, 0xffffffffffffffffL);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantInt *ci = llvm::dyn_cast<llvm::ConstantInt>(ir);
	ASSERT_NE(ci, nullptr);

	ASSERT_TRUE(ci->getType()->isIntegerTy());
	ASSERT_EQ(ci->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_EQ(ci->getZExtValue(), 0xffffffffffffffffL);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt64_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt64);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralUInt64_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralUInt64);
	ast.setFieldInt(FieldTag::ExprLiteralUInt64_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralFloat32_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat32);
	ast.setFieldReal(FieldTag::ExprLiteralFloat32_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantFP *cfp = llvm::dyn_cast<llvm::ConstantFP>(ir);
	ASSERT_NE(cfp, nullptr);

	ASSERT_TRUE(cfp->getType()->isFloatingPointTy());
	ASSERT_EQ(cfp->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_TRUE(cfp->getValueAPF().compare(llvm::APFloat(0.0f)) == llvm::APFloat::cmpEqual);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralFloat32_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat32);
	ast.setFieldReal(FieldTag::ExprLiteralFloat32_Value, 5.0l);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantFP *cfp = llvm::dyn_cast<llvm::ConstantFP>(ir);
	ASSERT_NE(cfp, nullptr);

	ASSERT_TRUE(cfp->getType()->isFloatingPointTy());
	ASSERT_EQ(cfp->getType()->getPrimitiveSizeInBits(), 32);

	ASSERT_TRUE(cfp->getValueAPF().compare(llvm::APFloat(5.0f)) == llvm::APFloat::cmpEqual);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralFloat32_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat32);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralFloat32_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat32);
	ast.setFieldInt(FieldTag::ExprLiteralFloat32_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralFloat64_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat64);
	ast.setFieldReal(FieldTag::ExprLiteralFloat64_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantFP *cfp = llvm::dyn_cast<llvm::ConstantFP>(ir);
	ASSERT_NE(cfp, nullptr);

	ASSERT_TRUE(cfp->getType()->isFloatingPointTy());
	ASSERT_EQ(cfp->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_TRUE(cfp->getValueAPF().compare(llvm::APFloat(0.0)) == llvm::APFloat::cmpEqual);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralFloat64_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat64);
	ast.setFieldReal(FieldTag::ExprLiteralFloat64_Value, 5.0l);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantFP *cfp = llvm::dyn_cast<llvm::ConstantFP>(ir);
	ASSERT_NE(cfp, nullptr);

	ASSERT_TRUE(cfp->getType()->isFloatingPointTy());
	ASSERT_EQ(cfp->getType()->getPrimitiveSizeInBits(), 64);

	ASSERT_TRUE(cfp->getValueAPF().compare(llvm::APFloat(5.0)) == llvm::APFloat::cmpEqual);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralFloat64_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat64);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralFloat64_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralFloat64);
	ast.setFieldInt(FieldTag::ExprLiteralFloat64_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralReal_Zero) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralReal);
	ast.setFieldReal(FieldTag::ExprLiteralReal_Value, 0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantFP *cfp = llvm::dyn_cast<llvm::ConstantFP>(ir);
	ASSERT_NE(cfp, nullptr);

	ASSERT_TRUE(cfp->getType()->isFloatingPointTy());
	ASSERT_GE(cfp->getType()->getPrimitiveSizeInBits(), 64);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprLiteralReal_Five) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralReal);
	ast.setFieldReal(FieldTag::ExprLiteralReal_Value, 5.0l);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);

	const llvm::ConstantFP *cfp = llvm::dyn_cast<llvm::ConstantFP>(ir);
	ASSERT_NE(cfp, nullptr);

	ASSERT_TRUE(cfp->getType()->isFloatingPointTy());
	ASSERT_GE(cfp->getType()->getPrimitiveSizeInBits(), 64);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralReal_ValueMissing) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralReal);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprLiteralReal_ValueForm) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprLiteralReal);
	ast.setFieldInt(FieldTag::ExprLiteralReal_Value, 1);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprAdd_TwoInts) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::ExprLiteralInt8);
	ast0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	Node ast1 = Node(NodeType::ExprLiteralInt8);
	ast1.setFieldInt(FieldTag::ExprLiteralInt8_Value, -3);

	Node ast = Node(NodeType::ExprAdd);
	ast.setFieldNodeVector(FieldTag::ExprAdd_Args, {
		ast0,
		ast1
	});

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprAdd_ThreeInts) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::ExprLiteralInt8);
	ast0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	Node ast1 = Node(NodeType::ExprLiteralInt8);
	ast1.setFieldInt(FieldTag::ExprLiteralInt8_Value, -3);

	Node ast2 = Node(NodeType::ExprLiteralInt8);
	ast2.setFieldInt(FieldTag::ExprLiteralInt8_Value, 100);

	Node ast = Node(NodeType::ExprAdd);
	ast.setFieldNodeVector(FieldTag::ExprAdd_Args, {
		ast0,
		ast1,
		ast2
	});

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprAdd_OneInt) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::ExprLiteralInt8);
	ast0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	Node ast = Node(NodeType::ExprAdd);
	ast.setFieldNodeVector(FieldTag::ExprAdd_Args, {
		ast0
	});

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprAdd_NoArgs) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprAdd);
	ast.setFieldNodeVector(FieldTag::ExprAdd_Args);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprAdd_ArgNonExpr) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprAdd);
	ast.setFieldNodeVector(FieldTag::ExprAdd_Args, {
		Node(NodeType::TypeAtomicInt32)
	});

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprAdd_ArgsNonNodeVector) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprAdd);
	ast.setFieldInt(FieldTag::ExprAdd_Args, 0);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprAdd_MissingArgs) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprAdd);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprNeg_OneInt) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::ExprLiteralInt8);
	ast0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	Node ast = Node(NodeType::ExprNeg);
	ast.setFieldNode(FieldTag::ExprNeg_Arg, ast0);

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprNeg_ArgNonExpr) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprNeg);
	ast.setFieldNodeVector(FieldTag::ExprNeg_Arg, {
		Node(NodeType::TypeAtomicInt32)
	});

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprNeg_ArgNonNode) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprNeg);
	ast.setFieldInt(FieldTag::ExprNeg_Arg, 0);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprNeg_MissingArg) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprNeg);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprMul_TwoInts) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::ExprLiteralInt8);
	ast0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	Node ast1 = Node(NodeType::ExprLiteralInt8);
	ast1.setFieldInt(FieldTag::ExprLiteralInt8_Value, -3);

	Node ast = Node(NodeType::ExprMul);
	ast.setFieldNodeVector(FieldTag::ExprMul_Args, {
		ast0,
		ast1
	});

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_ExprMul_ThreeInts) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::ExprLiteralInt8);
	ast0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	Node ast1 = Node(NodeType::ExprLiteralInt8);
	ast1.setFieldInt(FieldTag::ExprLiteralInt8_Value, -3);

	Node ast2 = Node(NodeType::ExprLiteralInt8);
	ast2.setFieldInt(FieldTag::ExprLiteralInt8_Value, 100);

	Node ast = Node(NodeType::ExprMul);
	ast.setFieldNodeVector(FieldTag::ExprMul_Args, {
		ast0,
		ast1,
		ast2
	});

	const llvm::Value *ir = gen.generateExpr(ast);

	ASSERT_NE(ir, nullptr);
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprMul_OneInt) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::ExprLiteralInt8);
	ast0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);

	Node ast = Node(NodeType::ExprMul);
	ast.setFieldNodeVector(FieldTag::ExprMul_Args, {
		ast0
	});

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprMul_NoArgs) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprMul);
	ast.setFieldNodeVector(FieldTag::ExprMul_Args);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprMul_ArgNonExpr) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprMul);
	ast.setFieldNodeVector(FieldTag::ExprMul_Args, {
		Node(NodeType::TypeAtomicInt32)
	});

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprMul_ArgsNonNodeVector) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprMul);
	ast.setFieldInt(FieldTag::ExprMul_Args, 0);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_ExprMul_MissingArgs) {
	LLVMGenerator gen;

	Node ast = Node(NodeType::ExprMul);

	ASSERT_DEATH({
		gen.generateExpr(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_DeclFunction_WithReturnNoArgs) {
	LLVMGenerator gen;

	Node ast3 = Node(NodeType::ExprLiteralInt32);
	ast3.setFieldInt(FieldTag::ExprLiteralInt32_Value, 5);

	Node ast0 = Node(NodeType::StmtReturn);
	ast0.setFieldNode(FieldTag::StmtReturn_Arg, ast3);

	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast = Node(NodeType::DeclFunction, Token(TokenID::Symbol, "f"));
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args);
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	llvm::Function *ir = gen.generateDeclFunction(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->getReturnType()->isIntegerTy());
	ASSERT_EQ(ir->getReturnType()->getPrimitiveSizeInBits(), 32);
	ASSERT_STREQ(ir->getName().data(), "f");
	ASSERT_FALSE(ir->isVarArg());
	ASSERT_EQ(ir->arg_size(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_DeclFunction_NoReturnNoArgs) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);

	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast = Node(NodeType::DeclFunction, Token(TokenID::Symbol, "f"));
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node(NodeType::TypeVoid));
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args);
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	llvm::Function *ir = gen.generateDeclFunction(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->getReturnType()->isVoidTy());
	ASSERT_STREQ(ir->getName().data(), "f");
	ASSERT_FALSE(ir->isVarArg());
	ASSERT_EQ(ir->arg_size(), 0);
}

TEST(Unit_CodeGen_LLVMGenerator, Good_DeclFunction_NoReturnOneArg) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);
	
	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast2 = Node(NodeType::DeclVariable, Token(TokenID::Symbol, "x0"));
	ast2.setFieldNode(FieldTag::DeclVariable_Type, Node(NodeType::TypeAtomicInt32));

	Node ast = Node(NodeType::DeclFunction, Token(TokenID::Symbol, "f"));
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node(NodeType::TypeVoid));
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args, {
		ast2
	});
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	llvm::Function *ir = gen.generateDeclFunction(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->getReturnType()->isVoidTy());
	ASSERT_STREQ(ir->getName().data(), "f");
	ASSERT_FALSE(ir->isVarArg());
	ASSERT_EQ(ir->arg_size(), 1);
	ASSERT_TRUE((ir->arg_begin())->getType()->isIntegerTy());
	ASSERT_EQ((ir->arg_begin())->getType()->getPrimitiveSizeInBits(), 32);
	ASSERT_STREQ((ir->arg_begin())->getName().data(), "x0");
}

TEST(Unit_CodeGen_LLVMGenerator, Good_DeclFunction_NoReturnTwoArgs) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);
	
	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast2 = Node(NodeType::DeclVariable, Token(TokenID::Symbol, "x0"));
	ast2.setFieldNode(FieldTag::DeclVariable_Type, Node(NodeType::TypeAtomicInt32));

	Node ast3 = Node(NodeType::DeclVariable, Token(TokenID::Symbol, "x1"));
	ast3.setFieldNode(FieldTag::DeclVariable_Type, Node(NodeType::TypeAtomicInt32));

	Node ast = Node(NodeType::DeclFunction, Token(TokenID::Symbol, "f"));
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node(NodeType::TypeVoid));
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args, {
		ast2,
		ast3
	});
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	llvm::Function *ir = gen.generateDeclFunction(ast);

	ASSERT_NE(ir, nullptr);

	ASSERT_TRUE(ir->getReturnType()->isVoidTy());
	ASSERT_STREQ(ir->getName().data(), "f");
	ASSERT_FALSE(ir->isVarArg());
	ASSERT_EQ(ir->arg_size(), 2);
	ASSERT_TRUE((ir->arg_begin())->getType()->isIntegerTy());
	ASSERT_EQ((ir->arg_begin())->getType()->getPrimitiveSizeInBits(), 32);
	ASSERT_STREQ((ir->arg_begin())->getName().data(), "x0");
	ASSERT_TRUE((ir->arg_begin()+1)->getType()->isIntegerTy());
	ASSERT_EQ((ir->arg_begin()+1)->getType()->getPrimitiveSizeInBits(), 32);
	ASSERT_STREQ((ir->arg_begin()+1)->getName().data(), "x1");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_DeclFunction_MissingReturn) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);

	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast = Node(NodeType::DeclFunction);
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args);
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	ASSERT_DEATH({
		gen.generateDeclFunction(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_DeclFunction_ReturnNonNode) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);

	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast = Node(NodeType::DeclFunction);
	ast.setFieldInt(FieldTag::DeclFunction_Return, 0);
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args);
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	ASSERT_DEATH({
		gen.generateDeclFunction(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_DeclFunction_ReturnNonType) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);

	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast = Node(NodeType::DeclFunction);
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node());
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args);
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	ASSERT_DEATH({
		gen.generateDeclFunction(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_DeclFunction_HasTemplateDeclArgs) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);

	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast = Node(NodeType::DeclFunction);
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNodeVector(FieldTag::DeclFunction_TemplateDeclArgs, {
		Node(NodeType::DeclVariable)
	});
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args);
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);

	ASSERT_DEATH({
		gen.generateDeclFunction(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_DeclFunction_ArgsNonDeclVariable) {
	LLVMGenerator gen;

	Node ast0 = Node(NodeType::StmtReturn);

	Node ast1 = Node(NodeType::StmtBlock);
	ast1.setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
		ast0
	});

	Node ast = Node(NodeType::DeclFunction);
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);
	ast.setFieldNodeVector(FieldTag::DeclFunction_Args, {
		Node()
	});

	ASSERT_DEATH({
		gen.generateDeclFunction(ast);
	}, "");
}

TEST(Unit_CodeGen_LLVMGenerator, Bad_DeclFunction_NoStmts) {
	LLVMGenerator gen;

	Node ast1 = Node(NodeType::StmtBlock);
	
	Node ast = Node(NodeType::DeclFunction);
	ast.setFieldNode(FieldTag::DeclFunction_Return, Node(NodeType::TypeAtomicInt32));
	ast.setFieldNode(FieldTag::DeclFunction_Body, ast1);
	
	ASSERT_DEATH({
		gen.generateDeclFunction(ast);
	}, "");
}
