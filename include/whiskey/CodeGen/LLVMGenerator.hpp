#ifndef __WHISKEY_CodeGen_LLVMGenerator_HPP
#define __WHISKEY_CodeGen_LLVMGenerator_HPP

// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wshorten-64-to-32"
// #pragma clang diagnostic ignored "-Wsign-conversion"
// #pragma clang diagnostic ignored "-Wold-style-cast"
// #pragma clang diagnostic ignored "-Wswitch-enum"
// #pragma clang diagnostic ignored "-Wdeprecated"
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
// #include <llvm/ExecutionEngine/Orc/ExecutionUtils.h>
// #include <llvm/ExecutionEngine/Orc/CompileUtils.h>
// #include <llvm/ExecutionEngine/Orc/IRCompileLayer.h>
// #include <llvm/ExecutionEngine/Orc/LambdaResolver.h>
// #include <llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h>
// #include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
// #include "llvm/ExecutionEngine/SectionMemoryManager.h"
// #include <llvm/IR/LegacyPassManager.h>
// #include <llvm/Transforms/Scalar.h>
// #include <llvm/Transforms/Scalar/GVN.h>
// #include "llvm/ADT/STLExtras.h"
// #include "llvm/ADT/iterator_range.h"
// #include <llvm/ExecutionEngine/ExecutionEngine.h>
// #include "llvm/ExecutionEngine/JITSymbol.h"
// #include <llvm/ExecutionEngine/Orc/Core.h>
// #include <llvm/ExecutionEngine/Orc/CompileUtils.h>
// #include <llvm/ExecutionEngine/Orc/IRCompileLayer.h>
// #include "llvm/ExecutionEngine/Orc/LambdaResolver.h"
// #include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
// #include <llvm/ExecutionEngine/RTDyldMemoryManager.h>
// #include "llvm/ExecutionEngine/SectionMemoryManager.h"
// #include "llvm/IR/DataLayout.h"
// #include "llvm/IR/Mangler.h"
// #include "llvm/Support/DynamicLibrary.h"
// #include "llvm/Support/raw_ostream.h"
// #include "llvm/Target/TargetMachine.h"
// #pragma clang diagnostic pop

#include <whiskey/CodeGen/Generator.hpp>

namespace llvm {
class Module;
class Type;
class Value;
}

namespace whiskey {
class Node;

class LLVMGenerator : public Generator {
private:
	static bool isJITInitted;

	llvm::LLVMContext llvmCtx;
	llvm::IRBuilder<> llvmBuilder;
	std::unique_ptr<llvm::Module> llvmModule;
	std::unique_ptr<llvm::legacy::FunctionPassManager> llvmPassMgr;
	// llvm::orc::ExecutionSession llvmExecSession;
	// std::unique_ptr<llvm::SymbolResolver> llvmSymbolResolver;
	// std::unique_ptr<llvm::TargetMachine> llvmTargetMachine;
	// const llvm::DataLayout llvmDataLayout;
	// llvm::RTDyldObjectLinkingLayer llvmObjectLayer;
	// llvm::IRCompileLayer<llvm::RTDyldObjectLinkingLayer, llvm::SimpleCompiler> llvmCompileLayer;

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

	// void *jitCompile(llvm::Function *func);

protected:
	void onGenerateUnit(const Node &node);

public:
	LLVMGenerator();

	llvm::Type *generateType(const Node &node);
	llvm::Value *generateExpr(const Node &node);
	void generateStmt(const Node &node);
	llvm::GlobalVariable *generateDeclVariable(const Node &node);
	llvm::Function *generateDeclFunction(const Node &node);

	std::unique_ptr<llvm::Module> &getLLVMModule();
};
}

#endif
