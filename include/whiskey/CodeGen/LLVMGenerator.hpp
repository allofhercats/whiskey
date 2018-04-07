#ifndef __WHISKEY_CodeGen_LLVMGenerator_HPP
#define __WHISKEY_CodeGen_LLVMGenerator_HPP

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wdeprecated"
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#pragma clang diagnostic pop

namespace llvm {
class Module;
class Type;
class Value;
}

namespace whiskey {
class Node;

class LLVMGenerator {
private:
	llvm::LLVMContext llvmCtx;
	llvm::IRBuilder<> llvmBuilder;
	std::unique_ptr<llvm::Module> llvmModule;

	llvm::Type *generateTypeFunction(const Node &node);
	llvm::Value *generateExprLiteralBool(const Node &node);
	llvm::Value *generateExprLiteralInt8(const Node &node);
	llvm::Value *generateExprLiteralInt16(const Node &node);
	llvm::Value *generateExprLiteralInt32(const Node &node);
	llvm::Value *generateExprLiteralInt64(const Node &node);
	llvm::Value *generateExprLiteralUInt8(const Node &node);
	llvm::Value *generateExprLiteralUInt16(const Node &node);
	llvm::Value *generateExprLiteralUInt32(const Node &node);
	llvm::Value *generateExprLiteralUInt64(const Node &node);
	llvm::Value *generateExprLiteralFloat32(const Node &node);
	llvm::Value *generateExprLiteralFloat64(const Node &node);
	llvm::Value *generateExprLiteralReal(const Node &node);
	llvm::Value *generateExprCall(const Node &node);
	llvm::Value *generateExprAdd(const Node &node);
	llvm::Value *generateExprNeg(const Node &node);
	llvm::Value *generateExprMul(const Node &node);
	void generateStmtReturn(const Node &node);
	void generateStmtBlock(const Node &node);

public:
	LLVMGenerator();

	llvm::Type *generateType(const Node &node);
	llvm::Value *generateExpr(const Node &node);
	void generateStmt(const Node &node);
	llvm::Function *generateDeclFunction(const Node &node);
};
}

#endif
