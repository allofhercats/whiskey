#include "LLVMJIT.hpp"

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/ExecutionEngine/Orc/LambdaResolver.h>
#include <llvm/IR/Mangler.h>

namespace whiskey {
LLVMJIT::LLVMJIT()
    : tm(llvm::EngineBuilder().selectTarget()), dl(tm->createDataLayout()),
      ol([]() { return std::make_shared<llvm::SectionMemoryManager>(); }),
      cl(ol, llvm::orc::SimpleCompiler(*tm)) {
  llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);
}

LLVMJIT::~LLVMJIT() {
}

llvm::TargetMachine &LLVMJIT::getTargetMachine() {
  return *tm;
}

LLVMJIT::ModuleHandle LLVMJIT::addModule(llvm::Module *m) {
  auto resolver = llvm::orc::createLambdaResolver(
      [&](const std::string &name) {
        if (auto sym = cl.findSymbol(name, false)) {
          return sym;
        } else {
          return llvm::JITSymbol(nullptr);
        }
      },
      [](const std::string &name) {
        if (auto symAddr =
                llvm::RTDyldMemoryManager::getSymbolAddressInProcess(name)) {
          return llvm::JITSymbol(symAddr, llvm::JITSymbolFlags::Exported);
        } else {
          return llvm::JITSymbol(nullptr);
        }
      });

  return llvm::cantFail(
      cl.addModule(std::shared_ptr<llvm::Module>(m), std::move(resolver)));
}

llvm::JITSymbol LLVMJIT::findSymbol(const std::string &name) {
  std::string mn;
  llvm::raw_string_ostream mns(mn);
  llvm::Mangler::getNameWithPrefix(mns, name, dl);
  return cl.findSymbol(mns.str(), true);
}

llvm::JITTargetAddress LLVMJIT::getSymbolAddress(const std::string &name) {
  return llvm::cantFail(findSymbol(name).getAddress());
}

void LLVMJIT::removeModule(LLVMJIT::ModuleHandle handle) {
  llvm::cantFail(cl.removeModule(handle));
}
} // namespace whiskey
