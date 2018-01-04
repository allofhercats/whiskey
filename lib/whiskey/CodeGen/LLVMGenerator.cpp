// #include "Module.inc"

#include <whiskey/CodeGen/LLVMGenerator.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/AST/Node.hpp>

#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/JITSymbol.h>

#include "LLVMJIT.hpp"

namespace whiskey {
llvm::Type *LLVMGenerator::generateType(const Node *node) {
  W_ASSERT_NONNULL(node, "Cannot generate null node.");
  W_ASSERT_TRUE(Node::getKindInfo(node->getKind()).isType(),
                "Cannot generate non-type node as type.");

  if (node->getKind() == Node::Kind::TypeAtomicBool) {
    return llvm::Type::getInt32Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicInt8) {
    return llvm::Type::getInt8Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicInt16) {
    return llvm::Type::getInt16Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicInt32) {
    return llvm::Type::getInt32Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicInt64) {
    return llvm::Type::getInt64Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicUInt8) {
    return llvm::Type::getInt8Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicUInt16) {
    return llvm::Type::getInt16Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicUInt32) {
    return llvm::Type::getInt32Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicUInt64) {
    return llvm::Type::getInt64Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicFloat32) {
    return llvm::Type::getFloatTy(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicFloat64) {
    return llvm::Type::getDoubleTy(ctx);
  } else if (node->getKind() == Node::Kind::TypeAtomicReal) {
    return llvm::Type::getFP128Ty(ctx);
  } else if (node->getKind() == Node::Kind::TypeFunction) {
    std::vector<llvm::Type *> tmp;
    for (const Node *i =
             node->getField(Node::FieldTag::TypeFunction_Args)->getNode();
         i != nullptr;
         i = i->getNext()) {
      tmp.push_back(generateType(i));
    }
    return llvm::FunctionType::get(
        generateType(
            node->getField(Node::FieldTag::TypeFunction_Return)->getNode()),
        tmp,
        false);
  } else {
    W_ASSERT_UNREACHABLE("Type is not supported.");
  }
}

llvm::Value *LLVMGenerator::generateValue(const Node *node) {
  W_ASSERT_NONNULL(node, "Cannot generate null node.");
  W_ASSERT_TRUE(Node::getKindInfo(node->getKind()).isExpr(),
                "Cannot generate non-expr node as expr.");

  if (node->getKind() == Node::Kind::ExprLiteralUInt) {
    return llvm::ConstantInt::get(
        generateType(
            node->getField(Node::FieldTag::ExprLiteralUInt_Type)->getNode()),
        node->getField(Node::FieldTag::ExprLiteralUInt_Value)->getUInt());
  } else if (node->getKind() == Node::Kind::ExprLiteralReal) {
    return llvm::ConstantFP::get(
        generateType(
            node->getField(Node::FieldTag::ExprLiteralReal_Type)->getNode()),
        node->getField(Node::FieldTag::ExprLiteralReal_Value)->getReal());
  } else {
    W_ASSERT_UNREACHABLE("Expr is not supported.");
  }
}

void LLVMGenerator::generateStmt(const Node *node) {
  W_ASSERT_NONNULL(node, "Cannot generate null node.");
  W_ASSERT_TRUE(Node::getKindInfo(node->getKind()).isStmt(),
                "Cannot generate non-stmt node as stmt.");

  if (node->getKind() == Node::Kind::StmtEmpty) {
  } else if (node->getKind() == Node::Kind::StmtExpr) {
    generateValue(node->getField(Node::FieldTag::StmtExpr_Expr)->getNode());
  } else if (node->getKind() == Node::Kind::StmtReturn) {
    builder.CreateRet(generateValue(
        node->getField(Node::FieldTag::StmtReturn_Arg)->getNode()));
  } else if (node->getKind() == Node::Kind::StmtBlock) {
    for (const Node *i =
             node->getField(Node::FieldTag::StmtBlock_Stmts)->getNode();
         i != nullptr;
         i = i->getNext()) {
      generateStmt(i);
    }
  } else {
    W_ASSERT_UNREACHABLE("Stmt is not supported.");
  }
}

void LLVMGenerator::generateDecl(const Node *node) {
  W_ASSERT_NONNULL(node, "Cannot generate null node.");
  W_ASSERT_TRUE(Node::getKindInfo(node->getKind()).isDecl(),
                "Cannot generate non-decl node as decl.");

  if (node->getKind() == Node::Kind::DeclFunction) {
    std::vector<llvm::Type *> argTypes;

    for (const Node *i =
             node->getField(Node::FieldTag::DeclFunction_Args)->getNode();
         i != nullptr;
         i = i->getNext()) {
      W_ASSERT_EQ(
          i->getKind(),
          Node::Kind::DeclVariable,
          "Function declaration must have only variable declaration nodes as arguments.");
      argTypes.push_back(generateType(
          i->getField(Node::FieldTag::DeclVariable_Type)->getNode()));
    }

    llvm::FunctionType *ft = llvm::FunctionType::get(
        generateType(
            node->getField(Node::FieldTag::DeclFunction_Return)->getNode()),
        argTypes,
        false);

    W_ASSERT_EQ(node->getField(Node::FieldTag::DeclFunction_Name)->getKind(),
                Field::Kind::String8,
                "Cannot output name with chars wider than 1 byte.");

    llvm::Function *f = llvm::Function::Create(
        ft,
        llvm::Function::ExternalLinkage,
        node->getField(Node::FieldTag::DeclFunction_Name)->getString8(),
        module);

    llvm::BasicBlock *bb = llvm::BasicBlock::Create(ctx, "entry", f);
    builder.SetInsertPoint(bb);

    generateStmt(node->getField(Node::FieldTag::DeclFunction_Body)->getNode());

    llvm::verifyFunction(*f);
  } else {
    W_ASSERT_UNREACHABLE("Decl is not supported.");
  }
}

void *LLVMGenerator::onGenerateFunctionPointer(const Node *node) {
  W_ASSERT_NONNULL(node, "Cannot generate null node.");
  W_ASSERT_EQ(
      node->getKind(),
      Node::Kind::DeclFunction,
      "Cannot generate function pointer from non-function declaration.");

  generateDecl(node);

  W_ASSERT_EQ(node->getField(Node::FieldTag::DeclFunction_Name)->getKind(),
              Field::Kind::String8,
              "Cannot output name with chars wider than 1 byte.");

  llvm::Function *f = module->getFunction(
      node->getField(Node::FieldTag::DeclFunction_Name)->getString8());
  if (f == nullptr) {
    W_ASSERT_UNREACHABLE(
        "Method generateDecl did not output function with given name.");
  }

  jit->addModule(module);
  llvm::JITSymbol symbol = jit->findSymbol(
      node->getField(Node::FieldTag::DeclFunction_Name)->getString8());
  W_ASSERT_TRUE(symbol, "Cannot find function symbol in JIT process.");

  return (void *)llvm::cantFail(symbol.getAddress());
}

void LLVMGenerator::onGenerateObjectFile(const Node *node,
                                         const std::string &path) {
  // module->setDataLayout(jit->getTargetMachine().createDataLayout());

  // std::error_code ec;
  // llvm::raw_fd_ostream f(path, ec, llvm::sys::fs::F_None);
  // W_ASSERT_FALSE(ec, "Error message: " << ec.message());

  // llvm::legacy::PassManager pm;
  // auto ft = llvm::TargetMachine::CGFT_ObjectFile;

  // W_ASSERT_TRUE(jit->getTargetMachine().addPassesToEmitFile(pm, f, ft),
  // "Target machine cannot emit object file.");

  // pm.run(*module);
  // f.flush();

  // f.close();
}

void LLVMGenerator::init() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmParser();
  llvm::InitializeNativeTargetAsmPrinter();
}

LLVMGenerator::LLVMGenerator() : builder(ctx) {
  jit = new LLVMJIT();

  module = new llvm::Module("my_module", ctx);
  module->setDataLayout(jit->getTargetMachine().createDataLayout());
}

LLVMGenerator::~LLVMGenerator() {
  delete jit;
}

llvm::Module *LLVMGenerator::getModule() {
  return module;
}

llvm::Function *LLVMGenerator::getFunction(const std::string &name) {
  return module->getFunction(name);
}
} // namespace whiskey
