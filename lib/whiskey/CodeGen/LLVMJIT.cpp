#include <whiskey/CodeGen/LLVMJIT.hpp>

// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wshorten-64-to-32"
// #pragma clang diagnostic ignored "-Wsign-conversion"
// #pragma clang diagnostic ignored "-Wold-style-cast"
// #pragma clang diagnostic ignored "-Wswitch-enum"
// #pragma clang diagnostic ignored "-Wdeprecated"
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
// #pragma clang diagnostic pop

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
llvm::JITSymbol LLVMJIT::findSymbol(const std::string &name) {
#ifdef LLVM_ON_WIN32
  const bool exportedSymbolsOnly = false;
#else
  const bool exportedSymbolsOnly = true;
#endif

  for (auto i : llvm::make_range(modules.rbegin(), modules.rend())) {
  	llvm::JITSymbol symbol = compileLayer.findSymbolIn(i, name, exportedSymbolsOnly);
    if (symbol) {
      return symbol;
    }
  }

  auto symbolAddress = llvm::RTDyldMemoryManager::getSymbolAddressInProcess(name);
  if (symbolAddress) {
    return llvm::JITSymbol(symbolAddress, llvm::JITSymbolFlags::Exported);
  }

#ifdef LLVM_ON_WIN32
  if (name.length() > 2 && name[0] == '_')
  void *symbolAddress = llvm::RTDyldMemoryManager::getSymbolAddressInProcess(name.substr(1));
  if (symbolAddress) {
    return llvm::JITSymbol(symbolAddress, llvm::JITSymbolFlags::Exported);
  }
#endif

  return nullptr;
}

void *LLVMJIT::onCompile(const std::string &name) {
	llvm::JITSymbol symbol = findSymbol(name);
	W_ASSERT_TRUE(symbol, "Cannot find symbol.");

	return reinterpret_cast<void *>(llvm::cantFail(symbol.getAddress()));
}

void LLVMJIT::init() {
	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmPrinter();
	llvm::InitializeNativeTargetAsmParser();
}

LLVMJIT::LLVMJIT() : targetMachine(llvm::EngineBuilder().selectTarget()), dataLayout(targetMachine->createDataLayout()), objectLayer([](){return std::make_shared<llvm::SectionMemoryManager>();}), compileLayer(objectLayer, llvm::orc::SimpleCompiler(*targetMachine)) {}

// LLVMJIT::~LLVMJIT() {}

void LLVMJIT::addModule(std::unique_ptr<llvm::Module> module) {
	module->setDataLayout(dataLayout);

	auto resolver = llvm::orc::createLambdaResolver(
		[&](const std::string &name) {
			llvm::JITSymbol symbol(nullptr);
			return symbol;
		},
		[](const std::string &name) {
			return nullptr;
		}
	);

	auto handle = llvm::cantFail(
		compileLayer.addModule(
			std::move(module),
			resolver
		)
	);

	modules.push_back(handle);
}
}
