#include "Integration.hpp"

#include <whiskey/CodeGen/JIT.hpp>

#include <whiskey-testing/IntegrationTest.hpp>
#include <whiskey-testing/IntegrationTestSuite.hpp>

using namespace whiskey;

extern IntegrationTestSuite suite;

void initSimple() {
	
	//////////////////////////////////////////////////////////////////////

	IntegrationTest empty("empty");

  empty.setSourceMode(IntegrationTest::SourceMode::Memory);
  empty.setSourceText(R"source(
  )source");

  empty.setCheckTokens(true);
  empty.setExpectedTokens({});

  empty.setCheckAST(true);
  empty.setExpectedAST(Node(NodeType::Unit)
  	.setFieldNodeVector(FieldTag::Unit_Members));

  suite.add(empty);

  //////////////////////////////////////////////////////////////////////

  IntegrationTest returnVoid("returnVoid");

  returnVoid.setSourceMode(IntegrationTest::SourceMode::Memory);
  returnVoid.setSourceText(R"source(
    void f() {
      return;
    }
  )source");

  returnVoid.setCheckTokens(true);
  returnVoid.setExpectedTokens({
    Token(TokenID::KWVoid, "void"),
    Token(TokenID::Symbol, "f"),
    Token(TokenID::LParen),
    Token(TokenID::RParen),
    Token(TokenID::LBrace),
    Token(TokenID::KWReturn, "return"),
    Token(TokenID::Semicolon),
    Token(TokenID::RBrace)
  });

  returnVoid.setCheckAST(true);
  returnVoid.setExpectedAST(
    Node(NodeType::Unit)
      .setFieldNodeVector(FieldTag::Unit_Members, {
        Node(NodeType::DeclFunction)
          .setFieldNode(FieldTag::DeclFunction_Return,
            Node(NodeType::TypeVoid)
          )
          .setFieldNodeVector(FieldTag::DeclFunction_TemplateDeclArgs)
          .setFieldNodeVector(FieldTag::DeclFunction_Args)
          .setFieldNode(FieldTag::DeclFunction_Body,
            Node(NodeType::StmtBlock)
              .setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
                Node(NodeType::StmtReturn)
              })
          )
      }
    )
  );

  returnVoid.setExecutionTest([](JIT &jit) {
    std::function<void(void)> f = jit.compile<void(void)>("f");
    f();
  });

  suite.add(returnVoid);

  //////////////////////////////////////////////////////////////////////

	IntegrationTest returnInt32("returnInt32");

  returnInt32.setSourceMode(IntegrationTest::SourceMode::Memory);
  returnInt32.setSourceText(R"source(
  	int32 f() {
      return 5;
    }
  )source");

  returnInt32.setCheckTokens(true);
  returnInt32.setExpectedTokens({
  	Token(TokenID::KWInt32, "int32"),
  	Token(TokenID::Symbol, "f"),
    Token(TokenID::LParen),
    Token(TokenID::RParen),
    Token(TokenID::LBrace),
    Token(TokenID::KWReturn, "return"),
    Token(TokenID::Int, "5"),
    Token(TokenID::Semicolon),
    Token(TokenID::RBrace)
  });

  returnInt32.setCheckAST(true);
  returnInt32.setExpectedAST(
  	Node(NodeType::Unit)
	  	.setFieldNodeVector(FieldTag::Unit_Members, {
	  		Node(NodeType::DeclFunction)
	  			.setFieldNode(FieldTag::DeclFunction_Return,
	  				Node(NodeType::TypeAtomicInt32)
	  			)
	  			.setFieldNodeVector(FieldTag::DeclFunction_TemplateDeclArgs)
          .setFieldNodeVector(FieldTag::DeclFunction_Args)
          .setFieldNode(FieldTag::DeclFunction_Body,
            Node(NodeType::StmtBlock)
              .setFieldNodeVector(FieldTag::StmtBlock_Stmts, {
                Node(NodeType::StmtReturn)
                  .setFieldNode(FieldTag::StmtReturn_Arg,
                    Node(NodeType::ExprLiteralUInt64)
                      .setFieldUInt(FieldTag::ExprLiteralUInt64_Value, 5)
                  )
              })
          )
	  	}
	  )
  );

  suite.add(returnInt32);

  //////////////////////////////////////////////////////////////////////

}
