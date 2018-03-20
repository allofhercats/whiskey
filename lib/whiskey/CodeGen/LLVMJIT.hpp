#ifndef __WHISKEY_LIB_CodeGen_LLVMJIT_HPP
#define __WHISKEY_LIB_CodeGen_LLVMJIT_HPP

// #include <llvm/ExecutionEngine/Orc/CompileUtils.h>
// #include <llvm/ExecutionEngine/Orc/IRCompileLayer.h>
// #include <llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h>
// #include <llvm/Target/TargetMachine.h>

// namespace whiskey {
// class LLVMJIT {
// private:
//   llvm::TargetMachine *tm;
//   const llvm::DataLayout dl;
//   llvm::orc::RTDyldObjectLinkingLayer ol;
//   llvm::orc::IRCompileLayer<llvm::orc::RTDyldObjectLinkingLayer,
//                             llvm::orc::SimpleCompiler>
//       cl;

// public:
//   using ModuleHandle =
//       llvm::orc::IRCompileLayer<llvm::orc::RTDyldObjectLinkingLayer,
//                                 llvm::orc::SimpleCompiler>::ModuleHandleT;

//   LLVMJIT();
//   LLVMJIT(const LLVMJIT &) = delete;
//   ~LLVMJIT();

//   llvm::TargetMachine &getTargetMachine();
//   ModuleHandle addModule(llvm::Module *m);
//   llvm::JITSymbol findSymbol(const std::string &name);
//   llvm::JITTargetAddress getSymbolAddress(const std::string &name);
//   void removeModule(ModuleHandle handle);
// };
// } // namespace whiskey

#endif
