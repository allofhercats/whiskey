#ifndef __WHISKEY_CodeGen_LLVMJIT_HPP
#define __WHISKEY_CodeGen_LLVMJIT_HPP

// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wshorten-64-to-32"
// #pragma clang diagnostic ignored "-Wsign-conversion"
// #pragma clang diagnostic ignored "-Wold-style-cast"
// #pragma clang diagnostic ignored "-Wswitch-enum"
// #pragma clang diagnostic ignored "-Wdeprecated"
#include <llvm/IR/Module.h>
#include <llvm/ExecutionEngine/Orc/CompileUtils.h>
#include <llvm/ExecutionEngine/Orc/IRCompileLayer.h>
#include <llvm/ExecutionEngine/Orc/LambdaResolver.h>
#include <llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
// #pragma clang diagnostic pop

#include <whiskey/CodeGen/JIT.hpp>

namespace whiskey {
class LLVMJIT : public JIT {
private:
	std::unique_ptr<llvm::TargetMachine> targetMachine;
	const llvm::DataLayout dataLayout;
	llvm::orc::RTDyldObjectLinkingLayer objectLayer;
	llvm::orc::IRCompileLayer<llvm::orc::RTDyldObjectLinkingLayer, llvm::orc::SimpleCompiler> compileLayer;
	std::vector<llvm::orc::IRCompileLayer<llvm::orc::RTDyldObjectLinkingLayer, llvm::orc::SimpleCompiler>::ModuleHandleT> modules;

	llvm::JITSymbol findSymbol(const std::string &name);

protected:
	void *onCompile(const std::string &name);

public:
	static void init();

	LLVMJIT();
	// ~LLVMJIT();

	void addModule(std::unique_ptr<llvm::Module> module);
};
}

#endif
