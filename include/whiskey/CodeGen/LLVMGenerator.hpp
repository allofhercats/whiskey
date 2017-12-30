#ifndef __WHISKEY_CodeGen_LLVMGenerator_HPP
#define __WHISKEY_CodeGen_LLVMGenerator_HPP

#include <whiskey/CodeGen/Module.inc>

#include <whiskey/CodeGen/Generator.hpp>
#include <whiskey/CodeGen/LLVMJIT.hpp>

namespace whiskey {
class LLVMGenerator : public Generator {
private:
  llvm::LLVMContext ctx;
  llvm::IRBuilder<> builder;
  llvm::Module *module;
  LLVMJIT *jit;

protected:
  void *onGenerateFunctionPointer(const Node *node);
  void onGenerateObjectFile(const Node *node, const std::string &path);

public:
  static void init();

  LLVMGenerator();
  ~LLVMGenerator();

  llvm::Type *generateType(const Node *node);
  llvm::Value *generateValue(const Node *node);
  void generateStmt(const Node *node);
  void generateDecl(const Node *node);
  void generateUnit(const Node *node);

  llvm::Module *getModule();
  llvm::Function *getFunction(const std::string &name);
};
} // namespace whiskey

#endif
