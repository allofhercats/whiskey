#ifndef __WHISKEY_CodeGen_LLVMJIT_HPP
#define __WHISKEY_CodeGen_LLVMJIT_HPP

#include <whiskey/CodeGen/Module.inc>

namespace whiskey {
class LLVMJIT {
private:
  llvm::TargetMachine *tm;
  const llvm::DataLayout dl;
  llvm::orc::RTDyldObjectLinkingLayer ol;
  llvm::orc::IRCompileLayer<decltype(ol), llvm::orc::SimpleCompiler> cl;

public:
  using ModuleHandle = decltype(cl)::ModuleHandleT;

  LLVMJIT();
  LLVMJIT(const LLVMJIT &) = delete;
  ~LLVMJIT();

  llvm::TargetMachine &getTargetMachine();
  ModuleHandle addModule(llvm::Module *m);
  llvm::JITSymbol findSymbol(const std::string &name);
  llvm::JITTargetAddress getSymbolAddress(const std::string &name);
  void removeModule(ModuleHandle handle);
};
} // namespace whiskey

#endif
